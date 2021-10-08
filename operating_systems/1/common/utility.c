#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utility.h"
#include "common.h"
#include "time.h"

void error_log(char* msg)
{
    printstr(stderrfd, "error\t");
    perror(msg);
    exit(-1);
}

int max(int x, int y) 
{ 
	return x > y ? x : y;
} 

int stoi(char* input)
{
  bool neg = 0;
  int integer = 0;
  int i;
  neg = input[0] == '-';
  
  for(i = neg ? 1 : 0; true; i++)
  {
    if(input[i] == '\0')
      break;
    if(input[i] >= '0' && input[i] <= '9')
      integer = integer * 10 + input[i] - '0';
    else 
        return 0;
  }
  return neg ? -integer : integer;
}

char* itos(int input)
{
    char* str = new_string_size(LEN);
    bool neg = input < 0;
    int index = 0;
    int i;
    input = neg ? -input : input;
    while(true) 
    {
        str[index++] = input % 10 + '0';
        input /= 10;
        if(input == 0)
        {
            if(neg)
                str[index++] = '-';
            str[index--] = '\0';
            break;
        }
    }
    for(i = 0; i < (index + 1) / 2; i++)
    {
        swap_in_char_array(str, i, index - i);
    }
    return str;
}

void swap_in_int_array(int* a, int i, int j)
{
  a[j] = a[i] ^ a[j];
  a[i] = a[i] ^ a[j];
  a[j] = a[i] ^ a[j];
}

void swap_in_char_array(char* a, int i, int j)
{
  a[j] = a[i] ^ a[j];
  a[i] = a[i] ^ a[j];
  a[j] = a[i] ^ a[j];
}

void printint(int fd, int number)
{
    char* buf;
    buf = itos(number);
    write(fd, buf, strlen(buf) + 1);
    free(buf);
}

void printstr(int fd, char* str)
{
    write(fd, str, strlen(str) + 1);
}

void server_log(char* msg)
{
    static time_t row_time;
    time(&row_time);
    static char* timestr;
    timestr = asctime(localtime(&row_time));
    timestr[strlen(timestr) - 1] = END; 
    printstr(stderrfd, "log\t");
    printstr(stderrfd, timestr);
    printstr(stderrfd, "\t");
    printstr(stderrfd, msg);
    printstr(stderrfd, "\n");
}

void server_log_response(char* msg)
{
    static time_t row_time;
    time(&row_time);
    static char* timestr;
    timestr = asctime(localtime(&row_time));
    timestr[strlen(timestr) - 1] = END; 
    printstr(stderrfd, "log\t");
    printstr(stderrfd, timestr);
    printstr(stderrfd, "\t");
    printstr(stderrfd, "response");
    printstr(stderrfd, "\n");
    printstr(stderrfd, msg);
    printstr(stderrfd, "\n");
}

void println(char* str)
{
    printstr(stdoutfd, str);
    printstr(stdoutfd, "\n");
}

void print_space(int fd, int sp)
{
    for(int i = 0; i < sp; i++)
        write(fd," ",2);
}

char* new_string_size(int size)
{
    char* str = (char*) malloc(size * sizeof(char));
    if(str == NULL)
        error_log("new_string");
    return str;
}

char* new_string(char* str)
{
    char* result = (char*) malloc(sizeof(char));
    result = strcpy(result, (const char*) str);
    return result;
}

bool equals(char* a, char* b)
{
    if(a == NULL || b == NULL)
        return false;
    return strcmp(a, b) == 0;
}