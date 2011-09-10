#include "luah.hpp"
#include "utest.h"

int main() {
    return utest_run_all();
}

// test cases

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

// -------- internal function test ----------

// test push
TEST_CASE(test_push) {
    LuaState lua;
    // test push int    
    luah::internal::push(lua.L, 3);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    ASSERT_TRUE(lua_isnumber(lua.L, -1));
    ASSERT_TRUE(lua_tonumber(lua.L, -1) == 3);
    lua_pop(lua.L, 1);
    // test push double
    luah::internal::push(lua.L, 3.5);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    ASSERT_TRUE(lua_isnumber(lua.L, -1));
    ASSERT_TRUE(lua_tonumber(lua.L, -1) == 3.5);
    lua_pop(lua.L, 1);
    // test push bool
    for (int i = 0; i < 2; ++i) {
        bool val = i == 0;
        luah::internal::push(lua.L, val);
        ASSERT_TRUE(lua_gettop(lua.L) == 1);
        ASSERT_TRUE(lua_isboolean(lua.L, -1));
        ASSERT_TRUE(lua_toboolean(lua.L, -1) == val);
        lua_pop(lua.L, 1);   
    }
    // test push const char *
    luah::internal::push(lua.L, "test str");
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    ASSERT_TRUE(lua_isstring(lua.L, -1));
    lua_pop(lua.L, 1);
    // test push std::string
    luah::internal::push(lua.L, std::string("test str"));
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    ASSERT_TRUE(lua_isstring(lua.L, -1));
    ASSERT_TRUE(lua_tostring(lua.L, -1) == std::string("test str"));
    lua_pop(lua.L, 1);
    // test push T*
    int * p = new int;
    luah::internal::push(lua.L, p);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    ASSERT_TRUE(lua_isuserdata(lua.L, -1));
    ASSERT_TRUE(lua_touserdata(lua.L, -1) == p);
    lua_pop(lua.L, 1);    
    delete p;
}

// test_checkadaptor
TEST_CASE(check_adaptor) {
    using luah::internal::check_adaptor;
    LuaState lua;
    // test check int
    lua_pushnumber(lua.L, 3);
    ASSERT_TRUE(check_adaptor<int>::call(lua.L, -1) == 3);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);
    // test check unsigned int
    lua_pushnumber(lua.L, 3u);
    ASSERT_TRUE(check_adaptor<unsigned int>::call(lua.L, -1) == 3u);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);    
    // test check short
    lua_pushnumber(lua.L, 3);
    ASSERT_TRUE(check_adaptor<short int>::call(lua.L, -1) == 3);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);
    // test check unsigned short
    lua_pushnumber(lua.L, 3u);
    ASSERT_TRUE(check_adaptor<unsigned short int>::call(lua.L, -1) == 3u);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);    
    // test check char
    lua_pushnumber(lua.L, 3u);
    ASSERT_TRUE(check_adaptor<char>::call(lua.L, -1) == 3u);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);    
    // test check double
    lua_pushnumber(lua.L, 5.5);
    ASSERT_TRUE(check_adaptor<double>::call(lua.L, -1) == 5.5);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);
    // test check float
    lua_pushnumber(lua.L, 5.5);
    ASSERT_TRUE(check_adaptor<float>::call(lua.L, -1) == 5.5);
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);
    
    // test check bool
    for (int i = 0; i < 2; ++i) {
        bool flag = i == 0;
        lua_pushboolean(lua.L, flag);
        ASSERT_TRUE(check_adaptor<bool>::call(lua.L, -1) == flag);
        ASSERT_TRUE(lua_gettop(lua.L) == 1);
        lua_pop(lua.L, 1);    
    }

    // test check const char *
    lua_pushstring(lua.L, "test_str");
    ASSERT_TRUE(check_adaptor<const char*>::call(lua.L, -1) == std::string("test_str"));
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);

    // test check std::string
    lua_pushstring(lua.L, "test_str");
    ASSERT_TRUE(check_adaptor<std::string>::call(lua.L, -1) == std::string("test_str"));
    ASSERT_TRUE(lua_gettop(lua.L) == 1);
    lua_pop(lua.L, 1);

    // test check T*: 1. userdata
    int a;
    int *ptr = &a;
    lua_pushlightuserdata(lua.L, ptr);
    ASSERT_TRUE(check_adaptor<int*>::call(lua.L, -1) == ptr);
    lua_pop(lua.L, 1);

    // test check T*: 2. special table
    //    lua_newtable(lua.L);
    //lua_pushlightuserdata(lua.L, (void*)0);
    //lua_pushlightuserdata(lua.L, ptr);
    //lua_settable(lua.L, -3);
    //ASSERT_TRUE(check_adaptor<int*>::call(lua.L, -1) == ptr);
    //lua_pop(lua.L, 1);

    // call void
    check_adaptor<void>::call(lua.L, -1);
}

// --------- function import test --------------

int test_int_func() {
    return 6;
}

void test_void_func() {}

double my_sqr_func(double x) {
    return x * x;
}

char * double_func(const char* str) {
    static char buf[1024];
    snprintf(buf, sizeof(buf), "%s%s", str, str);
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
    luah::add_func_table(lua.L, -1, "tvoid", test_void_func);
    luah::add_func_table(lua.L, -1, "mysqr", my_sqr_func);
    luah::add_func_table(lua.L, -1, "double", double_func);
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
    TestClass() {
        t = &destroy_flag;
    }
    int get_a() {
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

class TestClassB {
public:
    explicit TestClassB(TestClass * ins) {
        this->ins = ins;
    }
    void incr_by_n(int n) {
        ins->set_a(ins->get_a() + n);
    }
    void mul_tcb(TestClass * b) {
        ins->set_a(ins->get_a() * b->get_a());
    }
private:
    TestClass * ins;
};

TEST_CASE(test_class) {
    LuaState lua;
    luaL_openlibs(lua.L);
    luah::add_class<TestClass>(lua.L, "TestClass")
	<< luah::method("get_a", &TestClass::get_a)
	<< luah::method("set_a", &TestClass::set_a);
    typedef TestClass * t;
    luah::add_class<TestClassB>(lua.L, "TestClassB")[luah::ctor<t>()]
        << luah::method("incr_by_n", &TestClassB::incr_by_n)
        << luah::method("mul_tcb", &TestClassB::mul_tcb);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_class.lua") == 0, lua_tostring(lua.L, -1));
    ASSERT_TRUE_MSG(destroy_flag, "didn't destruct test class");
}

TestClass * test_class_creator (lua_State * L) {
    if (lua_gettop(L) == 0) {
        return new(std::nothrow)TestClass();
    }
    else if (lua_gettop(L) == 1) {
        if (lua_isnumber(L, 1)) {
            TestClass * t = new TestClass();
            t->set_a(lua_tonumber(L, 1));
            return t;
        }
        if (lua_istable(L, 1)) {
            return new(std::nothrow)TestClass(*luah::internal::check_adaptor<TestClass*>::call(L, 1));
        }
    }
    return NULL;
}

TEST_CASE(user_define_class_ctor) {
    LuaState lua;
    luaL_openlibs(lua.L);
    luah::add_class<TestClass>(lua.L, "TestClass")[test_class_creator]
        << luah::method("get_a", &TestClass::get_a)
        << luah::method("set_a", &TestClass::set_a);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_class_udc.lua") == 0, lua_tostring(lua.L, -1));    
}

int my_method(lua_State * L) {
    TestClass * tc = luah::get_instance<TestClass>(L);
    if (lua_gettop(L) == 1) {
        lua_pushnumber(L, tc->get_a());
        tc->set_a(lua_tonumber(L, 1));
        lua_pushnumber(L, tc->get_a());
        return 2;
    }
    return 0;
}

TEST_CASE(user_define_method) {
    LuaState lua;
    luaL_openlibs(lua.L);
    luah::add_class<TestClass>(lua.L, "TestClass")[luah::ctor<void>()]
        << luah::method("get_a", &TestClass::get_a)
        << luah::method("set_a", &TestClass::set_a)
        << luah::method_ex("my_method", &my_method);
    ASSERT_TRUE_MSG(luaL_dofile(lua.L, "test_class_udm.lua") == 0, lua_tostring(lua.L, -1));    

}
