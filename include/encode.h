#ifndef ENCODE_H
#define ENCODE_H

#include "hashmap.h"

#define ENCODE_BUF_SIZE 256

void encode_init();
char *encode_a_line(char *buf, int buf_size);
void encode_end();

void encode_set_num(HashMap *hmap, char *data_line);

#endif // !ENCODE_H