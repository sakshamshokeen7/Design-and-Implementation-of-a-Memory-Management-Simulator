CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include

TARGET = memsim

SRCS = src/main.cpp \
       src/allocator/allocator.cpp \
       src/buddy/buddy.cpp \
       src/cache/cache.cpp \
       src/virtual_memory/vm.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET).exe

run: $(TARGET)
	.\$(TARGET).exe
