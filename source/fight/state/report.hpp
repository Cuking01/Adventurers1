#pragma once

struct Report_Block
{
	wchar_t s[60];
	Report_Block*next;
	Report_Block();
};

struct Report_A
{
	Mem::Pool<Report_Block,15> pool;
	Report_A(Mem::SA&sa);
};

struct Report
{
	Report_A&a;
	Report_Block*head;
	Report_Block*end;
	s2 len;

	Report(Report_A&a);
};
