LuaH
=============

What is LuaH?
-------------
LuaH is a very simple library to use lua in C++.

Usage
-------------

    #include "luah.hpp"

    // export a function to lua
    luah::add_func(lua_state, "func_name", function);

    // export a function to lua(into a table)
    // stack_idx is current index of the table
    luah::add_func_table(lua_state, stack_idx, "func_name", function);

    // call a lua function
    int x = luah::call_func<int>(lua_state, "test", 6);


To do
----------------
- class support
- example
