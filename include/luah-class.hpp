#ifndef LUAH_CLASS_
#define LUAH_CLASS_

namespace luah {
    template <typename A0> struct ctor{int x;};
    
namespace internal {
    struct method {
	std::string name;
	lua_CFunction func;
	void * upval;
    };
    
    struct method_set {
	static const int kMaxMethodCount = 32;
	std::string class_name_;
	method m_[kMaxMethodCount];
	size_t ct;
	method_set() : ct(0) {}
	~method_set() {
	    for (size_t i = 0; i < ct; ++i)
		free(m_[i].upval);
	}
    };
    
    template <typename T>
    class method_importer {
    public:
	method_importer(lua_State* L) {
	    set_ = new method_set();
	}

	method_set& get_set() { return *set_; }	
	void add_method(const method & m) {
	    if (set_->ct < method_set::kMaxMethodCount) {
		set_->m_[set_->ct++] = m;
	    }
	    else {
		luaL_error(L_, "%s has too much method.", set_->class_name_.c_str());
	    }
	}
    private:
	lua_State * L_;
	method_set* set_;
    };

    template <typename R, typename I>
    struct class_method_adaptor {
	static int call(lua_State * L) {
	    push(L, static_cast<R>(I::call(L)));
	    return 1;
	}
    };
    
    template <typename I>
    struct class_method_adaptor<void, I> {
	static int call(lua_State * L) {
	    I::call(L);
	}
    };

    // todo: add to gen
    template <typename T, typename R>
    struct class_method_caller_0 {
	typedef R (T::*f_type) ();
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(1))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(2)));
	    return (t->*f)();
	}
    };

    template <typename T, typename R, typename A0>
    struct class_method_caller_1 {
	typedef R (T::*f_type) (A0);
	static R call(lua_State * L) {
	    f_type f  = *(f_type*) (lua_touserdata(L, lua_upvalueindex(1))); 
	    T* t =reinterpret_cast<T*> (lua_touserdata(L, lua_upvalueindex(2)));
	    return (t->*f)(check_adaptor<A0>::call(L, 1));
	}
    };
    

    template<typename T>
    method_importer<T>& operator<<(method_importer<T>& ip, method obj) {
	ip.add_method(obj);
	return ip;
    }

    void class_set_methods(lua_State *L, const method_set & set_, void * ins) {
	int table = lua_gettop(L);
	
    }

    template <typename T>
    struct class_constructor {
	static int call(lua_State *L) {
	    // upval 1: creator
	    // upval 2: method_set
	     
	    // step 1: create a new instance
	    typedef T * (*c_type) (lua_State *L);
	    T * instance = reinterpret_cast<c_type>(lua_touserdata(L, lua_upvalueindex(1))) (L);
	 
	    // step 2: create a new table ( as instance in lua )
	    lua_newtable(L);

            // step 3: put the C++ instance to table as udata
	    lua_pushlightuserdata(L, (void*)0);
	    lua_pushlightuserdata(L, instance);
	    lua_settable(L, -3); 
	    
	    // step 4: add methods to table 
	    class_set_methods(L, *static_cast<method_set*>(lua_touserdata(L, lua_upvalueindex(2))), instance);

	    // step 5: set table's metatable: to make __gc call destroy
	    lua_pushstring(L, "luah");
	    lua_gettable(L, LUA_REGISTRYINDEX);
	    lua_pushlightuserdata(L, reinterpret_cast<void*>(call));
	    lua_gettable(L, -2);
	    lua_setmetatable(L, -3);
	    lua_pop(L, 1);
	    return 1;
	}
    };
}
  
    template <typename T>
    class add_class {
    public:
	add_class(lua_State *L, const char* class_name) : L_(L), importer_(L) {
	    importer_.get_set().class_name_=class_name;
	    open(class_name);
	}

	~add_class() {
	    close(importer_.get_set().class_name_.c_str());
	}

	template <typename F>
	internal::method_importer<T>& operator[](F);

	///!! START_METHOD_IMPORTER
	internal::method_importer<T>& operator[](ctor<void>) {
	    creator_ = internal::creator_0<T>;
	    return importer_;
	}
	
	template <typename A0>
	internal::method_importer<T>& operator[](ctor<A0>) {
	    creator_ = internal::creator_1<T, A0>;
	    return importer_;
	}
	///!! END_METHOD_IMPORTER

	template <typename F>
	internal::method_importer<T>& operator<<(F f) {
	    return (*this)[ ctor<void>() ] << f;
	}
	
    private:
	internal::method_importer<T> importer_;
	lua_State *L_;
	T* (*creator_) (lua_State *L);

	void open(const char* class_name) {
	    //
	}

	static int do_gc(lua_State * L) {
	    delete reinterpret_cast<internal::method_set*>(lua_touserdata(L, lua_upvalueindex(1)));
	}

	void close(const char* class_name) {
	    // create a userdata which can be called as the construct of the class
	    lua_newuserdata(L_, sizeof(void*));
	    // create the metatable
	    lua_newtable(L_);
	    // add call method
	    lua_pushstring(L_, "__call");
	    lua_pushlightuserdata(L_, reinterpret_cast<void*>(creator_));
	    lua_pushlightuserdata(L_, &importer_.get_set());
	    lua_pushcclosure(L_, internal::class_constructor<T>::call, 2);
	    lua_settable(L_, -3);
	    // add gc method
	    lua_pushstring(L_, "__gc");
	    lua_pushlightuserdata(L_, &importer_.get_set());
	    lua_pushcclosure(L_, do_gc, 1);
	    lua_settable(L_, -3);
	    // set metatable
	    lua_setmetatable(L_, -2);
	    lua_setglobal(L_, class_name);
	}

	add_class();
	add_class(const add_class<T> &);
	void operator=(const add_class<T> &);
    };

    // todo : add to gen.py
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
}


#endif
