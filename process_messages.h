#ifndef PROCESS_MESSAGES_H
#define PROCESS_MESSAGES_H

#include <stdint.h>
#include <stdio.h>

typedef struct input_msg_s {
  uint8_t type;
  uint8_t length;
  char msg[255];
  uint32_t crc32;
  uint32_t mask;
} input_msg_t;

typedef struct output_msg_s {
  uint8_t type;
  uint8_t length;
  char msg[255];
  uint8_t crc32;
  uint8_t length_mod;
  char msg_masked[255];
  uint8_t crc32_mod;
} output_msg_t;

int parse_next_message(FILE* input, input_msg_t* msg );

int convert_message(const input_msg_t* msg_in, output_msg_t* msg_out);

int save_message(FILE* output, const output_msg_t* msg);

#endif
