CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0`

all: Demo	

Demo: MyAtk.a
	gcc $(CFLAGS) -o AtkDemo AtkDemo.c MyAtk.a $(LIBS) -Wall -g3 -O0 -ggdb3

MyAtk.a: AtkRoot.o AtkFrame.o
	ar rvs MyAtk.a AtkRoot.o AtkFrame.o

AtkRoot.o: AtkRoot.h AtkRoot.c
	gcc $(CFLAGS) -c AtkRoot.c $(LIBS) -Wall -g3 -O0 -ggdb3
	
AtkFrame.o: AtkFrame.h AtkFrame.c
	gcc $(CFLAGS) -c AtkFrame.c $(LIBS) -Wall -g3 -O0 -ggdb3	
	
clean:
	rm -fr AtkDemo *.o *.a
	
