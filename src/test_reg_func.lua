test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f + 1
   test_set.f[id] = f
   test_set.msg[id] = msg
end

-- testcases
add("test int func", function() return test_int_func() == 6 end)
add("test void func", function() 
			 test_void_func()
			 return true 
		   end)

add("test sqr func", function()
			return my_sqr(3) == 9 and my_sqr(0.5)==0.25
		  end)

add("test str func", function()
			return double_func("str_c")=="str_cstr_c"
		  end)

-- run tests
for i, f in ipairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end
 


