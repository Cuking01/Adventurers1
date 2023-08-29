#pragma once



s2 extract();        //翻译阶段1，提取合法字符
s2 merge_line();     //翻译阶段2，合并斜杠和换行符号为空

s2 remove_note();    //去注释    翻译阶段3
s2 empty_char();     //把所有空白字符变成空格 翻译阶段3 
s2 split();          //拆分      翻译阶段3
s2 merge_string();   //把相邻的字符串字面量合并
s2 lex();            //执行完整的词法分析
