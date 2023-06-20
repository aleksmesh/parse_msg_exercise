#ifndef CONSTANTS_H
#define CONSTANTS_H

enum errors {
  NO_ERROR = 0,
  ERR_OPEN_FILE = 1,
};

#define MASK_SIZE 4

#define CHUNK_SIZE 4

#define CRC32_SIZE 4

#define START_MSG_IDENT  "mess="
#define START_MASK_IDENT "mask="
#define START_LENGTH  5

#define INPUT_FILE_NAME "data_in.txt"
#define INPUT_UNHEXED_FILE_NAME "data_in_unhexed"
#define OUTPUT_FILE_NAME "data_out.txt"
#define OUTPUT_UNHEXED_FILE_NAME "data_out_unhexed"
#define ERR_LOG_FILE_NAME "error.log"

extern FILE* err_log;

#endif
