#include <stdio.h>
#include "arginit.h"
#include "library/argparse.h"
#include "consts.h"

static float learning_rate_opt;

const char *const usage_arg[] = {
    "\n    set_learnrate [number(float)]",
    NULL,
};

struct argparse_option options_arg[] = {
    OPT_HELP(),
    OPT_GROUP("Basic:"),
    OPT_FLOAT('r', "learning_rate", &learning_rate_opt, "Set learning rate equ [number float].", NULL, 0, 0),
    OPT_END(),
};

struct argparse argparse_arg;

void arg_init(int argc, const char **argv)
{
    learning_rate_opt = (float)learning_rate;
    argparse_init(&argparse_arg, options_arg, usage_arg, 0);
    argparse_parse(&argparse_arg, argc, argv);
    set_learning_rate((double)learning_rate_opt);
}