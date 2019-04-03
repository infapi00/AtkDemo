CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0`

all:	
	gcc $(CFLAGS) -o AtkDemo AtkDemo.c AtkRoot.c $(LIBS) -Wall -g3 -O0 -ggdb3

clean:
	rm -fr AtkDemo
	
