test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f + 1
   test_set.f[id] = f
   test_set.msg[id] = msg
end

-- testcases
add("test int func", function() return t.tint() == 6 end)
add("test void func", function() 
			 t.tvoid()
			 return true 
		   end)

add("test sqr func", function()
			return t.mysqr(3) == 9 and t.mysqr(0.5)==0.25
		  end)

add("test str func", function()
			return t.double("str_c")=="str_cstr_c"
		  end)

-- run tests
for i, f in ipairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end
 


