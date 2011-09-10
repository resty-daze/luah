
test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f + 1
   test_set.f[id] = f
   test_set.msg[id] = msg
end

-- testcases
add("case1 failed", 
    function()
       local a = TestClass()
       a.set_a(1)
       x, y = a.my_method(2)
       return x == 1 and y == 2 and a.get_a() == 2
 end)
			       

-- run tests
for i, f in pairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end

