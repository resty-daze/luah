
test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f
   test_set.f[id] = f
   test_set.msg[id] = msg
end

-- testcases
add("testclass, seta_geta", 
    function()
       local a = TestClass()
       a.set_a(5);
       return a.get_a()== 5
 end)
			       

-- run tests
for i, f in pairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end

-- ensure __gc all called
collectgarbage("collect")

