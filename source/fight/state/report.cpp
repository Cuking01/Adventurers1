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
