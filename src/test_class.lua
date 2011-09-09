
test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f + 1
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

add("testclass, testclassb",
    function()
       local a = TestClass()
       local b = TestClassB(a)
       a.set_a(4)
       b.incr_by_n(5)
       return a.get_a() == 9
 end)

add("testclass, testclassb2",
    function()
       local a = TestClass()
       local b = TestClassB(a)
       local c = TestClass()
       a.set_a(3)
       c.set_a(5)
       b.mul_tcb(c)
       return a.get_a() == 15
 end)
			       

-- run tests
for i, f in pairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end

-- ensure __gc all called
collectgarbage("collect")

