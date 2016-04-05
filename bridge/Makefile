INCLUDE_DIR = include
LIBRARY_DIR = lib
EXTERNALS_BASEDIR = externals

LIBARCHIVE_DIR = ../$(EXTERNALS_BASEDIR)/libarchive-2.8.5
LIBARCHIVE_STATIC = libarchive.a
WITHOUT_FLAGS = --without-bz2lib --without-lzmadec --without-expat
WITHOUT_FLAGS += --without-lzma --without-openssl --without-xml2

ZLIB_DIR = ../$(EXTERNALS_BASEDIR)/zlib-1.2.8
ZLIB_STATIC = libz.a

STB_DIR = ../$(EXTERNALS_BASEDIR)/stb


libarchive:
	echo "Compiling libarchive-2.8.5"
	cd $(LIBARCHIVE_DIR) && ./configure $(WITHOUT_FLAGS)
	make -C $(LIBARCHIVE_DIR) -f Makefile
	cp $(LIBARCHIVE_DIR)/.libs/$(LIBARCHIVE_STATIC) $(LIBRARY_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive.h $(INCLUDE_DIR)/
	cp $(LIBARCHIVE_DIR)/libarchive/archive_entry.h $(INCLUDE_DIR)/

zlib:
	echo "Compiling zlib-1.2.8"
	cd $(ZLIB_DIR) && ./configure
	make -C $(ZLIB_DIR) -f Makefile
	cp $(ZLIB_DIR)/$(ZLIB_STATIC) $(LIBRARY_DIR)/
	cp $(ZLIB_DIR)/zlib.h $(INCLUDE_DIR)/

stb:
	echo "Compiling stb"
	cp $(STB_DIR)/stb_image_resize.h $(INCLUDE_DIR)
	cp $(STB_DIR)/stb_image.h $(INCLUDE_DIR)
	cp $(STB_DIR)/stb_image_write.h $(INCLUDE_DIR)

.PHONY: libarchive zlib stb

clean:
	make -C $(LIBARCHIVE_DIR) -f Makefile distclean
	make -C $(ZLIB_DIR) -f Makefile distclean

.PHONY: clean
