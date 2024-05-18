#include "../head.h"

struct A
{
    int x,y;
    A(int x,int y):x(x),y(y){}
    virtual ~A(){}
};

struct B:A
{
    int z;
    B(int x,int y,int z):A(x,y),z(z){}
    virtual ~B(){}
};

struct C:B
{
    int a,b;
    C(int x,int y,int z,int a,int b):B(x,y,z),a(a),b(b){}
    virtual ~C(){}
};

int main()
{
	Mem::SA allocor(Mem::ra);


	puts("*****");
	setlocale(LC_ALL,"chinese");
	puts("一二三");
	
	
	using namespace Fight;

	Player_Config::Group 纯王者铜= 
	{
		.hero=
		{
			{
				.id=0x101,.level=120,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			}
		},

		.script=
		{
			lambda_Script_init
			{
				for(s2 i=0;i<5;i++)
					st.SH[i]=0;
				return 0;
			},
			lambda_Script_act
			{
				/*
					策略:(优先级按顺序由高到低)
					1.如果己方有人嘲讽刚刚结束且能释放技能3，则释放。
					2.如果己方当前无嘲讽保护，则在能释放技能2的英雄中，挑选生命值最大者释放
					3.如果有英雄能释放技能1，则对对方生命值最低者释放，如果有嘲讽保护，则在嘲讽者中挑选生命值最低的释放
					4.如果有英雄能释放普攻，且当前AP快满了，则对生命值最低者释放普攻。
					5.什么都不做
				*/

				auto&g=state[gid];
				auto&G=state[gid^1];

				auto get_target=[&](s2 flag=1)->s1
				{
					s2 cc=0;
					s1 target=-1;
					for(s1 pos=0;pos<5;pos++)
						if(G[pos].alive)
						{
							if(flag&&G[pos].嘲讽()>0)
							{
								if(cc==0||G[pos].HP<G[target].HP)target=pos;
								cc++;
							}
							else if(cc==0)
							{
								if(target==-1||G[pos].HP<G[target].HP)target=pos;
							}
						}
					return target;
				};

				s1 target=get_target();
				s1 Gid=gid^1;
				if(target==-1)
				{
					skill_id={-1};
					return 0;
				}
				auto 策略1=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					{
						if(st.SH[pos]&&state.time-st.SH[pos]<=50&&g[pos].嘲讽()<0.001&&g[pos].skill[4].check({.SH2=0})==0)
						{
							st.SH[pos]=0;
							s1 target=-1,num=0;
							for(s1 pos=0;pos<3;pos++)
							{
								s1 tc=G[pos].alive+G[pos+1].alive+G[pos+2].alive;
								if(tc>num)
								{
									num=tc;
									target=pos;
								}
							}
							skill_id={pos,4,{.SH2=target}};
							return 1;
						}
					}

					return 0;
				};

				auto 策略2=[&]()->s2
				{
					s2 cc=0;
					for(s1 pos=0;pos<5;pos++)
						if(g[pos].alive&&g[pos].嘲讽()>0)
							cc++;
					if(!cc)
					{
						s1 hpos=-1;
						f3 mxhp=0;
						for(s1 pos=0;pos<5;pos++)
						{
							if(g[pos].skill[3].check({})==0)
								if(g[pos].HP>mxhp)
								{
									mxhp=g[pos].HP;
									hpos=pos;
								}
						}
						if(~hpos)
						{
							skill_id={hpos,3,{}};
							st.SH[hpos]=state.time;
							return 1;
						}
					}

					return 0;
				};

				auto 策略3=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(g[pos].skill[2].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,2,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略4=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(g[pos].AP+10.0>g[pos].AP_lim()&&g[pos].skill[1].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,1,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略5=[&]()->s2
				{
					skill_id={-1};
					return 1;
				};

				策略1()||策略2()||策略3()||策略4()||策略5();
				return 0;
			}
		}

	};
	Player_Config::Group 纯冰棍= 
	{
		.hero=
		{
			{
				.id=0x102,.level=120,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x102,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x102,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x102,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x102,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			}
		},

		.script=
		{
			lambda_Script_init
			{
				st.I0=-10;
				return 0;
			},
			lambda_Script_act
			{
				/*
					策略:(优先级按顺序由高到低)
					1.如果能命中至少三个，有大招直接放，但不同角色连续放要错开0.5秒。
					2.如果能一次命中两个目标，则释放冰雨术,挑选能命中目标数最多的地方释放。
					3.否则对生命值最低者使用寒冰箭
					4.如果AP充足，释放普通攻击
					5.什么都不做
				*/

				auto&g=state[gid];
				auto&G=state[gid^1];

				auto get_target=[&](s2 flag=1)->s1
				{
					s2 cc=0;
					s1 target=-1;
					for(s1 pos=0;pos<5;pos++)
						if(G[pos].alive)
						{
							if(flag&&G[pos].嘲讽()>0)
							{
								if(cc==0||G[pos].HP<G[target].HP)target=pos;
								cc++;
							}
							else if(cc==0)
							{
								if(target==-1||G[pos].HP<G[target].HP)target=pos;
							}
						}
					return target;
				};

				s1 target=get_target();
				s1 Gid=gid^1;
				if(target==-1)
				{
					skill_id={-1};
					return 0;
				}
				auto 策略1=[&]()->s2
				{
					s2 cnt=0;
					for(s1 pos=0;pos<5;pos++)
						cnt+=G[pos].alive;


					if(cnt>=3&&state.time-st.I0>=8)
					{
						for(s1 pos=0;pos<5;pos++)
						{
							if(g[pos].skill[4].check({})==0)
							{
								skill_id={pos,4,{}};
								st.I0=state.time;
								return 1;
							}
						}
					}

					return 0;
				};

				auto 策略2=[&]()->s2
				{
					s2 mxnum=0;
					s1 mxpos;
					s2 cnt=0;
					for(s1 pos=0;pos<3;pos++)
					{
						cnt=G[pos].alive+G[pos+1].alive+G[pos+2].alive;
						if(cnt>mxnum)
						{
							mxnum=cnt;
							mxpos=pos;
						}
					}

					if(mxnum<2)
						return 0;
					
					Arg_t_6 arg={.SH2=mxpos};
					for(s1 pos=0;pos<5;pos++)
					{
						if(!(g[pos].skill[4].CD<0.0001&&g[pos].AP<135)&&g[pos].skill[3].check(arg)==0)
						{
							skill_id={pos,3,arg};
							return 1;
						}
					}

					return 0;
				};

				auto 策略3=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(!(g[pos].skill[4].CD<0.0001&&g[pos].AP<130)&&g[pos].skill[2].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,2,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略4=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(g[pos].AP+10.0>g[pos].AP_lim()&&g[pos].skill[1].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,1,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略5=[&]()->s2
				{
					skill_id={-1};
					return 1;
				};

				策略1()||策略2()||策略3()||策略4()||策略5();
				return 0;
			}
		}

	};
	Player_Config::Group 混编= 
	{
		.hero=
		{
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			},
			{
				.id=0x101,.level=60,
				.equipment={{0,10},{0,10},{0,10}},
				.skill={{0},{0},{0},{5},{10}}
			}
		},

		.script=
		{
			lambda_Script_init
			{
				for(s2 i=0;i<5;i++)
					st.SH[i]=0;
				return 0;
			},
			lambda_Script_act
			{
				/*
					策略:(优先级按顺序由高到低)
					1.如果己方有人嘲讽刚刚结束且能释放技能3，则释放。
					2.如果己方当前无嘲讽保护，则在能释放技能2的英雄中，挑选生命值最大者释放
					3.如果有英雄能释放技能1，则对对方生命值最低者释放，如果有嘲讽保护，则在嘲讽者中挑选生命值最低的释放
					4.如果有英雄能释放普攻，且当前AP快满了，则对生命值最低者释放普攻。
					5.什么都不做
				*/

				auto&g=state[gid];
				auto&G=state[gid^1];

				auto get_target=[&](s2 flag=1)->s1
				{
					s2 cc=0;
					s1 target=-1;
					for(s1 pos=0;pos<5;pos++)
						if(G[pos].alive)
						{
							if(flag&&G[pos].嘲讽()>0)
							{
								if(cc==0||G[pos].HP<G[target].HP)target=pos;
								cc++;
							}
							else if(cc==0)
							{
								if(target==-1||G[pos].HP<G[target].HP)target=pos;
							}
						}
					return target;
				};

				s1 target=get_target();
				s1 Gid=gid^1;
				if(target==-1)
				{
					skill_id={-1};
					return 0;
				}
				auto 策略1=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					{
						if(st.SH[pos]&&state.time-st.SH[pos]<=50&&g[pos].嘲讽()<0.001&&g[pos].skill[4].check({.SH2=0})==0)
						{
							st.SH[pos]=0;
							s1 target=-1,num=0;
							for(s1 pos=0;pos<3;pos++)
							{
								s1 tc=G[pos].alive+G[pos+1].alive+G[pos+2].alive;
								if(tc>num)
								{
									num=tc;
									target=pos;
								}
							}
							skill_id={pos,4,{.SH2=target}};
							return 1;
						}
					}

					return 0;
				};

				auto 策略2=[&]()->s2
				{
					s2 cc=0;
					for(s1 pos=0;pos<5;pos++)
						if(g[pos].alive&&g[pos].嘲讽()>0)
							cc++;
					if(!cc)
					{
						s1 hpos=-1;
						f3 mxhp=0;
						for(s1 pos=0;pos<5;pos++)
						{
							if(g[pos].skill[3].check({})==0)
								if(g[pos].HP>mxhp)
								{
									mxhp=g[pos].HP;
									hpos=pos;
								}
						}
						if(~hpos)
						{
							skill_id={hpos,3,{}};
							st.SH[hpos]=state.time;
							return 1;
						}
					}

					return 0;
				};

				auto 策略3=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(g[pos].skill[2].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,2,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略4=[&]()->s2
				{
					for(s1 pos=0;pos<5;pos++)
					if(g[pos].AP+10.0>g[pos].AP_lim()&&g[pos].skill[1].check({.SH0=Gid,.SH2=target})==0)
					{
						skill_id={pos,1,{.SH0=Gid,.SH2=target}};
						return 1;
					}
					return 0;
				};

				auto 策略5=[&]()->s2
				{
					skill_id={-1};
					return 1;
				};

				策略1()||策略2()||策略3()||策略4()||策略5();
				return 0;
			}
		}

	};

	//for(s2 i=0;i<5;i++)gc2.hero[i].level=30;

	int t0=clock();
	// for(int i=0;i<1000000;i++)
	// {
	// 	State::State state(gc,gc2,0ull,allocor);
	// 	state.start();
	// }
	State::State state(纯王者铜,纯冰棍,0ull,allocor);

	printf("sizeof(State):%d\n",(int)sizeof(state));

	/*

	state.start();
	
	int t1=clock();

	FILE*fp=fopen("fight_log.txt","w");
	for(int i=0;i<1;i++)
		state.report.save(fp);
	
	int t2=clock();
	printf("%d %d %d\n",t1-t0,t2-t1,t2);
	puts("*****");
	*/

	puts("******");

	FILE*fp=fopen("test_in.c","r");

	wchar_t code[10000];
	s2 len=0;
	while(~fscanf(fp,"%lc",code+len))
		len++;
	code[len]=0;
	fclose(fp);

	//printf("%ls\n\n",code);

	Cscript::Compiler compiler(code,allocor);
	compiler.compile();

	printf(">>>>>>>>>>>%d\n",(s2)compiler.units.size());

	for(auto&unit:compiler.units)
	{
		std::wcout<<unit->what(compiler)<<'\n';
		//printf("%d %d %d %d\n",(int)unit->type,(int)unit->type2,unit->line,unit->col);
	}

	freopen("out.txt","w",stderr);

	compiler.parse();
	
}
