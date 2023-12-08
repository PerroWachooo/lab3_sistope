FLAGS = -Wall -pthread -g
TARGET = lab3
SRCS = lab3.c lectura.c funciones.c salida.c globals.c
POSTFLAGS = -lm -no-pie
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	gcc $(FLAGS) -o $(TARGET) $(OBJS) $(POSTFLAGS)

clear:
	rm -f $(OBJS) $(TARGET)
