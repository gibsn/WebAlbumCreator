#!/bin/bash

make
mkdir -p photos
mkdir -p thumbnails
mkdir -p web_pages
./Example qwe.zip photos/ thumbnails/ web_pages/"Hello.html"
