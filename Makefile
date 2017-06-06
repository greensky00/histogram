LDFLAGS = -pthread
CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src -I./tests \
	--std=c++11 \

CXXFLAGS += -Wall
#CXXFLAGS += -O3

HISTOGRAM_TEST = \
	tests/histogram_test.o \

PROGRAMS = \
	tests/histogram_test \

all: $(PROGRAMS)

tests/histogram_test: $(HISTOGRAM_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so