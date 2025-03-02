CXX      = g++
CXXFLAGS_COMMON = -std=c++20 -Wall -Wpedantic -Wextra -fexceptions -fopenmp

# Change to debug to compile with debugging flags
MODE = release

ifeq ($(MODE),release)
	CXXFLAGS = $(CXXFLAGS_COMMON) -O3 -g -march=native -flto=auto -mavx2 -DNDEBUG
else
	CXXFLAGS = $(CXXFLAGS_COMMON) -g
endif

LDFLAGS  = 

TARGET = faco

BUILDDIR = build

SRCDIR = src

SOURCES = faco.cpp problem_instance.cpp local_search.cpp utils.cpp rand.cpp progargs.cpp env.cpp cross.cpp evaluator.cpp indi.cpp rand_.cpp kopt.cpp sort.cpp

OBJS = $(SOURCES:.cpp=.o)

OUT_OBJS = $(addprefix $(BUILDDIR)/,$(OBJS))

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OUT_OBJS)
	$(CXX) $(CXXFLAGS) $(OUT_OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
#	@mkdir -p results
#	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT_OBJS) $(TARGET)
