// luah-auto.hpp
// this is auto-generated file by gen.py
// generate time: 2011-09-07 23:38:41

namespace luah {
namespace internal {

    template <typename R, typename A0>
    class arg_t1 {
    public:
        typedef R(*F) (A0);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1));
        }
    };

    template <typename R, typename A0, typename A1>
    class arg_t2 {
    public:
        typedef R(*F) (A0, A1);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2));
        }
    };

    template <typename R, typename A0, typename A1, typename A2>
    class arg_t3 {
    public:
        typedef R(*F) (A0, A1, A2);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3));
        }
    };

    template <typename R, typename A0, typename A1, typename A2, typename A3>
    class arg_t4 {
    public:
        typedef R(*F) (A0, A1, A2, A3);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4));
        }
    };

    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    class arg_t5 {
    public:
        typedef R(*F) (A0, A1, A2, A3, A4);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5));
        }
    };

    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    class arg_t6 {
    public:
        typedef R(*F) (A0, A1, A2, A3, A4, A5);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6));
        }
    };

    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    class arg_t7 {
    public:
        typedef R(*F) (A0, A1, A2, A3, A4, A5, A6);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7));
        }
    };

    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    class arg_t8 {
    public:
        typedef R(*F) (A0, A1, A2, A3, A4, A5, A6, A7);
        static R call(lua_State *L, F func) {
            return func(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7), check_adaptor<A7>::call(L, 8));
        }
    };

}}
namespace luah {
namespace internal {

    template <typename T>
    T* creator_0(lua_State* L) {
        return new T();
    }

    template <typename T, typename A0>
    T* creator_1(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1));
    }

    template <typename T, typename A0, typename A1>
    T* creator_2(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2));
    }

    template <typename T, typename A0, typename A1, typename A2>
    T* creator_3(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3));
    }

    template <typename T, typename A0, typename A1, typename A2, typename A3>
    T* creator_4(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4));
    }

    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
    T* creator_5(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5));
    }

    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    T* creator_6(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6));
    }

    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    T* creator_7(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7));
    }

    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    T* creator_8(lua_State* L) {
        return new T(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7), check_adaptor<A7>::call(L, 8));
    }

}}
namespace luah {
namespace internal {

    template <typename T, typename R>
    struct class_method_caller_0 {
	typedef R (T::*f_type) ();
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)();
	}
    };

    template <typename T, typename R, typename A0>
    struct class_method_caller_1 {
	typedef R (T::*f_type) (A0);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1));
	}
    };

    template <typename T, typename R, typename A0, typename A1>
    struct class_method_caller_2 {
	typedef R (T::*f_type) (A0,A1);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2>
    struct class_method_caller_3 {
	typedef R (T::*f_type) (A0,A1,A2);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3>
    struct class_method_caller_4 {
	typedef R (T::*f_type) (A0,A1,A2,A3);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    struct class_method_caller_5 {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    struct class_method_caller_6 {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    struct class_method_caller_7 {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5,A6);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7));
	}
    };

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    struct class_method_caller_8 {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5,A6,A7);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(2))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(1)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1), check_adaptor<A1>::call(L, 2), check_adaptor<A2>::call(L, 3), check_adaptor<A3>::call(L, 4), check_adaptor<A4>::call(L, 5), check_adaptor<A5>::call(L, 6), check_adaptor<A6>::call(L, 7), check_adaptor<A7>::call(L, 8));
	}
    };

}}

namespace luah {


    template <typename R>
    void add_func(lua_State* L, const char * name, R (*func)() ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t0<R> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0>
    void add_func(lua_State* L, const char * name, R (*func)(A0) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t1<R, A0> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t2<R, A0, A1> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t3<R, A0, A1, A2> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2, A3) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t4<R, A0, A1, A2, A3> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2, A3, A4) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t5<R, A0, A1, A2, A3, A4> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2, A3, A4, A5) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t6<R, A0, A1, A2, A3, A4, A5> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2, A3, A4, A5, A6) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t7<R, A0, A1, A2, A3, A4, A5, A6> >::func, 1);
        lua_setglobal(L, name);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    void add_func(lua_State* L, const char * name, R (*func)(A0, A1, A2, A3, A4, A5, A6, A7) ) {
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t8<R, A0, A1, A2, A3, A4, A5, A6, A7> >::func, 1);
        lua_setglobal(L, name);
    }


}

namespace luah {


    template <typename R>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)() ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t0<R> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t1<R, A0> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t2<R, A0, A1> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t3<R, A0, A1, A2> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2, A3) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t4<R, A0, A1, A2, A3> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2, A3, A4) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t5<R, A0, A1, A2, A3, A4> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2, A3, A4, A5) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t6<R, A0, A1, A2, A3, A4, A5> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2, A3, A4, A5, A6) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t7<R, A0, A1, A2, A3, A4, A5, A6> >::func, 1);
        lua_settable(L, n);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    void add_func_table(lua_State* L, ptrdiff_t n, const char * name, R (*func)(A0, A1, A2, A3, A4, A5, A6, A7) ) {
        n = n < 0 ? lua_gettop(L) + n + 1 : n;
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, reinterpret_cast<void*>(func));
        lua_pushcclosure(L, internal::func_adaptor<R, internal::arg_t8<R, A0, A1, A2, A3, A4, A5, A6, A7> >::func, 1);
        lua_settable(L, n);
    }


}

namespace luah {


    template <typename R>
    R call_func(lua_State *L, const char * name)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 1);
        
        if (lua_pcall(L, 0, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0>
    R call_func(lua_State *L, const char * name, A0 a0)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 2);
        internal::push(L, a0);
        if (lua_pcall(L, 1, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 3);
        internal::push(L, a0);
        internal::push(L, a1);
        if (lua_pcall(L, 2, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 4);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        if (lua_pcall(L, 3, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2, A3 a3)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 5);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        internal::push(L, a3);
        if (lua_pcall(L, 4, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 6);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        internal::push(L, a3);
        internal::push(L, a4);
        if (lua_pcall(L, 5, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 7);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        internal::push(L, a3);
        internal::push(L, a4);
        internal::push(L, a5);
        if (lua_pcall(L, 6, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 8);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        internal::push(L, a3);
        internal::push(L, a4);
        internal::push(L, a5);
        internal::push(L, a6);
        if (lua_pcall(L, 7, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


    template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    R call_func(lua_State *L, const char * name, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)  {
        lua_getglobal(L, name);
        lua_checkstack(L, 9);
        internal::push(L, a0);
        internal::push(L, a1);
        internal::push(L, a2);
        internal::push(L, a3);
        internal::push(L, a4);
        internal::push(L, a5);
        internal::push(L, a6);
        internal::push(L, a7);
        if (lua_pcall(L, 8, 1, 0) != 0) {
            luaL_error(L, "%s", lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        return internal::check_adaptor<R>::call(L, 0);
    }


}

namespace luah {


    template <typename T, typename R>
    internal::method method (const char * name_, R (T::*f) ()) {
	typedef R (T::*f_type) ();
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_0<T, R> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0>
    internal::method method (const char * name_, R (T::*f) (A0)) {
	typedef R (T::*f_type) (A0);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_1<T, R, A0> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1>
    internal::method method (const char * name_, R (T::*f) (A0,A1)) {
	typedef R (T::*f_type) (A0,A1);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_2<T, R, A0, A1> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2)) {
	typedef R (T::*f_type) (A0,A1,A2);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_3<T, R, A0, A1, A2> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2,A3)) {
	typedef R (T::*f_type) (A0,A1,A2,A3);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_4<T, R, A0, A1, A2, A3> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2,A3,A4)) {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_5<T, R, A0, A1, A2, A3, A4> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2,A3,A4,A5)) {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_6<T, R, A0, A1, A2, A3, A4, A5> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2,A3,A4,A5,A6)) {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5,A6);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_7<T, R, A0, A1, A2, A3, A4, A5, A6> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

    template <typename T, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    internal::method method (const char * name_, R (T::*f) (A0,A1,A2,A3,A4,A5,A6,A7)) {
	typedef R (T::*f_type) (A0,A1,A2,A3,A4,A5,A6,A7);
	internal::method ret;
	ret.name = name_;
	ret.func = internal::class_method_adaptor<R, internal::class_method_caller_8<T, R, A0, A1, A2, A3, A4, A5, A6, A7> >::call;
	f_type * p = reinterpret_cast<f_type*> (malloc(sizeof(f_type)));
	*p = f;
	ret.upval = reinterpret_cast<void*>(p);
	return ret;
    }

}
namespace luah {
template <typename A0, typename A1=void, typename A2=void, typename A3=void, typename A4=void, typename A5=void, typename A6=void, typename A7=void> struct ctor{int x;};
}
