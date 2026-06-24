CXX       := g++
CXXFLAGS  := -Wall -Wextra -Werror -Iinclude -std=c++20 -g -MMD -fsanitize=address -fsanitize=undefined
LDFLAGS   := -fsanitize=address -fsanitize=undefined

TEST_SRC  := $(shell find tests -name 'test_*.cpp')
TEST_BINS := $(patsubst tests/test_%.cpp, bin/test_%, $(TEST_SRC))

DEP       := $(TEST_BINS:=.d)

.PHONY: all clean

all: $(TEST_BINS)

-include $(DEP)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

bin/test_%: tests/test_%.cpp $(OBJ)
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

clean:
	@rm -f $(DEP)
	@rm -rf bin/*
