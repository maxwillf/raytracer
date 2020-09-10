Target = raytracer 
INCLUDES = . 
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -ggdb -I $(INCLUDES) -fopenmp
DOCS = docs 
SRCDIR = src
OBJDIR = obj
BINDIR = bin 
OUTPUTPATH := bin/raytracer

HEADERS := $(wildcard $(INCLUDES) *.h)
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: project #docs

project: $(OBJECTS) | $(BINDIR)
	@echo "Linkin Files: " $(OBJECTS) $(DRIVER)
	@echo $(OUTPUTPATH)
	@$(CXX) $(OBJECTS) $(DRIVER)  $(CXXFLAGS) -o $(OUTPUTPATH)
	@echo "Linkin complete!"

docs: 
	@echo "Generating Documentation"
	@doxygen config

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@$(CXX) -w $(CXXFLAGS) -c $< -o $@
	@echo "Sources $<" 
	@echo "Compiling Files $< to  $@ "
	@echo "Compiled "$<" Succesfully!"

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: clean  clean_docs clean_proj

clean: clean_proj  #clean_docs

clean_proj:
	@rm -r $(OBJDIR) 
	@rm -r $(BINDIR) 
	@echo "Cleanup Complete!"

clean_docs: $(DOCS)
	@rm -r $(DOCS)
