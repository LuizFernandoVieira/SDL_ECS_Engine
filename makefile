CXX = clang++
SDL = -framework SDL2
SDL_image = -framework SDL2_image
SDL_mixer = -framework SDL2_mixer
SDL_ttf = -framework SDL2_ttf

SRCDIR = src
BUILDDIR = build
EXE = bin/prog

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CXXFLAGS = -Wall -c -std=c++11
LIB = $(SDL) $(SDL_image)

INC = -I include


$(EXE): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(EXE) $(LIB)"; $(CXX) $^ -o $(EXE) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(EXE)"; $(RM) -r $(BUILDDIR) $(EXE)

.PHONY: clean