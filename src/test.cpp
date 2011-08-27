#include "luah.hpp"

int func() {
	return 3;
}

void func_void() {
	printf("void test\n");
}

int sqr(int x) {
	return x * x;
}

void my_print(const char * s) {
	printf( " MY_PRINT:%s\n", s);
}

void init(lua_State *L) {
	luah::add_func(L, "testf", func);
	luah::add_func(L, "test_void", func_void);
	luah::add_func(L, "sqr", sqr);
	luah::add_func(L, "myprint", my_print);
}

void regt(lua_State * L) {
	lua_newtable(L);
	luah::add_func_table(L, -1, "x", func);
	luah::add_func_table(L, -1, "v", func_void);
	luah::add_func_table(L, -1, "sqr", sqr);
	luah::add_func_table(L, -1, "print", my_print);
	lua_setglobal(L, "t");
}


class A {
public:
	int x;
	int g() {return x + 1;}
};
void regc(lua_State *L) {
}

int main() {
	lua_State* L = lua_open();
	luaL_openlibs(L);
	short x = 2;
	init(L);
	regt(L);
	regc(L);

	typedef int (__thiscall A::* tf) ();
	tf funcc = &A::g;
	A a;
	a.x = 3;
	printf (" this is what ?  %d\n", (a.*funcc)());
	

	if (luaL_dofile(L, "test.lua") != 0) {
		printf("%s\n", lua_tostring(L, -1));
	}

	printf("calc()=%d\n", luah::call_func<int>(L, "calc"));
	luah::call_func<void>(L, "hello");

	printf("calc() = %.4f\n", luah::call_func<double>(L, "func", 6));


	return 0;
}