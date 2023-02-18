#pragma once

struct Attribute_Table_A
{
    Attribute_A attribute_a;
    Attribute_Table_A(Mem::SA&sa);
};

struct Attribute_Table
{
    Attribute HP_lim,MP_lim,AP_lim;
    Attribute HP_re,MP_re,AP_re;
    Attribute MP_init,AP_init;
    Attribute ATK;
    Attribute P_res,M_res;
    Attribute Crt,CrtD;
    Attribute exAPre_profit;
    Attribute Con_res;

    Attribute_Table(const Player_Config::Hero&hero,Attribute_Table_A&a);

};
