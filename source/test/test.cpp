#include "../head.h"

int main()
{
	setlocale(LC_ALL,"");
	Mem::SA allocor(Mem::ra);
	
	using namespace Fight;

	Player_Config::Group gc=
	{
		.hero=
		{
			{
				.id=0,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			}
		},

		.script=
		{
			lambda_Script_init{return 0;},
			lambda_Script_act
			{
				
				return 0;
			}
		}

	};
	State::State state(gc,gc,0ull,allocor);
	//state.start();
	wchar_t tmp[30000];


	state.report.write(fmt::format(L"一二三四五"));

	state.report.save(tmp);
	
	wprintf(L"%lc\n",tmp[0]);
	wprintf(L"%ls\n",tmp);
	int len=state.report.length();
	for(int i=0;i<=len;i++)
		printf("%d\n",(int)tmp[i]);

	puts("*****");
	//printf("%f\n",state.hero({0,0}).HP_lim.x);
	//printf("%f\n",state.hero({0,0}).HP_lim());
	FILE*fp=fopen("fight_log.txt","w");
	state.report.save(fp);
	puts("*****");
}
