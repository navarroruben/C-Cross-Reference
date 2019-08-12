all: ex1-cpp.exe

ex1-cpp.exe: lex.yy.cc
	g++ -o $@ $< -lfl

lex.yy.cc: ex1-cpp.l
	flex -o $@ $< 
clean: 
	rm -f ex1-cpp.exe *~ lex.yy* 


