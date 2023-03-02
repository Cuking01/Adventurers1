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
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{5},{5},{5},{5},{5}},
			}
		},

		.script=
		{
			lambda_Script_init{return 0;},
			lambda_Script_act
			{
				s1 target=-1;
				for(s1 pos=0;pos<5;pos++)
					if(state[gid^1][pos].alive)
					{
						target=pos;
						break;
					}
				if(target==-1)
				{
					skill_id={-1,-1,{}};
					return 0;
				}
				for(s1 pos=0;pos<5;pos++)
				{
					auto& hero=state[gid][pos];
					Arg_t_6 arg;
					arg.SH0=gid^1;
					arg.SH2=target;
					if(hero.skill[1].check(arg)==0)
					{
						skill_id={pos,1,arg};
						return 0;
					}
				}
				skill_id={-1,-1,{}};
				return 0;
			}
		}

	};
	Player_Config::Group gc2=gc;
	//for(s2 i=0;i<5;i++)gc2.hero[i].level=30;

	int t0=clock();
	for(int i=0;i<1000;i++)
	{
		State::State state(gc,gc2,0ull,allocor);
		state.start();
	}
	State::State state(gc,gc2,0ull,allocor);
	state.start();
	
	int t1=clock();

	FILE*fp=fopen("fight_log.txt","w");
	for(int i=0;i<10;i++)
		state.report.save(fp);
	
	int t2=clock();
	printf("%d %d %d\n",t1-t0,t2-t1,t2);
	puts("*****");
}
