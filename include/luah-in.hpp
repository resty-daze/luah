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

	void push(lua_State* L, const char* str) {
		lua_pushstring(L, str);
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
			return static_cast<T*>(luaL_checkudata(L, n, NULL));
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

