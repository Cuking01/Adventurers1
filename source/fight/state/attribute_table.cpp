#pragma once

Attribute_Table_A::Attribute_Table_A(Mem::SA&sa):
	attribute_a(sa)
{}

#define attr_init_end(name)  \
	name(  \
		Base_Config::hero[hero.id].attribute_table.name(hero.level)+ \
		Base_Config::equipment[hero.equipment[0].id].attribute_table.name(hero.equipment[0].level)+ \
		Base_Config::equipment[hero.equipment[1].id].attribute_table.name(hero.equipment[1].level)+ \
		Base_Config::equipment[hero.equipment[2].id].attribute_table.name(hero.equipment[2].level)+ \
		Base_Config::hero[hero.id].skill[0].attribute_table.name(hero.skill[0].level)+  \
		Base_Config::hero[hero.id].skill[1].attribute_table.name(hero.skill[1].level)+  \
		Base_Config::hero[hero.id].skill[2].attribute_table.name(hero.skill[2].level)+  \
		Base_Config::hero[hero.id].skill[3].attribute_table.name(hero.skill[3].level)+  \
		Base_Config::hero[hero.id].skill[4].attribute_table.name(hero.skill[4].level),a.attribute_a)

#define attr_init(name) attr_init_end(name),

Attribute_Table::Attribute_Table(const Player_Config::Hero&hero,Attribute_Table_A&a):
	PP_FOR_EACH(attr_init,HP_lim,MP_lim,AP_lim,HP_re,MP_re,AP_re,MP_init,AP_init,ATK,P_res,M_res,Crt,CrtD,exAPre_profit)
	attr_init_end(Con_res)
{}

#undef attr_init
#undef attr_init_end
