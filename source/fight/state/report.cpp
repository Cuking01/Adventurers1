#pragma once

Report_Block::Report_Block():
	next(nullptr)
{}

Report_A::Report_A(Mem::SA&sa):
	pool(sa)
{}

Report::Report(Report_A&a):
	a(a),
	len(0)
{
	end=head=a.pool();
}

s2 Report::length() const
{
	return len;
}


void Report::save(FILE*fp) const
{
	s2 tlen=len;
	Report_Block*p=head;

	while(tlen>60)
	{
		fwrite(p->s,sizeof(wchar_t),bs,fp);
		p=p->next;
		tlen-=bs;
	}
	
	if(tlen>0)
	{
		fwrite(p->s,sizeof(wchar_t),tlen,fp);
	}
}

void Report::save(wchar_t*tp) const
{
	s2 tlen=len;
	Report_Block*p=head;

	while(tlen>bs)
	{
		memcpy(tp,p->s,bs*sizeof(wchar_t));
		p=p->next;
		tlen-=bs;
		tp+=bs;
	}
	
	if(tlen>0)
	{
		memcpy(tp,p->s,tlen*sizeof(wchar_t));
	}

	tp[tlen]=L'\0';
}

template<typename... Args>
void Report::write(fmt::wformat_string<Args...> fmt,const Args&... args)
{
	std::wstring str=fmt::format(fmt,args...);
	//太长的滚蛋
	if(str.length()>10000)
		return;

	s2 l=str.length();
	s2 rlen=bs-len%bs;
	wchar_t*sp=str.data();

	s2 mlen=std::min(rlen,l);
	memcpy(end->s,sp,mlen);
	sp+=mlen;
	l-=mlen;

	if(rlen==mlen)
	{
		end->next=a.pool();
		end=end->next;
	}

	while(l>=bs)
	{
		memcpy(end->s,sp,bs*sizeof(wchar_t));
		sp+=bs;
		end->next=a.pool();
		end=end->next;
		l-=bs;
	}

	if(l)
	{
		memcpy(end->s,sp,l*sizeof(wchar_t));
	}

}
