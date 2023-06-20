#include "process_messages.h"
#include "crc32.h"
#include "constants.h"

#include <string.h>

int parse_next_message(FILE* input, input_msg* msg )
{
  char chunk[START_LENGTH];
  int res = fread(chunk, 1, START_LENGTH, input);
  if (START_LENGTH != res) {
    return 0 == feof(input) && 0 == ferror(input);
  }
  memset(msg->msg, 0, sizeof(msg->msg));
  while (0 == feof(input) && 0 == ferror(input)) {
    if (0 != memcmp(START_MSG_IDENT, chunk, START_LENGTH)) {
      memmove(chunk, chunk + 1, START_LENGTH - 1);
      res = fread(chunk + START_LENGTH - 1, 1, 1, input);
      fprintf(err_log, "Data file error!\n");
      continue;
    }
    if (1 != fread(&msg->type, 1, 1, input )) {
      fprintf(err_log, "Error read msg type\n");
      break;
    }
    if (1 != fread(&msg->length, 1, 1, input )) {
      fprintf(err_log, "Error read msg length\n");
      break;
    }
    if (msg->length != fread(msg->msg, 1, msg->length, input)) {
      fprintf(err_log, "Error read msg\n");
      break;
    }
    if (1 != fread(&msg->crc32, CRC32_SIZE, 1, input)) {
      fprintf(err_log, "Error read msg crc32\n");
      break;
    }
    if (START_LENGTH != fread(chunk, 1, START_LENGTH, input)) {
      fprintf(err_log, "Error read mask start\n");
      break;
    }
    if (0 != memcmp(START_MASK_IDENT, chunk, START_LENGTH)) {
      fprintf(err_log, "Unk err2!!! %s\n", chunk);
      continue;
    }
    if (1 != fread(&msg->mask, 4, 1, input)) {
      fprintf(err_log, "Error read mask\n");
      break;
    }
    break;
  }
  return (0 == feof(input) && 0 == ferror(input));
}

int convert_message(input_msg* msg_in, output_msg* msg_out)
{
  if (crc32(msg_in->msg, msg_in->length) != msg_in->crc32) {
    fprintf(err_log, "msg crc32 error!");
    return 0;
  }
  int pad = CHUNK_SIZE - msg_in->length%CHUNK_SIZE;
  int tet_count = (msg_in->length + pad)/CHUNK_SIZE;

  memset(msg_out->msg, 0, sizeof(msg_out->msg));
  memset(msg_out->msg_masked, 0, sizeof(msg_out->msg_masked));
  msg_out->type = msg_in->type;
  msg_out->length = msg_in->length;
  memcpy(msg_out->msg, msg_in->msg, msg_in->length);
  msg_out->crc32 = msg_in->crc32;
  msg_out->length_mod = msg_in->length + pad;

  for (int i = 0; i < tet_count; ++i) {
    uint32_t masked_chunk;
    memcpy(&masked_chunk, msg_in->msg + i*CHUNK_SIZE, CHUNK_SIZE);
    //TODO replace operation '|=' with pointer to function
    masked_chunk |= msg_in->mask;
    memcpy(msg_out->msg_masked + i*CHUNK_SIZE, &masked_chunk, CHUNK_SIZE);
  }
  msg_out->crc32_mod = crc32(msg_out->msg_masked, msg_out->length_mod);
  return 1;
}

int save_message(FILE* output, output_msg* msg)
{
  fputc(msg->type, output);
  fputc(msg->length, output);
  fwrite(msg->msg, 1, msg->length, output);
  putw(msg->crc32, output);
  fputc(msg->length_mod, output);
  fwrite(msg->msg_masked, 1, msg->length_mod, output);
  putw(msg->crc32_mod, output);

  return 0;
}
