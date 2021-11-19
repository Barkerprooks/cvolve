cc=gcc
cf=-Wall -Werror -g -I $(CURDIR)/include
objs=main.o genome.o medium.o nuralnet.o

all: clean cvolve mvobj

cvolve: $(objs)
	$(cc) $(cf) -o $@ $^ -lm

main.o: src/main.c
	$(cc) $(cf) -c $<

genome.o: src/genome.c
	$(cc) $(cf) -c $<

medium.o: src/medium.c
	$(cc) $(cf) -c $<

nuralnet.o: src/nuralnet.c
	$(cc) $(cf) -c $<

mvobj:
	mkdir -p obj
	mv *.o obj

clean:
	rm -rf obj
	rm -rf *.o
	rm -rf cvolve
