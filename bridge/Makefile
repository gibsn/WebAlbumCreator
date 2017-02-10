INCLUDE_DIR = include
LIBRARY_DIR = lib
OBJ_DIR = obj
EXTERNALS_BASEDIR = ../externals

LIBARCHIVE_DIR = $(EXTERNALS_BASEDIR)/libarchive-2.8.5
ZLIB_DIR = $(EXTERNALS_BASEDIR)/zlib-1.2.8
JPEG_DIR = $(EXTERNALS_BASEDIR)/jpeg-9b
STB_DIR = $(EXTERNALS_BASEDIR)/stb


libarchive:
	@echo "Compiling libarchive-2.8.5"
	make -C $(LIBARCHIVE_DIR) -f Makefile
	cp $(LIBARCHIVE_DIR)/obj/*.o $(OBJ_DIR)/
	cp $(LIBARCHIVE_DIR)/config.h $(INCLUDE_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive.h $(INCLUDE_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive_entry.h $(INCLUDE_DIR)/

zlib:
	@echo "Compiling zlib-1.2.8"
	make -C $(ZLIB_DIR) -f Makefile
	cp $(ZLIB_DIR)/*.o $(OBJ_DIR)/
	cp $(ZLIB_DIR)/zlib.h $(INCLUDE_DIR)/
	cp $(ZLIB_DIR)/zconf.h $(INCLUDE_DIR)/

jpeg:
	@echo "Compiling jpeg-b"
	make -C $(JPEG_DIR) -f Makefile
	cp $(JPEG_DIR)/*.o $(OBJ_DIR)/
	cp $(JPEG_DIR)/jpeglib.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jconfig.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jmorecfg.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jerror.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jpegint.h $(INCLUDE_DIR)/

stb:
	@echo "Compiling stb"
	cp $(STB_DIR)/stb_image_resize.h $(INCLUDE_DIR)
	cp $(STB_DIR)/stb_image.h $(INCLUDE_DIR)

clean:
	make -C $(LIBARCHIVE_DIR) -f Makefile clean
	make -C $(ZLIB_DIR) -f Makefile clean
	make -C $(JPEG_DIR) -f Makefile clean

.PHONY: libarchive zlib stb jpeg clean

