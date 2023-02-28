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

	while(tlen>bs)
	{
		p->s[bs]=L'\0';
		fwprintf(fp,L"%ls",p->s);
		p=p->next;
		tlen-=bs;
	}
	
	if(tlen>0)
	{
		p->s[tlen]=L'\0';
		fwprintf(fp,L"%ls",p->s);
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

void Report::write(const wchar_t* sp)
{
	//最长10万
	if(len>=100000)return;

	s2 l=wcslen(sp);

	//太长的滚蛋
	if(l>100000)return;

	s2 rlen=bs-len%bs;
	len+=l;


	s2 mlen=std::min(rlen,l);
	memcpy(end->s+bs-rlen,sp,mlen*sizeof(wchar_t));

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

void Report::write(const std::wstring&str)
{
	write(str.data());
}
