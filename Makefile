CXXFLAGS =  -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE 
CXX = g++

TEST = True

TEST_NAME = test_print_stack

OBJDIR = object_files
STKDIR = stack

SOURCES = $(STKDIR)/stack.cpp $(STKDIR)/print.cpp  $(STKDIR)/canary.cpp $(STKDIR)/hash.cpp
OBJECTS = $(OBJDIR)/stack.o $(OBJDIR)/print.o  $(OBJDIR)/canary.o $(OBJDIR)/hash.o

ifeq ($(TEST), True)
	SOURCES += test.cpp
	OBJECTS += $(OBJDIR)/test.o
else 
	SOURCES += main.cpp
	OBJECTS += $(OBJDIR)/main.o
endif


CANARY_PROTECTION = True
HASH_PROTECTION   = True
STACK_DUMP 		  = True
STDOUT_DUMP 	  = True
HASH_DEBUG 		  = True

ifeq ($(HASH_DEBUG), True)
	CXXFLAGS += -DHASH_DEBUG
endif

ifeq ($(CANARY_PROTECTION), True)
	CXXFLAGS += -DCANARY_PROTECTION
endif

ifeq ($(HASH_PROTECTION), True)
	CXXFLAGS += -DHASH_PROTECTION
endif

ifeq ($(STACK_DUMP), True)
	CXXFLAGS += -DSTACK_DUMP
endif

ifeq ($(STDOUT_DUMP), True)
	CXXFLAGS += -DSTDOUT_DUMP
endif

all: main.exe
	main.exe $(TEST_NAME)

main.exe: $(OBJECTS)
	@echo $(CXX) $^ [CXXFLAGS] -o $@ 
	@$(CXX) $^ $(CXXFLAGS) -o $@


$(OBJDIR)/%.o: $(STKDIR)/%.cpp
	@echo [CXX] [CXXFLAGS] -c $@ -o $< 
	@$(CXX) $(CXXFLAGS) -c -o  $@ $< 

$(OBJDIR)/%.o: %.cpp
	@echo [CXX] [CXXFLAGS] -c $@ -o $< 
	@$(CXX) $(CXXFLAGS) -c -o  $@ $< 

.PHONY: clean_exe
clean_exe:
	@echo "all .exe files are cleaned"
	@echo ""
	
	rm -rf *.exe

.PHONY: clean_object_files
clean_object_files:
	@echo "all object files (.o) are cleaned"
	@echo ""
	
	rm -rf *.o 

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf *.exe

.PHONY: create_documentation
create_docs: 
	doxygen Doxyfile
	@echo ""
	@echo "documentation is updated"
