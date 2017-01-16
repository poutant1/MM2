#Adjustable stuff
#NOTE: NEVER EVER USE TAB ANYWHERE ELSE THAN WHERE NECESSARY IN MAKEFILES
CC=g++
INCDIR=src
SRCDIR=src
OBJDIR=obj
BUILDDIR=build
BUILDNAME=main

#compiler flags
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic -I$(INCDIR)

#linker flags
LDFLAGS=-L/usr/local/lib 

#Linker libraries
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

#######################################
#DO NOT TOUCH BELOW
#######################################

.PHONY : clean checkdir run

#target exe
EXECUTABLE=$(BUILDDIR)/$(BUILDNAME)

#source list, autogenerated
SOURCES=$(wildcard $(SRCDIR)/*.cpp)

#object list, autogenerated from source list
OBJECTS= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

#when calling make
all:  checkdirs $(EXECUTABLE) 

#creation of target exe:linking
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ $(LIBS)

#compilation of object files from source
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CC) $(CPPFLAGS) -o $@ $<  

#make sure needed directories exist
checkdirs: $(BUILDDIR) $(OBJDIR)

#check build dir
$(BUILDDIR):
	mkdir -p $@

#check object dir
$(OBJDIR):
	mkdir -p $@

#remove object files & exe
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

#run exe
run: checkdirs $(EXECUTABLE)
	./$(EXECUTABLE)