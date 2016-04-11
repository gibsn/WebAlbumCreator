#!/bin/bash

make
mkdir -p photos
mkdir -p thumbnails
mkdir -p web_pages
./Example photos.tar photos/ thumbnails/ web_pages/"Hello.html"
open web_pages/Hello.html
