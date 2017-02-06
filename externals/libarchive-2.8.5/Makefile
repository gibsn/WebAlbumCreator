CFLAGS = -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64

STATIC_LIB = libarchive.a

SRC_DIR = libarchive
OBJ_DIR = obj
DEPS_DIR = deps

CFLAGS += -I$(SRC_DIR) -I. -I../../bridge/include

AR=ar cru

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS = $(addprefix $(DEPS_DIR)/, $(notdir $(SRCS:.c=.d)))

src_to_obj = $(addprefix $(OBJ_DIR)/, $(notdir $(1:.c=.o)))

all: static

ifneq ($(MAKECMDGOALS), clean)
-include .bridge.touch
endif

static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) $@ $(OBJS)

$(DEPS_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -E -MM -MT $(call src_to_obj, $<) -MT $@ -MF $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.bridge.touch:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(DEPS_DIR)
	@echo "-include $(DEPS)" > $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEPS_DIR)
	rm -f $(STATIC_LIB)
	rm -f .bridge.touch

.PHONY: clean all static
