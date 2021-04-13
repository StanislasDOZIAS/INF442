NAME = inf442
ZIP_FILE = DOZIAS_DURAND_$(NAME).zip
SRCDIR = src/
BIN = bin/
DOCS = doc/
#INCL = include/
SCRIPTS = recolte_data.sh

FILES := $(shell find $(SRCDIR) -name '*.cpp')
OBJ:= $(FILES:$(SRCDIR)%.cpp=$(BIN)%.o)

CC = g++
FLAGS = -std=c++11
LDLIBS = -D_REENTRANT -lm -D_GNU_SOURCE

.PHONY: all
all: $(NAME) scripts

$(NAME): $(OBJ)
	@printf "[\e[1;34mEn cours\e[0m] Assemblement\n"
#	$(CC) -o $(NAME) $(FLAGS) -I $(INCL) $(OBJ) $(LDLIBS)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LDLIBS)
	@printf "[\e[1;32mOK\e[0m] Assemblement finie\n"

$(BIN)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(dir $@)
#	$(CC) -c $(FLAGS) -I $(INCL) -o $@ $< $(LDLIBS)
	$(CC) -c $(FLAGS) -o $@ $< $(LDLIBS)

.PHONY: scripts
scripts:
	@sh $(SCRIPTS)

.PHONY: debug
debug: FLAGS += -D D_FLAG
debug: $(NAME)

.PHONY: log
log: FLAGS += -D D_FLAG -D D_LOGFILE
log: $(NAME)

.PHONY: clean
clean:
	@printf "[\e[1;34mEn cours\e[0m] Suppression des binaires\n"
	@rm -rf $(BIN)
	@printf "[\e[1;32mOK\e[0m] Suppression finie\n"

.PHONY: cleandoc
cleandoc:
	@printf "[\e[1;34mEn cours\e[0m] Suppression de la documentation\n"
	@rm -rf $(DOCS)
	@printf "[\e[1;32mOK\e[0m] Suppression finie\n"

.PHONY: cleanall
cleanall: clean cleandoc
	@rm -rf $(NAME)

.PHONY: re
re: cleanall $(NAME)
	@rm -rf $(ZIP_FILE)

.PHONY: doc
doc: cleandoc
	@printf "[\e[1;34mEn cours\e[0m] Création de la documentation\n"
	@doxygen documentation
	@printf "[\e[1;32mOK\e[0m] Création finie\n"

.PHONY: zip
zip:
	@printf "[\e[1;34mEn cours\e[0m] Début du zippage\n"
#	@zip -r $(ZIP_FILE) README.md Makefile $(SRCDIR) documentation $(INCL) DOZIAS_DURAND_rapport.pdf
	@zip -r $(ZIP_FILE) README.md Makefile $(SRCDIR) documentation DOZIAS_DURAND_rapport.pdf
	@printf "[\e[1;32mOK\e[0m] Zippage finie\n"