#pragma once



void parse();    //语法分析


Unit* get_unit() noexcept;

template<Symbol_Str symbol_str>
Unit* match_symbol_impl() noexcept;

template<Symbol_Str... symbols>
Unit* match_symbol() noexcept;

void unmatch_symbol();

Unit* match_idt() noexcept;
void unmatch_idt();

Literal* match_literal() noexcept;
void unmatch_literal();

