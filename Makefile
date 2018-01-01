LIBS= -lsfml-graphics -lsfml-window -lsfml-system
CXX=g++

HEADERS=src/headers/
SOURCES=src/
OBJDIR=obj/
LAZYDIR=lazy/

FILES=main vector2d body universe

OBJS=$(addsuffix .o, $(FILES))
LAZYS=$(addsuffix .i, $(FILES))
LAZYSLIST=$(addprefox $(LAZYDIR),$(LAZYS))

CXXFLAGS=-I $(HEADERS)  -w -g

OBJLIST=$(addprefix $(OBJDIR),$(OBJS))
OUTPUT=main
.SUFFIXES:
.SUFFIXES: .cpp .c .h .hpp .o .i

$(OBJDIR)%.o: $(SOURCES)%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ -I$(HEADERS)
$(LAZYDIR)%.i: $(SOUCES).cpp
	$(CXX) -E -P $(CXXFLAGS) $< -o $@ -I$(HEADERS)
$(OUTPUT): $(OBJLIST)
	$(CXX) $(OBJLIST) $(LIBS) $(LDFLAGS) -o $@
all: $(OUTPUT)
lazy: $(LAZYLIST)
clean:
	rm $(OBJLIST)
	rm $(OUTPUT)
run: $(OUTPUT)
	./$(OUTPUT) | awk '{print "\033[1;33m", $0}'
