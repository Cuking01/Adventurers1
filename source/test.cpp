#include "head.h"

int main()
{
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
			lambda_Script_act{return 0;}
		}

	};

	State::State_A state_a(allocor);

	State::State state(gc,gc,0ull,state_a);
	
	DS::Set<int>::A allocor3(allocor);
	DS::Set<int> a(allocor3);
	DS::Set<int> b(a);
}
