#include <stdlib.h>
#include <string.h>

#include "embedded_cli.h"
#include "cli_setup.h"

#define CLI_TOKEN_NPOS 0xff

#ifndef UNUSED
#define UNUSED(x) (void)x
#endif

#define PREPARE_IMPL(t) \
  EmbeddedCliImpl* impl = (EmbeddedCliImpl*)t->_impl

#define IS_FLAG_SET(flags, flag) (((flags) & (flag)) != 0)

#define SET_FLAG(flags, flag) ((flags) |= (flag))

#define UNSET_U8FLAG(flags, flag) ((flags) &= (uint8_t) ~(flag))

/**
 * Indicates that rx buffer overflow happened. In such case last command
 * that wasn't finished (no \r or \n were received) will be discarded
 */
#define CLI_FLAG_OVERFLOW 0x01u

/**
 * Indicates that live autocompletion is enabled
 */
#define CLI_FLAG_SCRIPTING_MODE_ENABLED 0x02u

typedef struct EmbeddedCliImpl EmbeddedCliImpl;
typedef struct FifoBuf FifoBuf;

struct FifoBuf {
    char *buf;
    /**
     * Position of first element in buffer. From this position elements are taken
     */
    uint8_t front;
    /**
     * Position after last element. At this position new elements are inserted
     */
    uint8_t back;
    /**
     * Size of buffer
     */
    uint8_t size;
};

struct EmbeddedCliImpl {
    /**
     * Buffer for storing received chars.
     * Chars are stored in FIFO mode.
     */
    FifoBuf rxBuffer;

    /**
     * Buffer for current command
     */
    char *cmdBuffer;

    /**
     * Size of current command
     */
    uint8_t cmdSize;

    /**
     * Total size of command buffer
     */
    uint8_t cmdMaxSize;

    CliCommandBinding *bindings;

    /**
     * Flags for each binding. Sizes are the same as for bindings array
     */
    uint8_t *bindingsFlags;

    uint8_t bindingsCount;

    uint8_t maxBindingsCount;

    /**
     * Total length of input line. This doesn't include invitation but
     * includes current command and its live autocompletion
     */
    uint8_t inputLineLength;

    /**
     * Stores last character that was processed.
     */
    char lastChar;

    /**
     * Flags are defined as CLI_FLAG_*
     */
    uint8_t flags;
};

static EmbeddedCliConfig defaultConfig;

static const char *lineBreak = "\n";

/**
 * Process input character. Character is valid displayable char and should be
 * added to current command string and displayed to client.
 * @param cli
 * @param c
 */
static void onDisplayableCharInput(EmbeddedCli *cli, char c);

/**
 * Process input character. If scripting mode is enabled no matter the char, 
 * it should be added to current command string.
 * @param cli
 * @param c
 */
static void onCharInput(EmbeddedCli *cli, char c);

/**
 * Process control character (like \r or \n) possibly altering state of current
 * command or executing onCommand callback.
 * @param cli
 * @param c
 */
static void onControlInput(EmbeddedCli *cli, char c);

/**
 * Parse command in buffer and execute callback
 * @param cli
 */
static void parseCommand(EmbeddedCli *cli);

/**
 * Write given string to cli output
 * @param cli
 * @param str
 */
static void writeToOutput(EmbeddedCli *cli, const char *str);

/**
 * Write given ctype buffer to cli output
 * @param cli
 * @param buffer
 * @param size
 */
static void writeToOutputCtypes(EmbeddedCli *cli, uint8_t *buffer, size_t size);

/**
 * Returns true if provided char is a supported control char:
 * \r, \n, \b or 0x7F (treated as \b)
 * @param c
 * @return True or False
 */
static bool isControlChar(char c);

/**
 * Returns true if provided char is a supported control char in ctypes mode:
 * \n
 * @param c
 * @return True or False
 */
static bool isControlCharCtypes(char c);

/**
 * Returns true if provided char is a valid displayable character:
 * a-z, A-Z, 0-9, whitespace, punctuation, etc.
 * Currently only ASCII is supported
 * @param c
 * @return
 */
static bool isDisplayableChar(char c);

/**
 * How many elements are currently available in buffer
 * @param buffer
 * @return number of elements
 */
static uint8_t fifoBufAvailable(FifoBuf *buffer);

/**
 * Return first character from buffer and remove it from buffer
 * Buffer must be non-empty, otherwise 0 is returned
 * @param buffer
 * @return
 */
static char fifoBufPop(FifoBuf *buffer);

/**
 * Push character into fifo buffer. If there is no space left, character is
 * discarded and false is returned
 * @param buffer
 * @param a - character to add
 * @return true if char was added to buffer, false otherwise
 */
static bool fifoBufPush(FifoBuf *buffer, char a);

/**
 * Return position (index of first char) of specified token
 * @param tokenizedStr - tokenized string (separated by \0 with
 * \0\0 at the end)
 * @param pos - token position (counted from 1)
 * @return index of first char of specified token
 */
static uint8_t getTokenPosition(const char *tokenizedStr, uint8_t pos);

#define EMBEDDED_CLI_REQUIRED_SIZE (sizeof(EmbeddedCli) \
                                  + sizeof(EmbeddedCliImpl) \
                                  + CLI_RX_BUFFER_SIZE \
                                  + CLI_CMD_BUFFER_SIZE \
                                  + (CLI_MAX_BINDING_COUNT \
                                   * (sizeof(CliCommandBinding) + sizeof(uint8_t))))

EmbeddedCli *embeddedCliNew(EmbeddedCliConfig *config) {
    EmbeddedCli *cli = NULL;

    uint8_t *buf = config->cliBuffer;

    // memset(buf, 0, EMBEDDED_CLI_REQUIRED_SIZE);

    cli = (EmbeddedCli *) buf;
    buf += sizeof(EmbeddedCli);

    cli->_impl = (EmbeddedCliImpl *) buf;
    buf += sizeof(EmbeddedCliImpl);

    PREPARE_IMPL(cli);
    impl->rxBuffer.buf = (char *) buf;
    buf += config->rxBufferSize * sizeof(char);

    impl->cmdBuffer = (char *) buf;
    buf += config->cmdBufferSize * sizeof(char);

    impl->bindings = (CliCommandBinding *) buf;
    buf += CLI_MAX_BINDING_COUNT * sizeof(CliCommandBinding);

    impl->bindingsFlags = buf;
    buf += CLI_MAX_BINDING_COUNT;

    impl->rxBuffer.size = config->rxBufferSize;
    impl->rxBuffer.front = 0;
    impl->rxBuffer.back = 0;
    impl->cmdMaxSize = config->cmdBufferSize;
    impl->bindingsCount = 0;
    impl->maxBindingsCount = config->maxBindingCount;
    impl->lastChar = '\0';

    return cli;
}

void embeddedCliReceiveChar(EmbeddedCli *cli, char c) {
    PREPARE_IMPL(cli);

    if (!fifoBufPush(&impl->rxBuffer, c)) {
        SET_FLAG(impl->flags, CLI_FLAG_OVERFLOW);
    }
}

void embeddedCliProcess(EmbeddedCli *cli) {
    if (cli->writeChar == NULL)
        return;

    PREPARE_IMPL(cli);

    while (fifoBufAvailable(&impl->rxBuffer)) {
        char c = fifoBufPop(&impl->rxBuffer);

        if (isControlChar(c))
        {
            onControlInput(cli, c);
        }
        else
        {
            onCharInput(cli, c);
        }

        impl->lastChar = c;
    }

    // discard unfinished command if overflow happened
    if (IS_FLAG_SET(impl->flags, CLI_FLAG_OVERFLOW)) {
        impl->cmdSize = 0;
        impl->cmdBuffer[impl->cmdSize] = '\0';
        UNSET_U8FLAG(impl->flags, CLI_FLAG_OVERFLOW);
    }
}

bool embeddedCliAddBinding(EmbeddedCli *cli, CliCommandBinding binding) {
    PREPARE_IMPL(cli);
    if (impl->bindingsCount == impl->maxBindingsCount)
        return false;

    impl->bindings[impl->bindingsCount] = binding;

    ++impl->bindingsCount;
    return true;
}

void embeddedCliPrint(EmbeddedCli *cli, const char *string) {
    if (cli->writeChar == NULL)
        return;

    PREPARE_IMPL(cli);

    // print provided string
    writeToOutput(cli, string);
    writeToOutput(cli, lineBreak);
}

void embeddedCliSendCtype(EmbeddedCli *cli, uint8_t *bytes, size_t size) {
    if (cli->writeChar == NULL)
        return;

    // send provided bytes
    writeToOutputCtypes(cli, bytes, size);
}

void embeddedCliTokenizeArgs(char *args) {
    if (args == NULL)
        return;

    // for now only space, but can add more later
    const char *separators = " ";

    // indicates that arg is quoted so separators are copied as is
    bool quotesEnabled = false;
    // indicates that previous char was a slash, so next char is copied as is
    bool escapeActivated = false;
    int insertPos = 0;

    int i = 0;
    char currentChar;
    while ((currentChar = args[i]) != '\0') {
        ++i;

        if (escapeActivated) {
            escapeActivated = false;
        } else if (currentChar == '\\') {
            escapeActivated = true;
            continue;
        } else if (currentChar == '"') {
            quotesEnabled = !quotesEnabled;
            currentChar = '\0';
        } else if (!quotesEnabled && strchr(separators, currentChar) != NULL) {
            currentChar = '\0';
        }

        // null chars are only copied once and not copied to the beginning
        if (currentChar != '\0' || (insertPos > 0 && args[insertPos - 1] != '\0')) {
            args[insertPos] = currentChar;
            ++insertPos;
        }
    }

    // make args double null-terminated source buffer must be big enough to contain extra spaces
    args[insertPos] = '\0';
    args[insertPos + 1] = '\0';
}

const char *embeddedCliGetToken(const char *tokenizedStr, uint8_t pos) {
    uint8_t i = getTokenPosition(tokenizedStr, pos);

    if (i != CLI_TOKEN_NPOS)
        return &tokenizedStr[i];
    else
        return NULL;
}

static void onCharInput(EmbeddedCli *cli, char c) {
    PREPARE_IMPL(cli);

    // have to reserve two extra chars for command ending (used in tokenization)
    if (impl->cmdSize + 2 >= impl->cmdMaxSize)
        return;

    impl->cmdBuffer[impl->cmdSize] = c;
    ++impl->cmdSize;
    impl->cmdBuffer[impl->cmdSize] = '\0';
}

static void onControlInput(EmbeddedCli *cli, char c) {
    PREPARE_IMPL(cli);

    // process \r\n and \n\r as single \r\n command
    if ((impl->lastChar == '\r' && c == '\n') ||
        (impl->lastChar == '\n' && c == '\r'))
        return;

    if (c == '\n') {
        if (impl->cmdSize > 0)
            parseCommand(cli);
        impl->cmdSize = 0;
        impl->cmdBuffer[impl->cmdSize] = '\0';
        impl->inputLineLength = 0;
    }

}

static void parseCommand(EmbeddedCli *cli) {
    PREPARE_IMPL(cli);

    bool isEmpty = true;

    for (int i = 0; i < impl->cmdSize; ++i) {
        if (impl->cmdBuffer[i] != ' ') {
            isEmpty = false;
            break;
        }
    }
    // do not process empty commands
    if (isEmpty)
        return;

    char *cmdName = NULL;
    char *cmdArgs = NULL;
    bool nameFinished = false;

    // find command name and command args inside command buffer
    for (int i = 0; i < impl->cmdSize; ++i) {
        char c = impl->cmdBuffer[i];

        if (c == ' ') {
            // all spaces between name and args are filled with zeros
            // so name is a correct null-terminated string
            if (cmdArgs == NULL)
                impl->cmdBuffer[i] = '\0';
            if (cmdName != NULL)
                nameFinished = true;

        } else if (cmdName == NULL) {
            cmdName = &impl->cmdBuffer[i];
        } else if (cmdArgs == NULL && nameFinished) {
            cmdArgs = &impl->cmdBuffer[i];
        }
    }

    // we keep two last bytes in cmd buffer reserved so cmdSize is always by 2
    // less than cmdMaxSize
    impl->cmdBuffer[impl->cmdSize + 1] = '\0';

    if (cmdName == NULL)
        return;

    // try to find command in bindings
    for (int i = 0; i < impl->bindingsCount; ++i) {
        if (strcmp(cmdName, impl->bindings[i].name) == 0) {
            if (impl->bindings[i].binding == NULL)
                break;

            if (impl->bindings[i].tokenizeArgs) {
                embeddedCliTokenizeArgs(cmdArgs);
            }
            else {
                impl->bindings[i].binding(cli, cmdArgs);
            }
            return;
        }
    }
}

static void writeToOutput(EmbeddedCli *cli, const char *str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len; ++i) {
        cli->writeChar(cli, str[i]);
    }
}

static void writeToOutputCtypes(EmbeddedCli *cli, uint8_t *buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        cli->writeChar(cli, buffer[i]);
    }
}

static bool isControlChar(char c) {
    return c == '\n';
}

static uint8_t fifoBufAvailable(FifoBuf *buffer) {
    if (buffer->back >= buffer->front)
        return (uint8_t) (buffer->back - buffer->front);
    else
        return (uint8_t) (buffer->size - buffer->front + buffer->back);
}

static char fifoBufPop(FifoBuf *buffer) {
    char a = '\0';
    if (buffer->front != buffer->back) {
        a = buffer->buf[buffer->front];
        buffer->front = (uint8_t) (buffer->front + 1) % buffer->size;
    }
    return a;
}

static bool fifoBufPush(FifoBuf *buffer, char a) {
    uint8_t newBack = (uint8_t) (buffer->back + 1) % buffer->size;
    if (newBack != buffer->front) {
        buffer->buf[buffer->back] = a;
        buffer->back = newBack;
        return true;
    }
    return false;
}

static uint8_t getTokenPosition(const char *tokenizedStr, uint8_t pos) {
    if (tokenizedStr == NULL || pos == 0)
        return CLI_TOKEN_NPOS;
    uint8_t i = 0;
    uint8_t tokenCount = 1;
    while (true) {
        if (tokenCount == pos)
            break;

        if (tokenizedStr[i] == '\0') {
            ++tokenCount;
            if (tokenizedStr[i + 1] == '\0')
                break;
        }

        ++i;
    }

    if (tokenizedStr[i] != '\0')
        return i;
    else
        return CLI_TOKEN_NPOS;
}