#include "encode.h"
#include "consts.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

static FILE *fp = NULL;

void encode_init()
{
    if (fp != NULL)
        return;
    fp = fopen(get_training_file(), "r");
    assert(fp != NULL);
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
    assert(fp != NULL);
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

static void print_entry(const char *k, void *v, void *ctx)
{
    (void)ctx;
    printf("%-12s => %ld\n", k, (long)(intptr_t)v);
}

void make_dictV(char *data_line, HashMap *number_list)
{
    // make dict
    while ((encode_a_line(data_line, ENCODE_BUF_SIZE)) != NULL)
        encode_set_num(number_list, data_line);

    hashmap_foreach(number_list, print_entry, NULL);
}