
test_set={f={}, msg={}}
function add(msg, f) 
   local id = #test_set.f + 1
   test_set.f[id] = f
   test_set.msg[id] = msg
end

-- testcases
add("testudc, udc1",
    function()
       local a = TestClass()
       a.set_a(5)
       return a.get_a() == 5
 end)

add("testudc, udc2",
    function()
       local a = TestClass(5)
       return a.get_a() == 5
 end)

add("testudc, udc3",
    function()
       local a = TestClass(6)
       local b = TestClass(a)
       return b.get_a() == 6
 end)
			       

-- run tests
for i, f in pairs(test_set.f) do
   if not f() then
      error(test_set.msg[i])
   end
end

