CC = gcc
CFLAGS = -O0 -g -Wall
TARGET = libhttp.a
OBJS = api.o http.o llhttp.o

$(TARGET): $(OBJS)
	# build library
	$(AR) rcs $(TARGET) $(OBJS)
	# $(RANLIB) $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)