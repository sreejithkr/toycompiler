OBJECTS= ../build/compiler.o ../build/cprocess.o ../build/lex_process.o ../build/lexer.o ../build/helpers/buffer.o ../build/helpers/vector.o ../build/lexer_number_token.o
INCLUDES= -I./

all: ${OBJECTS}
	gcc -g main.c ${INCLUDES} ${OBJECTS} -g -o ../out/main

../build/compiler.o: ./compiler.c
	gcc ./compiler.c ${INCLUDES} -o ../build/compiler.o -g -c 

../build/cprocess.o: ./cprocess.c
	gcc ./cprocess.c ${INCLUDES} -o ../build/cprocess.o -g -c 

../build/lexer.o: ./lexer/lexer.c
	gcc ./lexer/lexer.c ${INCLUDES} -o ../build/lexer.o -g -c 

../build/lex_process.o: ./lexer/lex_process.c
	gcc ./lexer/lex_process.c ${INCLUDES} -o ../build/lex_process.o -g -c 

../build/lexer_number_token.o: ./lexer/lexer_number_token.c
	gcc ./lexer/lexer_number_token.c ${INCLUDES} -o ../build/lexer_number_token.o -g -c 

../build/helpers/buffer.o: ./helpers/buffer.c
	gcc ./helpers/buffer.c ${INCLUDES} -o ../build/helpers/buffer.o -g -c 

../build/helpers/vector.o: ./helpers/vector.c
	gcc ./helpers/vector.c ${INCLUDES} -o ../build/helpers/vector.o -g -c 

clean:
	rm ../out/main
	rm -rf ${OBJECTS}
	rm -rf ../out/main.sSYM/

