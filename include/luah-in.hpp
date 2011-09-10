// luah-internal
// do not include this file yourself

#ifdef LUAH_INTERNAL
#error "do not include luah-in.hpp yourself"
#endif

#define LUAH_INTERNAL

#include <string>

namespace luah {
    namespace internal {
	void push(lua_State* L, double val) {
            lua_pushnumber(L, val);
	}

	void push(lua_State* L, int val) {
            lua_pushnumber(L, val);
	}

	void push(lua_State* L, bool val) {
            lua_pushboolean(L, val);
	}

        void push(lua_State* L, char* str) {
            lua_pushstring(L, str);
        }

	void push(lua_State* L, const char* str) {
            lua_pushstring(L, str);
	}
       
        void push(lua_State* L,const std::string &str) {
            lua_pushstring(L, str.c_str());
        }

	void push(lua_State* L, lua_CFunction func) {
            lua_pushcclosure(L, func, 0);
	}

	template <typename T>
	void push(lua_State* L, T* ud) {
            lua_pushlightuserdata(L, ud);
	}

	template<typename T>
	T check(lua_State *L, ptrdiff_t n) {
            return luaL_checkudata(L, n, NULL);
	}

	template <>
	int check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	short int check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	char check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	unsigned int check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	unsigned short int check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	unsigned char check(lua_State* L, ptrdiff_t n) {
            return luaL_checkint(L, n);
	}

	template <>
	float check(lua_State* L, ptrdiff_t n) {
            return static_cast<float>(luaL_checknumber(L, n));
	}

	template<>
	double check(lua_State* L, ptrdiff_t n) {
            return luaL_checknumber(L, n);
	}

	template<>
	bool check(lua_State* L, ptrdiff_t n) {
            return static_cast<bool>(lua_toboolean(L, n));
	}

	template<>
	std::string check(lua_State *L, ptrdiff_t n) {
            return luaL_checkstring(L, n);
	}

	template <typename T>
	class check_adaptor {
	public:
            static T call(lua_State *L, ptrdiff_t n) {
                return check<T>(L, n);
            }
	};

	template <typename T>
	class check_adaptor<T*> {
	public:
            static T* call(lua_State *L, ptrdiff_t n) {
                int bp = lua_gettop(L);
                if (n < 0) n = bp + n + 1;
                if (lua_isuserdata(L, n)) {
                    return static_cast<T*>(lua_touserdata(L, n));
                }
                if (lua_istable(L, n)) {
                    lua_pushlightuserdata(L, (void*)0);
                    lua_gettable(L, n);
                    if (!lua_isuserdata(L, -1)) {
                        luaL_error(L, ":expect udata or class here.");
                    }
                    T** inst = static_cast<T**>(lua_touserdata(L, -1));
                    lua_settop(L, bp);
                    return *inst;
                }
                luaL_error(L, "expect udata or class here.");
            }
	};

	template<>
	class check_adaptor<const char*> {
	public:
            static const char* call(lua_State *L, ptrdiff_t n) {
                return luaL_checkstring(L, n);
            }
	};

	template<>
	class check_adaptor<void> {
	public:
            static void call(lua_State *L, ptrdiff_t n) {
            }
	};

	template <typename R, typename I>
	class func_adaptor {
	public:
            static int func(lua_State *L) {
                typename I::F f = reinterpret_cast<typename I::F>(lua_touserdata(L, lua_upvalueindex(1)));
                push(L, static_cast<R>(I::call(L, f)));
                return 1;
            }
	};

	template <typename I>
	class func_adaptor<void, I> {
	public:
            static int func(lua_State *L) {
                typename I::F f = reinterpret_cast<typename I::F>(lua_touserdata(L, lua_upvalueindex(1)));
                I::call(L, f);
                return 0;
            }
	};

	template <typename R>
	class arg_t0 {
	public:
            typedef R(*F) (void);
            static R call(lua_State *L, F func) {
                return func();
            }
	};

    }
}


namespace luah {
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

        template<typename T>
        method_importer<T>& operator<<(method_importer<T>& ip, method obj) {
            ip.add_method(obj);
            return ip;
        }

        void class_set_methods(lua_State *L, const method_set & set_, void * ins) {
            for (size_t i = 0; i < set_.ct; ++i) {
                lua_pushstring(L, set_.m_[i].name.c_str());
                lua_pushlightuserdata(L, ins);
                int n = 1;
                if (set_.m_[i].upval != NULL) {
                    ++n;
                    lua_pushlightuserdata(L, set_.m_[i].upval);
                }
                lua_pushcclosure(L, set_.m_[i].func, n);
                lua_settable(L, -3);
            }
        }

        template <typename T>
        struct class_constructor {
            static int call(lua_State *L) {
                // upval 1: creator
                // upval 2: method_se
                lua_remove(L, 1);
                
                // step 1: create a new instance
                typedef T * (*c_type) (lua_State *L);
                T * instance = reinterpret_cast<c_type>(lua_touserdata(L, lua_upvalueindex(1))) (L);
	    
                // step 2: create a new table ( as instance in lua )
                lua_newtable(L);
	    
                // step 3: add methods to table 
                class_set_methods(L, *static_cast<method_set*>(lua_touserdata(L, lua_upvalueindex(2))), instance);
	    
                // step 4: set table's metatable: to make __gc call destroy
                lua_pushlightuserdata(L, (void*)0);
                T** ptr = reinterpret_cast<T**>(lua_newuserdata(L, sizeof(T**)));
                *ptr = instance;
                lua_pushstring(L, "luah");
                lua_gettable(L, LUA_REGISTRYINDEX);
                lua_pushlightuserdata(L, reinterpret_cast<void*>(call));
                lua_gettable(L, -2);
                lua_setmetatable(L, -3);
                lua_pop(L, 1);
                lua_settable(L, -3);
                return 1;
            }
        };


    }
} 








