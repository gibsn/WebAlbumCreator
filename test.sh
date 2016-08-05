#!/bin/bash

make
mkdir -p photos
mkdir -p thumbnails
mkdir -p web_pages
valgrind ./Example photos.tar photos thumbnails web_pages/test.html ../photos/ ../thumbnails/
open web_pages/test.html
