import string
import datetime
import re
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

def print_creator(fp, count):
    for i in xrange(0, count + 1):
        print >> fp, """
    template <typename T%s>
    T* creator_%d(lua_State* L) {
        return new T(%s);
    }""" % (string.join([", typename A%d" % x for x in xrange(i)], ""),
            i,
            string.join(["check_adaptor<A%d>::call(L, %d)" % (x, x+2) for x in xrange(i)], ", "))

def print_class_method_caller(fp, count):
    for i in xrange(0, count + 1):
        print >> fp, """
    template <typename T, typename R%s>
    struct class_method_caller_%d {
	typedef R (T::*f_type) (%s);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(%s);
	}
    };""" %( string.join([", typename A%d" % x for x in xrange(i)], ""),
             i,
             string.join(["A%d" % x for x in xrange(i)], ','),
             string.join(["check_adaptor<A%d>::call(L, %d)" % (x, x+1) for x in xrange(i)], ", "));
             
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

def print_method(fp, k):
    i = k - 1
    print >> fp, """
    template <typename T, typename R%s>
    internal::method method (const char * name_, R (T::*f) (%s)) {
	typedef R (T::*f_type) (%s);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_%d<T, R%s> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }""" % ( string.join([", typename A%d" % x for x in xrange(i)], ''),
             string.join(["A%d" % x for x in xrange(i)], ','),
             string.join(["A%d" % x for x in xrange(i)], ','),
             i,
             string.join([", A%d" % x for x in xrange(i)], '')
             )

def print_ctor(fp):
    print >> fp, """namespace luah {
template <typename A0%s> struct ctor{int x;};
}""" % string.join([", typename A%d=void" % x for x in xrange(1, ARG_COUNT)], '');

    
fp = open("luah-auto.hpp", "w")
print_head(fp)
print_in_internal(fp, lambda: print_arg_t(fp, ARG_COUNT))
print_in_internal(fp, lambda: print_creator(fp, ARG_COUNT))
print_in_internal(fp, lambda: print_class_method_caller(fp, ARG_COUNT))
print_in_luah(fp, print_add_func, ARG_COUNT + 1)
print_in_luah(fp, print_add_func_table, ARG_COUNT + 1)
print_in_luah(fp, print_call_func, ARG_COUNT + 1)
print_in_luah(fp, print_method, ARG_COUNT + 1)
print_ctor(fp)
fp.close()

def gen_cons_oper(n):
    str = "///!! START_METHOD_IMPORTER\n"
    str += """        internal::method_importer<T>& operator[](ctor<void>) {
        creator_ = internal::creator_0<T>;
        return importer_;
	}"""
    for i in xrange(1, n+1):
        str += """
        template <%s>
        internal::method_importer<T>& operator[](ctor<%s>) {
            creator_ = internal::creator_1<T, %s>;
            return importer_;
        }""" % ( string.join(["typename A%d" % x for x in xrange(i)], ', '),
                 string.join(["A%d" % x for x in xrange(i)], ', '),
                 string.join(["A%d" % x for x in xrange(i)], ', '))
    str += "\n    ///!! END_METHOD_IMPORTER\n"
    return str

fp = open("luah-class.hpp")
str = fp.read()
fp.close()

fp = open("luah-class.hpp", "w")
print >> fp, re.sub('///!! START_METHOD_IMPORTER(.|\n)*///!! END_METHOD_IMPORTER', gen_cons_oper(ARG_COUNT), str)
fp.close()

print "finished."

