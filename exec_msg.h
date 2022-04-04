#ifndef EXEC_MSG_H
#define EXEC_MSG_H

#endif // EXEC_MSG_H

enum exec_msg {
    ERR_INVALID_BIN = -6,
    ERR_BAD_PATH = -5,
    ERR_OPEN_WRITE = -4,
    ERR_OPEN_READ = -3,
    ERR_NO_INPUT = -2,
    ERR_FILE_NOT_EXIST = -1,
    SUCCEED = 0,
    UNEXPECTED = 1,
    UNHANDLED = 2,
    };
