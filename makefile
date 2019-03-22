CFLAGS = `pkg-config --cflags atk-bridge-2.0`
LIBS = `pkg-config --libs atk-bridge-2.0`

all:	
	gcc $(CFLAGS) -o AtkDemo.o AtkDemo.c $(LIBS)

clean:
	rm -fr AtkDemo.o
	