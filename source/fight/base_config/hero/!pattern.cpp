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
			.name=L"skill1",
			.description=L"skill1",
			.attribute_table={},
			.cd={0.5,0},
			.cd_init={0,0},
			.AP_use={100,-0.5},
			.MP_use={0,0},
			.tag=
			{
				.consumption_check=1,
				.sp_state_check=1,
				.target_check=1,
				.group_restrict=1,
				.target_group=1
			},
			.fun_init=lambda_Skill_init{},
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				auto&state=skill.state;
				auto&hero=state[skill.hid];
				auto&damage=hero.make_damage
				(
					arg.I0,
					hero.ATK()*(1+0.02*skill.level),
					{DT::直接,DT::物理,DT::单体,DT::普攻,0,0}
				);
				damage.act();
			}
		},
		//2,主动1
		{
			.name=L"skill2",
			.description=L"skill2",
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
		//3,主动2
		{
			.name=L"skill3",
			.description=L"skill3",
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
		//4,主动3
		{
			.name=L"skill4",
			.description=L"skill4",
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
		}
	}

};
