#!/bin/bash

make
mkdir -p photos
mkdir -p thumbnails
mkdir -p web_pages
./Example photos.tar.gz photos thumbnails web_pages/test.html
open web_pages/test.html
