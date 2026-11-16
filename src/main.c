#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "encode.h"
#include "hashmap.h"
#include "init.h"

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    init(argc, argv);

    char *data_line = malloc(ENCODE_BUF_SIZE + 1);
    HashMap *number_list = hashmap_create();

    assert(number_list != NULL);

    // cut input to map
    make_dictV(data_line, number_list);

    hashmap_destroy(number_list, NULL);
    free(data_line);
    encode_end();
    return 0;
}
