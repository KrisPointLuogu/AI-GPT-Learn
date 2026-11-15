#include "encode.h"
#include "consts.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static FILE *fp = NULL;

void encode_init()
{
    if (fp != NULL)
        return;
    fp = fopen(get_training_file(), "r");
    if (fp == NULL)
    {
        perror("Well, there is a problem with the File IO.\n");
        perror("Please check the permission or what.\n");
        exit(1);
    }
}

char *encode_a_line(char *buf, int buf_size)
{
    // char *buf = (char *)malloc((256) * sizeof(char) + 1); /* BE CAREFUL STACK OVERFLOW */
    if (fgets(buf, (buf_size), fp) != NULL)
    {
        return buf;
    }
    // End
    return NULL;
}

void encode_end()
{
    if (fp == NULL)
    {
        perror("Why the fp is the NULL?\n");
        exit(1);
    }
    fclose(fp);
    fp = NULL;
}

void encode_set_num(HashMap *hmap, char *data_line)
{
    static int __encode_number_list_cnt = 0;
    int data_line_len = strlen(data_line);
    for (int str_idx = 0; str_idx < data_line_len; str_idx++)
    {
        char key[2] = {data_line[str_idx], '\0'};
        if (!hashmap_contains(hmap, key))
        {
            hashmap_put(hmap, key, (void *)(intptr_t)(++__encode_number_list_cnt), NULL);
        }
    }
}
