#pragma once



hero[0x101]=
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

		.ATK={80,4.8},
		
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
				//I0存储层数，I4存储上次受伤时间，U16存储清零事件id，D8存储每层减伤比例。
				//P0存timed_val_buff的地址

				auto&st=skill.st;
				auto&state=skill.state;
				auto&hero=state[skill.hid];

				auto*buff=hero.timed_val_buff_table.add({BT::正面,BT::强驱散},40,6,L"坚韧不屈");


				st.P0=(void*)&buff->st.I0;
				st.D8=(3+0.1*skill.level)*0.01;
				st.P16=(void*)buff;

				//给自身添加减伤buff
				hero.t_before_damaged.add(state.gen_id(),
				{
					{
						.st={.P0=(void*)&st},
					},
					lambda_Damage_Handler
					{
						damage.x.add(state.gen_id(),
						{
							{
								.st={.P0=(void*)st.P0}
							},
							lambda_Buff
							{
								auto*p=(Arg_t_7*)st.P0;
								bh.subp*=1.0-p->D8*(*(s2*)p->P0);
								return 0;
							}
						});
						return 0;
					}
				});

				//受伤扳机
				hero.t_damaged.add(state.gen_id(),
				{
					{
						.st={.P0=st.P16}
					},
					lambda_Damage_Handler
					{
						if(damage.tag(DT::直接))
						{
							auto*p=(State::Timed_Val_Buff*)st.P0;
							p->add(1);
						}
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
			.name=L"普通攻击",
			.description=L"对单个目标造成(1+0.02L)*ATK的物理伤害",
			.attribute_table={},
			.cd={0.5,0},
			.cd_init={0,0},
			.AP_use={100,-0.5},
			.MP_use={0,0},
			.tag=
			{
				.target_check=1,
				.group_restrict=1,
				.target_group=1,
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
			.name=L"冲锋斩",
			.description=L"冲向目标英雄，借势斩出一击，造成20+8L+(1+0.02L)*ATK的物理伤害，并削弱其(20+2L)%的护甲，持续(3+0.1L)秒",
			.attribute_table={},
			.cd={4,-0.1},
			.cd_init={0,0},
			.AP_use={120,-1},
			.MP_use={0,0},
			.tag=
			{
				.target_check=1,
				.group_restrict=1,
				.target_group=1,
			},
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=
			lambda_Skill_use
			{
				auto&state=skill.state;
				auto&hero=state[skill.hid];

				report_A对B使用了X(skill.hid,State::Hid(arg.I0),L"冲锋斩");

				auto&damage=hero.make_damage
				(
					arg.I0,
					20+8*skill.level+hero.ATK()*(1+0.02*skill.level),
					{DT::直接,DT::物理,DT::单体}
				);
				damage.addition.add(state.gen_id(),
				{
					{
						.st={.I0=skill.level}
					},
					lambda_Damage_Handler
					{
						auto&hero=state[damage.to];
						u2 id=state.gen_id();
						report_X(fmt::format(L"{:s} 的护甲降低了\n",hero.report_name()));
						hero.P_res.add(id,
						{
							{
								.st={.D0=0.2+st.I0*0.02},
								.tag={BT::负面,BT::中驱散},
								.hid=damage.to,
								.name=L"比例破甲"
							},
							lambda_Buff
							{
								bh.subp*=1-st.D0;
								return 0;
							}
						});

						Arg_t_5 event_arg;
						event_arg.U0=id;
						event_arg.I4=(s2)damage.to;
						state.event_queue.add(state.gen_id(),30+st.I0,
						{
							{
								.st=event_arg
							},
							lambda_Event
							{
								state[Hid(st.I4)].P_res.erase(st.U0);
								return 0;
							}
						});
						return 0;
					}
				});

				damage.act();
				damage.destroy();
			}
		},
		//3,主动2
		{
			.name=L"陷阵",
			.description=L"于敌阵之中咆哮，吸引敌方攻击，自身获得嘲讽，持续2+0.2L秒",
			.attribute_table={},
			.cd={6,-0.1},
			.cd_init={0,0},
			.AP_use={50,-1},
			.MP_use={0,0},
			.tag={},
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				auto&state=skill.state;
				auto&hero=state[skill.hid];

				report_A使用了X(skill.hid,L"陷阵");
				s2 L=skill.level;
				hero.en_嘲讽(20+2*L);
			}
		},
		//4,主动3
		{
			.name=L"战气罡风",
			.description=L"释放积蓄已久的战气，凝聚在武器之上并挥出，对最多三个连续目标造成(0.4+0.015L+坚韧层数*(0.1+0.015L)*ATK的物理伤害，并消耗所有坚韧层数\n参数格式:SH0存最左英雄位置，可以不在0~4内，然后对I0~I0+2的英雄造成伤害，不合法位置不会产生伤害",
			.attribute_table={},
			.cd={8,-0.2},
			.cd_init={1,-0.1},
			.AP_use={100,-1},
			.MP_use={0,0},
			.tag={},
			.fun_init=nullptr,
			.fun_check=nullptr,
			.fun_use=lambda_Skill_use
			{
				auto&state=skill.state;
				auto&hero=state[skill.hid];


				s2 L=skill.level;
				auto&I0=*(s2*)hero.skill[0].st.P0;
				s1 pos=arg.SH2;

				report_A于位置B使用了X(skill.hid,pos,L"战气罡风");
				for(s1 i=0;i<3;i++)
				{
					s1 tp=pos+i;
					if(tp>=0&&tp<5&&state[skill.hid.gid^1][tp].alive)
						hero.cause_damage
						(
							{(s1)(skill.hid.gid^1),tp},
							(0.4+0.02*L+(0.1+0.02*L)*I0)*hero.ATK(),
							{DT::直接,DT::物理,DT::群体}
						);
				}
				I0=0;
			}
		}
	}

};
