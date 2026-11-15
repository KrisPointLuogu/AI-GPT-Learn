#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arginit.h"
#include "consts.h"
#include "encode.h"
#include "hashmap.h"

static void print_entry(const char *k, void *v, void *ctx)
{
    (void)ctx;
    printf("%-12s => %ld\n", k, (long)(intptr_t)v);
}

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    arg_init(argc, argv);

    set_training_file("./data/shakespeare.txt");
    set_learning_rate(0.1);

    printf("Training from: %s, learning rate is: %f\n", get_training_file(), get_learning_rate());

    encode_init();

    char *data_line = malloc(ENCODE_BUF_SIZE + 1);
    HashMap *number_list = hashmap_create();

    if (number_list == NULL)
    {
        perror("Fuck memory problems\n");
        exit(1);
    }

    // make dict
    while ((encode_a_line(data_line, ENCODE_BUF_SIZE)) != NULL)
        encode_set_num(number_list, data_line);

    hashmap_foreach(number_list, print_entry, NULL);

    hashmap_destroy(number_list, NULL);
    free(data_line);
    encode_end();

    return 0;
}
