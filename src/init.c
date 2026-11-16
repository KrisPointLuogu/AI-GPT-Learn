#include <stdio.h>
#include "arginit.h"
#include "consts.h"
#include "encode.h"
#include "init.h"

void init(int argc, const char **argv)
{
    arg_init(argc, argv);

    set_training_file("./data/shakespeare.txt");
    set_learning_rate(0.1);

    printf("Training from: %s, learning rate is: %f\n", get_training_file(), get_learning_rate());

    encode_init();
}