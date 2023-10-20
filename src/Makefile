CC = g++
BUILDNAME = Graph
CPPFLAGS = -std=c++11 -Wall -Werror 
HEADERFILES = $(wildcard */*.h) $(wildcard *.h) 
CPPLIBFILES = $(wildcard *.cpp)
CPPTASKSFILES = Task1/Task1.cpp Task2/Task2.cpp Task3/Task3.cpp Task4/Task4.cpp Task5/Task5.cpp Task6/Task6.cpp Task7/Task7.cpp Task8/Task8.cpp
OBJLIBFILES = $(patsubst %.cpp, %.o, $(CPPLIBFILES)) 
OBJTASKSFILES = Task1.o Task2.o Task3.o Task4.o Task5.o Task6.o Task7.o Task8.o

all: $(BUILDNAME)

$(BUILDNAME): $(OBJLIBFILES) $(OBJTASKSFILES)
	g++ $(OBJLIBFILES) $(OBJTASKSFILES) -o $(BUILDNAME)

$(OBJTASKSFILES): $(CPPTASKSFILES)
	$(CC) $(CPPFLAGS) -c $(CPPTASKSFILES)

$(OBJLIBFILES): $(CPPLIBFILES)
	$(CC) $(CPPFLAGS) -c $(CPPLIBFILES)

rebuild: clean all

clean: 
	rm -f $(BUILDNAME) *.o *.txt