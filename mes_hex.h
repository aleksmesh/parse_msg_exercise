#ifndef MES_HEX_H
#define MES_HEX_H

int file2hexfile(const char* input_name, const char* output_name, const char* out_open_mode);
int hexfile2file(const char* input_name, const char* output_name, int check_file);

#endif
