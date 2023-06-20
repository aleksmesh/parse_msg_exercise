#ifndef PROCESS_MESSAGES_H
#define PROCESS_MESSAGES_H

#include <stdint.h>
#include <stdio.h>

struct input_msg_t {
  uint8_t type;
  uint8_t length;
  char msg[255];
  uint32_t crc32;
  uint32_t mask;
};
typedef struct input_msg_t input_msg;

struct output_msg_t {
  uint8_t type;
  uint8_t length;
  char msg[255];
  uint8_t crc32;
  uint8_t length_mod;
  char msg_masked[255];
  uint8_t crc32_mod;
};
typedef struct output_msg_t output_msg;

int parse_next_message(FILE* input, input_msg* msg );

int convert_message(input_msg* msg_in, output_msg* msg_out);

int save_message(FILE* output, output_msg* msg);

#endif
