#include "input_file_generator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "crc32.h"
#include "mes_hex.h"

void rand_string(char* buf, uint8_t length) {
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
  static uint8_t charset_length = sizeof(charset) - 1;

  if (NULL != buf) {
    for (uint8_t n = 0; n < length; ++n) {
      int key = rand() % (int)(charset_length);
      buf[n] = charset[key];
    }
    buf[length] = '\0';
  }
}

uint8_t rand_msg_type()
{
  return rand() % 255;
}

int generate_input_file()
{
  FILE* input = fopen(INPUT_UNHEXED_FILE_NAME, "w");
  if (NULL == input) {
    fprintf(err_log, "Can't open file %s for writing\n", INPUT_UNHEXED_FILE_NAME);
    return ERR_OPEN_FILE;
  }

  char* random_string = malloc(54);
  for (int i = 0; i < 437; ++i) {
    fputs("mess=", input);
    uint8_t type = rand_msg_type();
    fputc(type, input);
    rand_string(random_string, 54);
    fputc(strlen(random_string), input);
    fputs(random_string, input);
    uint32_t crc = crc32(random_string, strlen(random_string));
    putw(crc, input);
    fputs("mask=", input);
    putw(rand(), input);
  }
  fclose(input);
  free(random_string);
  file2hexfile(INPUT_UNHEXED_FILE_NAME, INPUT_FILE_NAME, "w");
  return remove(INPUT_UNHEXED_FILE_NAME);
}
