ifeq ($(strip $(GOOGLETEST_DIR)),)
  $(error GOOGLETEST_DIR not defined.  This must be set to the base directory which contains the Google Test framework.)
endif

GOOGLETEST_INCLUDE=-I$(GOOGLETEST_DIR)/include -I$(GOOGLETEST_DIR)
export GOOGLETEST_INCLUDE

MOCKCPP_INCLUDE=-I../include
export MOCKCPP_INCLUDE

CXXFLAGS+=-O0 -fprofile-arcs --coverage -g -stdlib=libc++ -std=c++11 $(GOOGLETEST_INCLUDE) $(MOCKCPP_INCLUDE)

GOOGLETEST_SOURCES=$(GOOGLETEST_DIR)/src/gtest_main.cc $(GOOGLETEST_DIR)/src/gtest-all.cc

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: ALL clean

ALL: mockcpp_test
	mkdir -p coverage
	lcov -b .. --directory . --zerocounters
	./mockcpp_test
	lcov -b .. --directory . --capture --output-file coverage/mockcpp_test.info
	lcov --remove coverage/mockcpp_test.info "/usr/*" -o coverage/mockcpp_test.info
	lcov --remove coverage/mockcpp_test.info "src/gtest*" -o coverage/mockcpp_test.info
	lcov --remove coverage/mockcpp_test.info "gtest/*" -o coverage/mockcpp_test.info
	lcov --remove coverage/mockcpp_test.info "test/*" -o coverage/mockcpp_test.info
	genhtml -o coverage coverage/mockcpp_test.info

mockcpp_test: $(OBJECTS) $(GOOGLETEST_SOURCES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o mockcpp_test $(OBJECTS) $(GOOGLETEST_SOURCES) -lstdc++

clean:
	rm -f mockcpp_test
	rm -f mockcpp_test.info
	rm -rf mockcpp_test.dSYM
	rm -f $(OBJECTS)
	rm -f *.gcda
	rm -f *.gcno
	rm -rf coverage
