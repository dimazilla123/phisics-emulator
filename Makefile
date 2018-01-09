LIBS= -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS = -L~/Documents/Programs/builds/sfml-2.4.2/build/lib/
CXX=g++

HEADERS=src/headers/
SOURCES=src/
OBJDIR=obj/

FILES=main vector2d body universe interface

OBJS=$(addsuffix .o, $(FILES))

CXXFLAGS=-I $(HEADERS) -g 

OBJLIST=$(addprefix $(OBJDIR),$(OBJS))
OUTPUT=main
.SUFFIXES:
.SUFFIXES: .cpp .c .h .hpp .o .i

$(OBJDIR)%.o: $(SOURCES)%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ -I$(HEADERS)
$(LAZYDIR)%.i: $(SOUCES).cpp
	$(CXX) -E -P $(CXXFLAGS) $< -o $@ -I$(HEADERS)
$(OUTPUT): $(OBJLIST)
	$(CXX) $(OBJLIST) $(LDFLAGS) $(LIBS)  -o $@
all: $(OUTPUT)
clean:
	rm $(OBJLIST)
	rm $(OUTPUT)
run: $(OUTPUT)
	./$(OUTPUT)
