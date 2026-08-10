CC      = gcc
# deve utilizar os comando shell para pegar os resultados de compilação
# do allegro no terminal
CFLAGS  = -Wall -Wextra -Werror -g -std=c99 $(shell pkg-config --cflags allegro-5 allegro_image-5)
LDLIBS  = -lm $(shell pkg-config --libs allegro-5 allegro_image-5)

MAIN = tarzan_federal
ENTREGA = $(MAIN)

# lista de arquivos cabecalhos
HDR = grafico.h 

# lista de arquivos-objetos
OBJ = grafico.o main.o  

# construir o executavel
$(MAIN): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# regra genérica para construir (.o) a partir dos (.c)
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $<

# contruir TADS
grafico.o: grafico.c grafico.h

# executar 
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind 
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo tgz para entregar
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h makefile /tmp/$(USER)/$(ENTREGA)
	cp -r imagens /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) $(ENTREGA).tgz