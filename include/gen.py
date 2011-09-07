import string
import datetime
ARG_COUNT = 8

def print_head(fp):
    print >> fp, "// luah-auto.hpp"
    print >> fp, "// this is auto-generated file by gen.py"
    print >> fp, "// generate time: " + datetime.datetime.now().strftime("%Y-%m-%d %X")
    print >> fp

def print_in_internal(fp, f):
    print >> fp, """namespace luah {
namespace internal {"""
    f()
    print >> fp, """
}}"""

def print_arg_t(fp, count):
    for i in xrange(1, count + 1):
        print_arg_t_class(fp, i)

def print_creator(fp, count):
    for i in xrange(0, count + 1):
        print >> fp, """
    template <typename T%s>
    T* creator_%d(lua_State* L) {
        return new T(%s);
    }""" % (string.join([", typename A%d" % x for x in xrange(i)], ""),
            i,
            string.join(["check_adaptor<A%d>::call(L, %d)" % (x, x+1) for x in xrange(i)], ", "))

def print_arg_t_class(fp, i):
    print >> fp, """
    template <typename R, %s>
    class arg_t%d {
    public:
        typedef R(*F) (%s);
        static R call(lua_State *L, F func) {
            return func(%s);
        }
    };""" % (string.join(["typename A%d" % x for x in range(i)], ', '),
             i,
             string.join([("A%d" % x) for x in range(i)], ', '),
             string.join([("check_adaptor<A%d>::call(L, %d)" % (x, x+1)) for x in range(i)], ", "))
             
def print_in_luah(fp, func, count):
    print >> fp, "\nnamespace luah {\n"
    for i in xrange (1, count + 1):
        func(fp, i)
    print >> fp, "\n}"

def print_add_func(fp, k):
    i = k - 1
    print >> fp, """
    template <typename R%s>
    void add_func(lua_State* L, const char * name, R (*func)(%s) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t%d<R%s> >::func, 1);
        lua_setglobal(L, name);
    }
""" % (string.join([", typename A%d" % x for x in range(i)], ''),
       string.join(["A%d" % x for x in range(i)], ', '),
       i,
       string.join([", A%d" % x for x in range(i)], ''))

def print_add_func_table(fp, k):
    i = k - 1
    print >> fp, """
    template <typename R%s>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(%s) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t%d<R%s> >::func, 1);
        lua_settable(L, n);
    }
"""  % (string.join([", typename A%d" % x for x in range(i)], ''),
       string.join(["A%d" % x for x in range(i)], ', '),
       i,
       string.join([", A%d" % x for x in range(i)], ''))

def print_call_func(fp, k):
    i = k - 1
    print >> fp, """
    template <typename R%s>
    R call_func(lua_State *L, const char * name%s)  {
        lua_getglobal(L, name);
        lua_checkstack(L, %d);
        %s
        if (lua_pcall(L, %d, 1, 0) != 0) {
            luaL_error(L, "%%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }
""" % ( string.join([", typename A%d" % x for x in range(i)], ''),
        string.join([", A%d a%d" % (x, x) for x in range(i)], ''),
        i + 1,
        string.join(["internal::push(L, a%d);" % x for x in range(i)], '\n        '),
        i)
    
fp = open("luah-auto.hpp", "w")
print_head(fp)
print_in_internal(fp, lambda: print_arg_t(fp, ARG_COUNT))
print_in_internal(fp, lambda: print_creator(fp, ARG_COUNT)) 
print_in_luah(fp, print_add_func, ARG_COUNT + 1)
print_in_luah(fp, print_add_func_table, ARG_COUNT + 1)
print_in_luah(fp, print_call_func, ARG_COUNT + 1)
fp.close()

print "finished."

