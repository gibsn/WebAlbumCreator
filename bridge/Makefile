INCLUDE_DIR = include
LIBRARY_DIR = lib
EXTERNALS_BASEDIR = externals

LIBARCHIVE_DIR = ../$(EXTERNALS_BASEDIR)/libarchive-2.8.5
LIBARCHIVE_STATIC = libarchive.a

ZLIB_DIR = ../$(EXTERNALS_BASEDIR)/zlib-1.2.8
ZLIB_STATIC = libz.a

JPEG_DIR = ../$(EXTERNALS_BASEDIR)/jpeg-9b
JPEG_STATIC = libjpeg.a

STB_DIR = ../$(EXTERNALS_BASEDIR)/stb


libarchive:
	@echo "Compiling libarchive-2.8.5"
	make -C $(LIBARCHIVE_DIR) -f Makefile
	cp $(LIBARCHIVE_DIR)/$(LIBARCHIVE_STATIC) $(LIBRARY_DIR)/
	cp $(LIBARCHIVE_DIR)/config.h $(INCLUDE_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive.h $(INCLUDE_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive_entry.h $(INCLUDE_DIR)/

zlib:
	@echo "Compiling zlib-1.2.8"
	cd $(ZLIB_DIR) && ./configure
	make -C $(ZLIB_DIR) -f Makefile
	cp $(ZLIB_DIR)/$(ZLIB_STATIC) $(LIBRARY_DIR)/
	cp $(ZLIB_DIR)/zlib.h $(INCLUDE_DIR)/

jpeg:
	@echo "Compiling jpeg-b"
	cd $(JPEG_DIR) && ./configure
	make -C $(JPEG_DIR) -f makefile.ansi
	cp $(JPEG_DIR)/$(JPEG_STATIC) $(LIBRARY_DIR)/libjpeg9.a
	cp $(JPEG_DIR)/jpeglib.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jconfig.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jmorecfg.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jerror.h $(INCLUDE_DIR)/
	cp $(JPEG_DIR)/jpegint.h $(INCLUDE_DIR)/

stb:
	@echo "Compiling stb"
	cp $(STB_DIR)/stb_image_resize.h $(INCLUDE_DIR)
	cp $(STB_DIR)/stb_image.h $(INCLUDE_DIR)

.PHONY: libarchive zlib stb jpeg

clean:
	make -C $(LIBARCHIVE_DIR) -f Makefile clean
	make -C $(ZLIB_DIR) -f Makefile distclean
	make -C $(JPEG_DIR) -f makefile.ansi clean

.PHONY: clean
