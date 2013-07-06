#CROSS           = arm-linux-gnueabihf-
CROSS            =
CC               = $(CROSS)gcc
CPPC		 = $(CROSS)g++
OBJS             = main.o controller.o
TARGET           = radicon_controller
UNZIP            = unzip
XIVELYLIBDIR     = ./libxively/src/libxively
XIVELYLIB        = $(XIVELYLIBDIR)/libxively.a
ARDUINOLIBBASEDIR = ./libarduino
ARDUINOLIBDIR	 = $(ARDUINOLIBBASEDIR)/static
ARDUINOLIB	 = $(ARDUINOLIBDIR)/libarduino.a
ARDUINOINCDIR	 = $(ARDUINOLIBBASEDIR)/include
CFLAGS           = -Wall -I. -I$(XIVELYLIBDIR) -L$(XIVELYLIBDIR) -I$(ARDUINOINCDIR) -L$(ARDUINOLIBDIR) -lxively -larduino -lpthread
CFLAGS          += -Os -g

.PHONY: clean purge all

all: $(TARGET)

.cpp.o:
	@echo "========================================================"
	$(CPPC) $(CFLAGS) -c $<

.c.o:
	@echo "========================================================"
	$(CC) $(CFLAGS) -c $<

$(XIVELYLIB):
	make -C $(XIVELYLIBDIR)

$(ARDUINOLIB):
	make -C $(ARDUINOLIBDIR)

$(TARGET): $(XIVELYLIB) $(ARDUINOLIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	@echo "Clean project =========================================="
	rm -fr $(TARGET) $(OBJS)
	make -C $(XIVELYLIBDIR) clean
	make -C $(ARDUINOLIBBASEDIR) clean

purge:
	rm -f *~ *bak

depend: $(OBJS:.o=.cpp)
	-@ makedepend -- $(CFLAGS) -- -Y $^ -f Makefile 2> /dev/null
# DO NOT DELETE
