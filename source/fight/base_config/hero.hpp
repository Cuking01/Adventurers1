#pragma once

struct Hero
{
    const wchar_t* name;
    const wchar_t* description;
    struct Tag{};
    Tag tag;
    Attribute_Table attribute_table;
    Skill skill[5];

    s2 id() const;
    s2 check() const;
};
