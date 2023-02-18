#pragma once

struct Equipment
{
    const wchar_t* name;
    const wchar_t* description;
    Attribute_Table attribute_table;
    Skill skill;

    s2 id() const;
};
