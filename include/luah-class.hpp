#ifndef LUAH_CLASS_
#define LUAH_CLASS_

namespace luah {
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

        //        template <typename F>
        //        internal::method_importer<T>& operator[](F);

        internal::method_importer<T>& operator[](T* (*f) (lua_State * L)) {
            creator_ = f;
            return importer_;
        }
 
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
        template <typename A0, typename A1>
        internal::method_importer<T>& operator[](ctor<A0, A1>) {
            creator_ = internal::creator_1<T, A0, A1>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2>) {
            creator_ = internal::creator_1<T, A0, A1, A2>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2, typename A3>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2, A3>) {
            creator_ = internal::creator_1<T, A0, A1, A2, A3>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2, typename A3, typename A4>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2, A3, A4>) {
            creator_ = internal::creator_1<T, A0, A1, A2, A3, A4>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2, A3, A4, A5>) {
            creator_ = internal::creator_1<T, A0, A1, A2, A3, A4, A5>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2, A3, A4, A5, A6>) {
            creator_ = internal::creator_1<T, A0, A1, A2, A3, A4, A5, A6>;
            return importer_;
        }
        template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
        internal::method_importer<T>& operator[](ctor<A0, A1, A2, A3, A4, A5, A6, A7>) {
            creator_ = internal::creator_1<T, A0, A1, A2, A3, A4, A5, A6, A7>;
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
 
        static int destroy(lua_State *L) {
            T* ptr = *internal::check_adaptor<T**>::call(L, 1);
            delete ptr;
            return 0;
        }

        void open(const char* class_name) {
            lua_pushstring(L_, "luah");
            lua_pushstring(L_, "luah");
            lua_gettable(L_, LUA_REGISTRYINDEX);
            if (lua_isnil(L_, -1)) {
                lua_pop(L_, 1);
                lua_newtable(L_);
            }

            lua_pushlightuserdata(L_, reinterpret_cast<void*>(internal::class_constructor<T>::call));
            lua_newtable(L_);
            lua_pushstring(L_, "__gc");
            lua_pushcfunction(L_, destroy);
            lua_settable(L_, -3);
            lua_settable(L_, -3);
            lua_settable(L_, LUA_REGISTRYINDEX);
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
}


#endif










