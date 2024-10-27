
# Setting ####################################################################
CXX = g++

EXE_NAME    = grid
SOURCE_FILES = main.cpp

OBJECT_FILES_DIR = .objectFiles

DEBUG_COMPILE_OPTION   = -O0 -g -Wall -Wextra -Wshadow -Wfloat-equal
RELEASE_COMPILE_OPTION = -O3 -mtune=native -march=native

LIBRARYS = -L libs/odpGridGraphGAs/lib/ -lodpGridGraphGAs
LIBRARYS += -L libs/commonLibraries/lib/ -lcommonLibraries
INCLUDE_PATH = $(wildcard libs/*/include)
#############################################################################
#############################################################################

# convert cpp filepath to object filepath
# example: aaa/hoge.cpp -> objectFiles/aaa/hoge.o
OBJECT_FILES = $(addprefix $(OBJECT_FILES_DIR)/, $(patsubst %.cpp, %.o, $(SOURCE_FILES)))
INCLUDE_OPTIONS = $(addprefix -I, $(INCLUDE_PATH))

.PHONY: debug
debug: debugEcho $(OBJECT_FILES)
	@echo "Linking object files"
	@$(CXX) \
		$(DEBUG_COMPILE_OPTION) \
		$(OBJECT_FILES) \
		$(LIBRARYS) \
		-o $(EXE_NAME)

.PHONY: release
release:
	@echo "Building in Release mode."
	@echo "It takes a long time for the process to be completed."
	@$(CXX) \
		$(RELEASE_COMPILE_OPTION) \
		$(SOURCE_FILES) \
		$(LIBRARYS) \
		-o $(EXE_NAME) \
		-I ${INCLUDE_OPTIONS}

.PHONY: clean
clean:
	@echo "Remove object files and directory"
	@rm -rf $(OBJECT_FILES_DIR)

$(OBJECT_FILES_DIR)/%.o: %.cpp
	@echo "Compiling $<"
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(CXX) $(DEBUG_COMPILE_OPTION) -o $@ -c $< $(INCLUDE_OPTIONS)

debugEcho: 
	@echo "Building in Debug Mode"
