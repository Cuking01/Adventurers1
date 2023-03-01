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
	State::State state(gc,gc,0ull,allocor);
	state.start();

	//printf("%f\n",state.hero({0,0}).HP_lim.x);
	//printf("%f\n",state.hero({0,0}).HP_lim());
	FILE*fp=fopen("fight_log.txt","w");
	state.report.save(fp);
	puts("*****");
}
