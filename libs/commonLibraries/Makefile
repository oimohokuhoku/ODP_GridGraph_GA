
# Setting ####################################################################
CXX = g++

LIB_NAME    = lib/libcommonLibraries.a
SOURCE_FILES = $(wildcard src/*.cpp)
OBJECTS_DIR = .objectFiles
DEBUG_CFLAGS   = -O0 -g -Wall -Wextra -Wshadow -Wfloat-equal
RELEASE_CFLAGS = -O3 -mtune=native -march=native
#############################################################################
#############################################################################
# convert cpp filepath to object filepath
# example: aaa/hoge.cpp -> objectFiles/aaa/hoge.o
OBJECT_FILES = $(addprefix $(OBJECTS_DIR)/, $(patsubst %.cpp, %.o, $(SOURCE_FILES)))

.PHONY: release
release: launchReleaseMode $(OBJECT_FILES)
	@ar rcs $(LIB_NAME) $(GRID_GRAPH_LIB) $(OBJECT_FILES)

.PHONY: debug
debug: launchDebugMode $(OBJECT_FILES)
	@ar rcs $(LIB_NAME) $(GRID_GRAPH_LIB) $(OBJECT_FILES)
	
.PHONY: clean
clean:
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(LIB_NAME)
	@echo "Created files is removed."

# Private #################################################################################
launchReleaseMode: 
	@echo "Building in Release Mode"
	$(eval CFLAGS := $(RELEASE_CFLAGS))
	@echo "Compile Options: $(CFLAGS)"

launchDebugMode: 
	@echo "Building in Debug Mode"
	$(eval CFLAGS := $(DEBUG_CFLAGS))
	@echo "Compile Options: $(CFLAGS)"

$(OBJECTS_DIR)/%.o: %.cpp
	@echo "Compiling $<"
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(CXX) $(CFLAGS) -o $@ -c $<
