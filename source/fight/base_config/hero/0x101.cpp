#pragma once


//static_assert(0); //防止被include

hero[0x000]=
{
	.name=L"王者铜",
	.description=L"",
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
			.name=L"坚韧不屈",
			.description=L"每次受到直接伤害后，获得一层坚韧不屈效果，英雄获得((3+0.1*L)*层数)%的伤害减免，最多叠加5层，4秒内不受伤害则层数清零",
			.attribute_table={},
			.cd={1,0},
			.cd_init={1,0},
			.AP_use={0,0},
			.MP_use={0,0},
			.tag={},
			.fun_init=lambda_Skill_init
			{
				//I0存储层数，I4存储上次受伤时间，D8存储每层减伤比例。
				st.I0=0;
				st.I4=0;
				st.D8=0.01*(3+0.1*skill.level);
				auto&state=skill.state;
				auto&hero=state[skill.hid];

				hero.t_damaged.add(state.gen_id(),
				{
					{{.P0=(void*)&st},{BT::正面,BT::不可驱散}},
					lambda_Damage_Handler
					{
						damage.x.add(state.gen_id(),
						{
							{{.P0=st.P0}},
							lambda_Buff
							{
								auto*p=(Arg_t_6*)st.P0;
								bh.gsub*=(1-p->D8*p->I0);
								return 0;
							}
						});
						return 0;
					}
				});
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
				.target_group=1,
				.auto_consume=1
			},
			.fun_init=lambda_Skill_init{},
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				auto&state=skill.state;
				auto&hero=state[skill.hid];

				report_A对B使用了X(skill.hid,State::Hid(arg.I0),L"普通攻击");

				hero.cause_damage
				(
					arg.I0,
					hero.ATK()*(1+0.02*skill.level),
					{DT::直接,DT::物理,DT::单体,DT::普攻,0,0}
				);

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
