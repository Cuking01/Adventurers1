#pragma once



struct Report_Block
{
	static constexpr s2 bs=59;
	wchar_t s[bs+1];
	Report_Block*next;
	Report_Block();
};

struct Report_A
{
	Mem::Pool<Report_Block,15> pool;
	Mem::Allocator<wchar_t> buf_a;
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

	void write(const wchar_t* str);
	void write(const std::wstring&str);

	// template<typename... Args>
	// void write(fmt::wformat_string<Args...> fmt,const Args&... args);
	
	// template<typename... Args>
	// void write(const wchar_t* fm,const Args&... args);

	s2 length() const;

	void save(FILE*fp) const;
	void save(wchar_t*tp) const;

};

