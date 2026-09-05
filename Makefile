# ──────────────────────────────────────────
# Compiler & Flags
# ──────────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -I. -Iinclude
COVFLAGS = $(CXXFLAGS) --coverage -fprofile-arcs -ftest-coverage -O0

TARGET     = taskforge
COV_DIR    = coverage
COV_TARGET = $(COV_DIR)/taskforge_cov

# Automatically detect all .cpp files in root and src/
SRCS     = $(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJS     = $(SRCS:.cpp=.o)
COV_OBJS = $(addprefix $(COV_DIR)/,$(SRCS:.cpp=.o))

# ──────────────────────────────────────────
# Default Build
# ──────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ──────────────────────────────────────────
# Execution & Debugging
# ──────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

valgrind: $(TARGET)
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--error-exitcode=1 \
		./$(TARGET)

# ──────────────────────────────────────────
# Coverage Build + HTML Report
# ──────────────────────────────────────────
$(COV_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(COVFLAGS) -c $< -o $@

$(COV_TARGET): $(COV_OBJS)
	$(CXX) $(COVFLAGS) -o $(COV_TARGET) $(COV_OBJS)

coverage: $(COV_TARGET)
	./$(COV_TARGET)
	lcov --capture --directory $(COV_DIR) --output-file $(COV_DIR)/coverage.info --rc lcov_branch_coverage=1
	lcov --remove $(COV_DIR)/coverage.info '/usr/*' --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR) --branch-coverage
	@echo "----------------------------------------------------"
	@echo "Coverage report ready: open $(COV_DIR)/index.html"
	@echo "----------------------------------------------------"

coverage-html: coverage

# ──────────────────────────────────────────
# Clean
# ──────────────────────────────────────────
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(COV_DIR)

.PHONY: all run gdb valgrind coverage coverage-html clean