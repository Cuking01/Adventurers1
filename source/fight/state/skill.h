#pragma once

struct Skill_A;
struct Skill;

#define lambda_Skill_init []([[maybe_unused]] ::Fight::State::Skill&skill)->void
#define lambda_Skill_check []([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg)->s2
#define lambda_Skill_use []([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg)->void
