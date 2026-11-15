#include "consts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double learning_rate;
char *training_file = NULL;

void set_learning_rate(double given_lr)
{
    learning_rate = given_lr;
}

double get_learning_rate()
{
    return learning_rate;
}

void set_training_file(const char *tf)
{
    free(training_file);
    training_file = NULL;
    if (tf != NULL)
    {
        training_file = (char *)malloc(strlen(tf) + 5);
        if (training_file != NULL)
        {
            strcpy(training_file, tf);
        }
        else
        {
            perror("Errr, there is a problem with memory system...\n");
            return;
        }
    }
}

char *get_training_file()
{
    return training_file;
}
