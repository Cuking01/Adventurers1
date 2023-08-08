#include<stdio.h>
#include<stdlib.h>

int main(int argc,char**argv)
{
	if(argc==3)
	{
		char tmp[10000];
		sprintf(tmp,"g++ %s -O2 -o %s -s -std=c++20 -Wl,--stack=0x10000000 -Wall -Wextra -fno-strict-aliasing -Wno-missing-field-initializers -Wno-type-limits -Wno-parentheses",argv[1],argv[2]);
		system(tmp);
	}
	else
	{
		puts("\nmake error.\n");
	}
}
