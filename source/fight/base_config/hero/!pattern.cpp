#pragma once


//static_assert(0); //防止被include

hero[0x000]=
{
	.name=L"test_hero",
	.description=L"the hero for test",
	.tag={},
	.attribute_table=
	{
		.HP_lim={500,30},
		.MP_lim={100,0},
		.AP_lim={200,0},

		.HP_re={5,0.3},
		.MP_re={1,0},
		.AP_re={70,0},

		.MP_init={100,0},
		.AP_init={50,0},

		.ATK={40,2.4},
		
		.P_res={40,0.35},
		.M_res={25,0.2},

		.Crt={0,0},
		.CrtD={0,0},

		.exAPre_profit={0.8,0},
		.Con_res={0,0}
	},
	.skill=
	{
		//0,被动
		{
			.name=L"skill0",
			.description=L"skill0",
			.attribute_table={},
			.cd={1,0},
			.cd_init={1,0},
			.AP_use={0,0},
			.MP_use={0,0},
			.tag={},
			.fun_init=lambda_Skill_init
			{

			},
			//被动技能的check恒返回0
			.fun_check=lambda_Skill_check
			{
				return 0;
			},
			//被动技能的use恒为空指针.
			.fun_use=nullptr
		},
		//1,普攻
		{
			
		},
		//2,主动1
		{

		},
		//3,主动2
		{

		},
		//4,主动3
		{

		}
	}

};
