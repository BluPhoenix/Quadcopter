CC=g++

BDIR=./build

DEPS=imu.h \
	 motorcontrol.h \
	 pid.h \
	 sensor.h \
	 spi.h \
	 vector.h \
	 fifo/Input.h

_OBJ=imu.o \
	motorcontrol.o \
	pid.o \
	sensor.o \
	spi.o \
	vector.o \
	fifo/Input.o

OBJ=$(patsubst %, $(BDIR)/%, $(_OBJ))

$(BDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

all: $(OBJ)
	$(CC) - o $(BDIR)/main $(OBJ)

test: $(OBJ) $(BDIR)/test.o
	$(CC) -o $(BDIR)/test $(OBJ) $(BDIR)/test.o -lrt

.PHONY: clean

clean:
	rm -f $(BDIR)/*
