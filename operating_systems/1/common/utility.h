#ifndef UTILITY_H
#define UTILITY_H
#include "common.h"

char* new_string_size(int size);
char* new_string(char* str);
void swap_in_char_array(char* a, int i, int j);
void swap_in_int_array(int* a, int i, int j);
void print_space(int fd, int sp);
void println(char* str);
void printstr(int fd,char* str);
void printint(int fd, int number);
char* itos(int input);
int stoi(char* input);
void error_log(char* msg);
int max(int x, int y);
bool equals(char* a, char* b);
void sever_log(char* msg);
#endif