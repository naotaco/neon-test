SRCS:=neon01.cpp
CXX=clang++
TARGET=neon-test
OBJS:=$(SRCS:.cpp=.o)

CXXFLAGS:= -Wall -mfloat-abi=hard -mfpu=neon -march=armv8-a

all: $(OBJS)
	$(CXX) -o $(TARGET) $<

main.o:
	$(CXX) $(CXXFLAGS) -c -Wall -o $*.o $*.cpp

clean: $(OBJS) $(TARGET)
	rm -rf $(OBJS) $(TARGET)
