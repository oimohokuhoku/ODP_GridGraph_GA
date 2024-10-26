SOURCES = test.cpp
COMPILE_OPTION = -O0 -g
LIB = -L /usr/local/lib -L ../../lib -lgtest -lgtest_main -lpthread -lodpGridGraphs

main: 
	g++ $(SOURCES) $(COMPILE_OPTION) $(LIB) -o test

clean:
	rm test.exe