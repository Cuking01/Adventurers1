#include "../head.h"

int main()
{
	Mem::SA allocor(Mem::ra);

	FILE*fp=fopen("test_in.c","r");

	wchar_t code[10000];
	s2 len=0;
	while(~fscanf(fp,"%lc",code+len))
		len++;
	code[len]=0;
	fclose(fp);

	Cscript::Compiler compiler(code,allocor);
	compiler.compile();

	printf(">>>>>>>>>>>%d\n",(s2)compiler.units.size());

	for(auto&unit:compiler.units)
	{
		printf("%4d %4d  ",unit->line,unit->col);
		std::wcout<<unit->what(compiler)<<'\n';
	}

	std::wcout<<"error:"<<"\n\n";

	for(auto&err:compiler.error)
	{
		std::wcout<<err<<'\n';
	}
	
}
