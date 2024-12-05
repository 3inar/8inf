SRC := src/lexer_preprocessor.c src/rts.c src/handlers.c
INC := inc/lexer_preprocessor.h inc/rts.h inc/handlers.h
# FLAGS := -g

8inf: 8inf.c $(SRC) $(INC)
	gcc $(FLAGS) -Iinc 8inf.c $(SRC) -o 8inf

clean:
	rm 8inf

.PHONY: clean
