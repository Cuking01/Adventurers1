#include "stdhead.h"
#include "tool.h"
#include "memory.h"
#include "fight.h"

#include "tool.hpp"
#include "fight.hpp"

#define Warning(...) printf(__VA_ARGS__)

#include "tool.cpp"
#include "memory.cpp"
#include "fight.cpp"

int main()
{
	Mem::SA allocor1(Mem::ra);
	Mem::Allocator<int> allocor2(allocor1);
	Mem::Allocator_STL<int>allocor3(allocor2);
	std::vector<int,decltype(allocor3)> vec(allocor3);
	vec.push_back(123123);
	
	using namespace Fight::State;


	Attribute_A allocor5(allocor1);

	Damage_A allocor7(allocor1);

	State_A state_a(allocor1);

	Fight::Player_Config::Group gc;
	State state(gc,gc,state_a);

	Attribute attr(10,0,100,allocor5);

	attr.add(5,Buff{{{},{}},lambda_Buff{bh.add+=5;return 0;}});
	attr.add(8,Buff{{{},{}},lambda_Buff{bh.addp+=1;return 0;}});
	attr.add(10,Buff{{{.D0=10},{}},lambda_Buff{bh.sub+=st.D0;return 0;}});

	printf("%f\n",attr());

	attr.erase(8);

	printf("%f\n",attr());
	puts("****");

	Damage damage(0,{},{},{},allocor7);

	
}
