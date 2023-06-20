#include "mes_hex.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "constants.h"

int file2hexfile(const char* input_name, const char* output_name, const char* out_open_mode)
{
  FILE* in = fopen(input_name, "r");
  if (NULL == in) {
    fprintf(err_log, "Error open file %s to hex convert\n", input_name);
    return ERR_OPEN_FILE;
  }
  FILE* out = fopen(output_name, out_open_mode);
  if (NULL == out) {
    fprintf(err_log, "Error open file %s to hex convert\n", output_name);
    fclose(in);
    return ERR_OPEN_FILE;
  }
  int ch;
  while (EOF != (ch = fgetc(in))) {
    fprintf(out, "%02X", ch);
  }
  fclose(in);
  fclose(out);
  return NO_ERROR;
}

int hexfile2file(const char* input_name, const char* output_name, int check_file)
{
  FILE* in = fopen(input_name, "r");
  if (NULL == in) {
    fprintf(err_log, "Error open file %s from hex convert\n", input_name);
    return ERR_OPEN_FILE;
  }
  FILE* out = fopen(output_name, "w");
  if (NULL == out) {
    fprintf(err_log, "Error open file %s from hex convert\n", "data_in_norm.txt");
    fclose(in);
    return ERR_OPEN_FILE;
  }
  int ch;
  int counter = 0;
  char one_hex[3] = {0,0,0};
  int pos = 0;
  while (EOF != (ch = fgetc(in))) {
    if (0 != check_file && 0 == isxdigit(ch)) {
      fprintf(err_log, "Non hex digit in position = %d.\n", pos );
    }
    ++pos;
    one_hex[counter] = ch;
    ++counter;
    if (2 == counter) {
      counter = 0;
      char norm_ch = strtol(one_hex, NULL, 16);
      fputc(norm_ch, out);
    }
  }
  fclose(in);
  fclose(out);
  return NO_ERROR;
}
