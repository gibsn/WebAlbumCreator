#!/bin/bash

make
mkdir -p photos
mkdir -p thumbnails
mkdir -p web_pages
valgrind ./Example foo.zip photos thumbnails web_pages/test.html ../photos/ ../thumbnails/
open web_pages/test.html
