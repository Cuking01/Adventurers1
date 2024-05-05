#pragma once



void parse();    //语法分析


Unit* get_unit() noexcept;

template<Symbol_Str symbol_str>
Unit* match_symbol() noexcept;

template<Symbol_Str... symbols,typename... Callbacks>
Unit* match_symbol(Callbacks&&...callbacks) noexcept;

void unmatch_symbol();

Unit* match_idt() noexcept;
void unmatch_idt();

Unit* match_type() noexcept;
void unmatch_type();

