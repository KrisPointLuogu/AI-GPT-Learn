#include "consts.h"
double learning_rate;

void set_learning_rate(double given_lr)
{
    learning_rate = given_lr;
}

double get_learning_rate()
{
    return learning_rate;
}
