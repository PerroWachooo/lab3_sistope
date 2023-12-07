FLAGS = -Wall -pthread -g
TARGET = programa
SRCS = lab3.c lectura.c funciones.c salida.c
POSTFLAGS = -lm -no-pie
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	gcc $(FLAGS) -o $(TARGET) $(OBJS) $(POSTFLAGS)

clear:
	rm -f $(OBJS) $(TARGET)