#pragma once

struct Skill;

#define lambda_Skill_init []([[maybe_unused]] ::Fight::State::Skill&skill)
#define lambda_Skill_check []([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg)
#define lambda_Skill_use []([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg)
