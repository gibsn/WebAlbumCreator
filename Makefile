CXX = g++
CXXFLAGS = -g -Wall
CXXFLAGS += -Wno-unused-variable -Wno-unused-value -std=c++98 -fpermissive
#Needed for proper libarchive work
CXXFLAGS += -D_FILE_OFFSET_BITS=64

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
DEPS_DIR = deps
BRIDGE_DIR = bridge

SRC_MODULES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_MODULES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_MODULES:.cpp=.o)))
DEPS_MODULES = $(addprefix $(DEPS_DIR)/, $(notdir $(SRC_MODULES:.cpp=.d)))

STATIC_LIB = libwac.a

BRIDGE_TARGETS = zlib libarchive stb jpeg

CXXFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += -I$(BRIDGE_DIR)/include

src_to_obj = $(addprefix $(OBJ_DIR)/, $(notdir $(1:.cpp=.o)))

Example: examples/Example.cpp $(STATIC_LIB)
	$(CXX) $(CXXFLAGS) examples/Example.cpp $(OBJ_MODULES) $(STATIC_LIB) -o Example

static: $(STATIC_LIB)

ifneq ($(MAKECMDGOALS), clean)
-include .bridge.touch
endif

$(STATIC_LIB): .libs.touch $(OBJ_MODULES)
	cp -r $(OBJ_DIR)/*.o .tmp-ar;                    \
	ar -r $@ $(OBJ_MODULES) $(wildcard .tmp-ar/*.o); \
	rm -rf .tmp-ar

.libs.touch:
	mkdir -p .tmp-ar;                     \

	for file in $(BRIDGE_DIR)/lib/*.a; do \
		cp $$file .tmp-ar/lib.a;          \
		cd .tmp-ar && ar -x lib.a;        \
		rm -f lib.a;                      \
		cd ..;                            \
	done

	touch .libs.touch

$(DEPS_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -E -MM -MT $(call src_to_obj, $<) -MT $@ -MF $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.bridge.touch:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(DEPS_DIR)
	mkdir -p $(BRIDGE_DIR)/include
	mkdir -p $(BRIDGE_DIR)/lib
	mkdir -p $(BRIDGE_DIR)/bin
	make -C $(BRIDGE_DIR) -f Makefile $(BRIDGE_TARGETS)
	@echo "-include $(DEPS_MODULES)" > $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEPS_DIR)
	rm -rf $(BRIDGE_DIR)/include
	rm -rf $(BRIDGE_DIR)/lib
	rm -rf $(BRIDGE_DIR)/bin
	rm -f $(STATIC_LIB)
	rm -f Example
	rm -rf Example.dSYM
	rm -f .bridge.touch
	rm -f .libs.touch
	make -C $(dir $(BRIDGE_DIR)/Makefile) -f Makefile clean

clangcomp:
	@echo $(CXXFLAGS) | tr ' ' '\n' | grep -v 'Werror' > .clang_complete

.PHONY: clangcomp clean
