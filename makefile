CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0`

all:	
	gcc $(CFLAGS) -o AtkDemo.o AtkDemo.c $(LIBS)

clean:
	rm -fr AtkDemo.o
	