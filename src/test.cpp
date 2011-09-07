#include "luah.hpp"
#include "utest.h"

struct LuaState { // RAII for lua state
    LuaState() {
	L = lua_open();
    }
    ~LuaState() {
	if (L != NULL)
	    lua_close(L);
    }
    lua_State * L;
};

int test_int_func() {
    return 6;
}

void test_void_func() {}

double my_sqr_func(double x) {
    return x * x;
}

char * double_func(const char* str) {
    static char buf[1024];
    snprintf(buf, sizeof(buf), "%s%s", str);
    return buf;
}

TEST_CASE(reg_func) {
    LuaState lua;
    luaL_openlibs(lua.L);
    luah::add_func(lua.L, "test_int_func", test_int_func);
    luah::add_func(lua.L, "test_void_func", test_void_func);
    luah::add_func(lua.L, "my_sqr", my_sqr_func);
    luah::add_func(lua.L, "double_func", double_func);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_reg_func.lua") == 0, lua_tostring(lua.L, -1));
}

TEST_CASE(reg_func_to_table) {
    LuaState lua;
    luaL_openlibs(lua.L);
    lua_newtable(lua.L);
    luah::add_func_table(lua.L, -1, "tint", test_int_func);
    luah::add_func_table(lua.L, -1, "tvoid", test_int_func);
    luah::add_func_table(lua.L, -1, "mysqr", test_int_func);
    luah::add_func_table(lua.L, -1, "double", test_int_func);
    lua_setglobal(lua.L, "t");
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_reg_func_table.lua") == 0, lua_tostring(lua.L, -1));
}

TEST_CASE(call_lua_func) {
    LuaState lua;
    luaL_openlibs(lua.L);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_call_func.lua") == 0, lua_tostring(lua.L, -1));
    ASSERT_TRUE(luah::call_func<int>(lua.L, "calc", 1) == 2);
    ASSERT_TRUE(luah::call_func<int>(lua.L, "add", 2, 3) == 5);  
}

bool destroy_flag = false;
class TestClass {
public:
    int get_a() {
	t = &destroy_flag;
	return a_;
    }
    void set_a(int a) {
	a_ = a;
    }

    ~TestClass() {
	*t = true;
    }
private:
    int a_;
public:
    bool *t;
};

TEST_CASE(test_class) {
    LuaState lua;
    luah::add_class<TestClass>(lua.L, "TestClass")[luah::ctor<void>()]
	<< luah::method("get_a", &TestClass::get_a)
	<< luah::method("set_a", &TestClass::set_a);
    luaL_openlibs(lua.L);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_class.lua") == 0, lua_tostring(lua.L, -1));
    ASSERT_TRUE_MSG(destroy_flag, "didn't destruct test class");
}

int main() {
    return utest_run_all();
}
