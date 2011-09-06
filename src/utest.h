// utest.h
// unit test functions

namespace utest_inner {
struct ErrorCollector {
  virtual void collect(const char* file, int line, const char* msg) = 0;
};

typedef void (*TestFunc) (ErrorCollector*);
void register_test_func(const char* name, TestFunc func);
}

int utest_run_all();

#define TEST_CASE(name) \
  struct utest_testcase_register_##name {				\
    utest_testcase_register_##name() {utest_inner::register_test_func(#name,run);} \
    static void run(utest_inner::ErrorCollector*);			\
  } utest_testcase_register_instance_##name;				\
  void utest_testcase_register_##name::run(utest_inner::ErrorCollector * __utest_collector)

#define ASSERT_TRUE(exp) \
  if (!(exp))							\
    return __utest_collector->collect(__FILE__, __LINE__, #exp)

#define ASSERT_TRUE_MSG(exp, msg) \
  if (!(exp))							\
    return __utest_collector->collect(__FILE__, __LINE__, msg)

