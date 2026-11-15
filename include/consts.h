#ifndef CONSTS_H
#define CONSTS_H

extern double learning_rate;
void set_learning_rate(double given_lr);
double get_learning_rate();

extern char *training_file;
void set_training_file(const char *tf);
char *get_training_file();

#endif // !CONSTS_H