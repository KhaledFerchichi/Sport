# Makefile - VERSION AVEC .o VISIBLES
OBJ = test_ges_entraineurs.o gestion_entraineurs.o inscription.o

all: test

test: $(OBJ)
	gcc -o test_ges_entraineurs $(OBJ)

%.o: %.c
	gcc -c $<

run: test
	./test_ges_entraineurs

clean:
	rm -f *.o test_ges_entraineurs entraineurs.txt inscriptions.txt

