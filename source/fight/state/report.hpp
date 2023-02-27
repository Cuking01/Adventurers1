#pragma once



struct Report_Block
{
	static constexpr s2 bs=60;
	wchar_t s[bs];
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
	static constexpr s2 bs=Report_Block::bs;
	Report_A&a;
	Report_Block*head;
	Report_Block*end;
	s2 len;

	Report(Report_A&a);

	template<typename... Args>
	void write(fmt::wformat_string<Args...> fmt,const Args&... args);
	
	s2 length() const;

	void save(FILE*fp) const;
	void save(wchar_t*tp) const;

};

