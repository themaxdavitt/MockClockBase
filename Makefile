# Build and test Session class

.PHONY: all
all : Session_t

Session_t : Session_t.o
	g++ Session_t.o -o Session_t

Session_t.o : Session_t.cpp
	g++ -std=c++11 -c Session_t.cpp

.PHONY: test
test : Session_t
	./Session_t

.PHONY: clean
clean :
	@rm -f Session_t Session_t.o
