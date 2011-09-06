#include "utest.h"
#include <vector>
#include <string>
#include <cstdio>

using namespace utest_inner;

std::vector<std::pair<std::string, TestFunc> > & tests() {
  static std::vector<std::pair<std::string, TestFunc> > test_arr;
  return test_arr;
}

void utest_inner::register_test_func(const char* name, TestFunc func) {
  tests().push_back(make_pair(std::string(name), func));
}

class UtestErrorCollector : public ErrorCollector {
public:
  static UtestErrorCollector & instance() {
    static UtestErrorCollector inst;
    return inst;
  }

  void collect(const char* file, int line, const char* msg) {
    fprintf(stderr, "[FAILED][%s][%s:%d]%s\n", case_name.c_str(), file, line, msg);
    ++error_cnt;
  }

  void new_case(const char * name) {
    error_cnt = 0;
    case_name = name;
  }

  bool failed() const {return error_cnt!=0;}

private:
  std::string case_name;
  int error_cnt;

  UtestErrorCollector() : error_cnt(0) {
  }

  UtestErrorCollector(const UtestErrorCollector&);
  void operator=(const UtestErrorCollector&);
};

int utest_run_all() {
  int failed = 0;
  int cnt = tests().size();
  for (int i = 0; i < cnt; ++i) {
    UtestErrorCollector::instance().new_case(tests()[i].first.c_str());
    tests()[i].second(&UtestErrorCollector::instance());
    if (UtestErrorCollector::instance().failed()) {
      ++ failed;
    }
    else {
      fprintf(stderr, "[PASS] %s\n", tests()[i].first.c_str());
    }
  }
  int ret;
  if (failed == 0) {
    fprintf(stderr, "[Result] Good! All %d tests passed.\n", cnt);
    ret = 0;
  }
  else {
    fprintf(stderr, "[Result] Total: %d, Passed: %d, Failed: %d\n", cnt, cnt - failed, failed);
    ret = 1;
  }
  return ret;
}
