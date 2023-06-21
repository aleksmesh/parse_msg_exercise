#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "crc32.h"
#include "input_file_generator.h"
#include "process_messages.h"
#include "mes_hex.h"
#include "constants.h"

FILE* err_log = NULL;

int main() {
  err_log = fopen(ERR_LOG_FILE_NAME, "w");
  generate_input_file();
  if (NULL == err_log) {
    err_log = stderr;
    fprintf(err_log, "Can't open file %s\n", ERR_LOG_FILE_NAME);
  }
  if (NO_ERROR != hexfile2file(INPUT_FILE_NAME, INPUT_UNHEXED_FILE_NAME, 1)) {
    fprintf(err_log, "Can't convert hex_file %s\n", INPUT_FILE_NAME);
    return EXIT_FAILURE;
  }
  FILE* input = fopen(INPUT_UNHEXED_FILE_NAME, "rb");
  if (NULL == input) {
    fprintf(err_log, "Can't open file %s\n", INPUT_FILE_NAME);
    return EXIT_FAILURE;
  }
  FILE* output = fopen(OUTPUT_UNHEXED_FILE_NAME, "ab");
  if (NULL == output) {
    fprintf(err_log, "Can't open file %s\n", OUTPUT_FILE_NAME);
    return EXIT_FAILURE;
  }

  input_msg_t msg_in = {0};
  output_msg_t msg_out = {0};
  int msg_count = 0;
  while (0 < parse_next_message(input, &msg_in)) {
    if(!convert_message(&msg_in, &msg_out)) {
      continue;
    }
    save_message(output, &msg_out);
    ++msg_count;
  }
  fprintf(err_log, "msg count = %d\n", msg_count);
  fclose(input);
  fclose(output);

  file2hexfile(OUTPUT_UNHEXED_FILE_NAME, OUTPUT_FILE_NAME, "a");
  remove(OUTPUT_UNHEXED_FILE_NAME);
  remove(INPUT_UNHEXED_FILE_NAME);

  return EXIT_SUCCESS;
}
