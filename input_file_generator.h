#ifndef INPUT_FILE_GENERATOR_H
#define INPUT_FILE_GENERATOR_H

#include <stdint.h>

void rand_string(char* buf, uint8_t length);

uint8_t rand_msg_type();

int generate_input_file();

#endif
