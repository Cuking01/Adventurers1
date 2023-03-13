#pragma once

struct Buff_Helper;

struct Buff_Base;

struct Buff;
struct Event;
struct Damage_Handler;

#define lambda_Buff []([[maybe_unused]] ::Fight::State::Attribute&attr,::Fight::State::Buff_Helper&bh,[[maybe_unused]]const Arg_t_5&st)->s2
#define lambda_Event []([[maybe_unused]] ::Fight::State::State&state,[[maybe_unused]]const Arg_t_5&st)->s2
#define lambda_Damage_Handler []([[maybe_unused]] ::Fight::State::State&state,[[maybe_unused]] ::Fight::State::Damage&damage,[[maybe_unused]]const Arg_t_5&st)->s2
#define lambda_Skill_Handler []([[maybe_unused]] ::Fight::State::State&state,[[maybe_unused]] ::Fight::State::Hid hid,[[maybe_unused]] s2 sid,[[maybe_unused]] const Arg_t_6&arg,[[maybe_unused]] const Arg_t_5&st)

#define BT ::Fight::State::Buff_Base::Tag
