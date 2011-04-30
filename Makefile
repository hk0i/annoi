CC=gcc
CFLAGS=`sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_image -lSDL_mixer
OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))

annoi: $(OBJS)
	gcc -o annoi $(OBJS) $(CFLAGS) $(LIBS)

clean:
	rm -rf $(OBJS) *~ *.o annoi
