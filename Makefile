CC=gcc
CFLAGS=-Wall -ansi -pedantic
	
game: champion.o protection.o soin.o arme.o initChampion.o game.o duel.o affiche.o
	$(CC) -o game game.o champion.o protection.o soin.o arme.o initChampion.o duel.o affiche.o

champion.o: champion.c champion.h
	$(CC) $(CFLAGS) -c champion.c

protection.o: protection.c protection.h
	$(CC) $(CFLAGS) -c protection.c

soin.o: soin.c soin.h 
	$(CC) $(CFLAGS) -c soin.c
	
arme.o: arme.c arme.h 
	$(CC) $(CFLAGS) -c arme.c
	
initChampion.o: initChampion.c initChampion.h champion.h protection.h soin.h arme.h
	$(CC) $(CFLAGS) -c initChampion.c
	
duel.o: duel.c duel.h initChampion.c initChampion.h
	$(CC) $(CFLAGS) -c duel.c
	
affiche.o: affiche.c affiche.h duel.c duel.h
	$(CC) $(CFLAGS) -c affiche.c

game.o: game.c initChampion.h champion.h protection.h soin.h arme.h duel.h affiche.h
	$(CC) $(CFLAGS) -c game.c

clean:
	@rm *.o 2> /dev/null || true
	@echo "cleaning done"
