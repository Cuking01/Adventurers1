#pragma once


hero[0x102]=
{
	.name=L"冰棍",
	.description=L"强大的冰系魔法师，拥有召唤巨大冰棍的恐怖力量，每逢其释放大招，人们常惊叹：真是冰天下之大棍！",
	.tag={},
	.attribute_table=
	{
		.HP_lim={400,24},
		.MP_lim={500,32},
		.AP_lim={150,0},

		.HP_re={3,0.18},
		.MP_re={10,0.7},
		.AP_re={60,0},

		.MP_init={500,32},
		.AP_init={40,0},

		.ATK={20,1.1},
		
		.P_res={30,0.2},
		.M_res={25,0.2},

		.Crt={0,0},
		.CrtD={0,0},

		.exAPre_profit={0.7,0},
		.Con_res={0,0}
	},
	.skill=
	{
		//0,被动
		{
			.name=L"彻骨之寒",
			.description=L"冰棍的主动技能命中目标时可使其获得\"冰寒\"层数，每个英雄最多十层，持续3+0.2L秒。受冰寒影响时，每层冰寒降低(1+0.1L)%的敏捷。当具有\"冰寒\"的英雄死亡时，冰棍可以汲取其中的力量并恢复法力值，每层可以恢复2%的法力值。",
			.attribute_table={},
			.cd={1,0},
			.cd_init={1,0},
			.AP_use={0,0},
			.MP_use={0,0},
			.tag={},
			.fun_init=lambda_Skill_init
			{
				//用hero.st.I0存储应该附加几层冰寒
				auto&state=skill.state;
				auto&hero=state[skill.hid];
				auto&st=skill.st;
				for(s1 pos=0;pos<5;pos++)
				{
					auto&hero=state[skill.hid.gid^1][pos];
					
					st.P[pos]=(void*)hero.timed_val_buff_table.add({BT::负面,BT::中驱散},30+skill.level,10,L"冰寒");
					Arg_t_5 buff_st;
					buff_st.P0=(void*)&(((State::Timed_Val_Buff*)st.P[pos])->st.I0);
					buff_st.D8=(1+0.1*skill.level)*0.01;
					hero.AP_re.add(state.gen_id(),
					{
						{.st=buff_st},
						lambda_Buff
						{
							bh.subp*=(1-st.D8*(*(s2*)st.P0));
							return 0;
						}
					});
				}

				hero.t_damage.add(state.gen_id(),
				{
					{
						//P0指向冰寒层数，P8指向st
						.st={.P0=(void*)&hero.st.I0,.P8=(void*)&st}
					},
					lambda_Damage_Handler
					{
						damage.addition.add(state.gen_id(),
						{
							{
								.st={.P0=st.P0,.P8=(void*)((Arg_t_7*)st.P8)->P[damage.to.pos]}
							},
							lambda_Damage_Handler
							{
								s2 x=*(s2*)st.P0;
								if(x>0)
									((State::Timed_Val_Buff*)st.P8)->add(x);
								return 0;
							}				
						});
						return 0;
					}
				});

				hero.t_use_skill.add(state.gen_id(),
				{
					{},
					lambda_Skill_Handler
					{
						s2 x;
						if(sid==2||sid==4)x=2;
						else if(sid==3)x=1;
						else x=0;
						state[hid].st.I0=x;
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
					{DT::直接,DT::物理,DT::单体,DT::普攻,DT::可暴击}
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
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{

			}
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
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				
			}
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
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				
			}
		}
	}

};
