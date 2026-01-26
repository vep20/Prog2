# Definição de variável para o comando do Git
GIT = git

# Target para fazer push das mudanças
push:
	$(GIT) add .
	$(GIT) commit -m "Commit automático"
	$(GIT) push

# Target para fazer pull das mudanças
pull:
	$(GIT) pull

# Target padrão que executa push e pull
all: pull push

.PHONY: push pull all

