
CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -g -std=c99

ALLEGRO = allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5
CPPFLAGS = -Icabecalhos $(shell pkg-config --cflags $(ALLEGRO))
LDLIBS = -lm $(shell pkg-config --libs $(ALLEGRO))

MAIN = jogo
ENTREGA = $(MAIN)

COD_DIR = cod_font
HDR_DIR = cabecalhos
REC_DIR = recursos
OBJ_DIR = obj

# Arquivos fonte
SRC = jogo.c $(wildcard $(COD_DIR)/*.c)

# Arquivos objeto
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# Arquivos de dependencias
DEP = $(OBJ:.o=.d)

# Regra padrao
all: $(MAIN)

# Gerar executavel
$(MAIN): $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)

# Gerar arquivos objeto
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Incluir dependencias dos cabecalhos
-include $(DEP)

# Executar programa
run: $(MAIN)
	./$(MAIN)

# Testar com Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# Gerar arquivo para entrega
entrega: $(MAIN)
	mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp jogo.c Makefile /tmp/$(USER)/$(ENTREGA)
	cp -r $(COD_DIR) $(HDR_DIR) $(REC_DIR) /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)/$(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# Limpar arquivos temporarios
clean:
	rm -f *~ $(MAIN) $(ENTREGA).tgz
	rm -rf $(OBJ_DIR)

.PHONY: all run valgrind entrega clean
