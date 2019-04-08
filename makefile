CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0`

all: Demo	

Demo: demo.a
	gcc $(CFLAGS) -o demo demo.c demo.a $(LIBS) -Wall -g3 -O0 -ggdb3

demo.a: demo_root.o demo_frame.o
	ar rvs demo.a AtkRoot.o AtkFrame.o

demo_root.o: demo_root.h demo_root.c
	gcc $(CFLAGS) -c AtkRoot.c $(LIBS) -Wall -g3 -O0 -ggdb3
	
demo_frame.o: demo_frame.h demo_frame.c
	gcc $(CFLAGS) -c AtkFrame.c $(LIBS) -Wall -g3 -O0 -ggdb3	
	
clean:
	rm -fr AtkDemo *.o *.a
	
