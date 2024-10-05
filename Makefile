
# Setting ####################################################################
CXX = g++

EXE_NAME    = grid
INCLUDE_DIR = ./

OBJECT_FILES_DIR = _objectFiles

DEBUG_COMPILE_OPTION   = -O0 -g -Wall -Wextra -Wshadow -Wfloat-equal
RELEASE_COMPILE_OPTION = -O3 -mtune=native -march=native

SOURCE_FILES = main.cpp
SOURCE_FILES += $(wildcard odpGridGraphGAs/src/*.cpp)
SOURCE_FILES += $(wildcard odpGridGraphGAs/src/*/*.cpp)
SOURCE_FILES += $(wildcard commonLib/*/*.cpp)

GRID_GRAPH_LIB = -L odpGridGraphs/lib/ -lodpGridGraphs
#############################################################################
#############################################################################

# convert cpp filepath to object filepath
# example: aaa/hoge.cpp -> objectFiles/aaa/hoge.o
OBJECT_FILES = $(addprefix $(OBJECT_FILES_DIR)/, $(patsubst %.cpp, %.o, $(SOURCE_FILES)))

.PHONY: debug
debug: debugEcho $(OBJECT_FILES)
	@echo "Linking object files"
	@$(CXX) \
		$(DEBUG_COMPILE_OPTION) \
		$(OBJECT_FILES) \
		$(GRID_GRAPH_LIB) \
		-o $(EXE_NAME) \
		-I ${INCLUDE_DIR}

.PHONY: release
release:
	@echo "Building in Release mode."
	@echo "It takes a long time for the process to be completed."
	@$(CXX) \
		$(RELEASE_COMPILE_OPTION) \
		$(SOURCE_FILES) \
		$(GRID_GRAPH_LIB) \
		-o $(EXE_NAME) \
		-I ${INCLUDE_DIR}

.PHONY: clean
clean:
	@echo "Remove object files and directory"
	@rm -rf $(OBJECT_FILES_DIR)

$(OBJECT_FILES_DIR)/%.o: %.cpp
	@echo "Compiling $<"
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(CXX) $(DEBUG_COMPILE_OPTION) -o $@ -c $< -I $(INCLUDE_DIR)

debugEcho: 
	@echo "Building in Debug Mode"
