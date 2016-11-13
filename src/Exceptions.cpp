#include <string.h>
#include <stdio.h>

#include "archive.h"

#include "Exceptions.h"


//TODO: add exceptions for JPEG
LibArchiveEx::LibArchiveEx(Archive *a)
{
    SetText(0);
    if (a) SetText(archive_error_string(a));
}


void LibArchiveEx::Print()
{
    fprintf(stderr, "%s\n", GetText());
}


StbEx::StbEx()
{}


void StbEx::Print()
{}


ReadDirEx::ReadDirEx(const char *t)
{
    SetText(0);
    if (t) SetText(t);
}


void ReadDirEx::Print()
{
    fprintf(stderr, "%s\n", GetText());
}


void WrongPathToArchive::Print()
{
    fprintf(stderr, "You have entered the wrong path to the archive\n");
}


void NoPathToArchive::Print()
{
    fprintf(stderr, "You haven't enered any path to the archive \n");
}


void WrongPathToUnpack::Print()
{
    fprintf(stderr, "You have entered the wrong path where to unpack\n");
}


void WrongPathToOriginals::Print()
{
    fprintf(stderr, "You have entered the wrong path to the original photos\n");
}


void NoPathToOriginals::Print()
{
    fprintf(stderr, "You haven't entered any path to the original photos\n");
}


void WrongPathToThumbnails::Print()
{
    fprintf(stderr, "You have entered the wrong thumbnails destination path\n");
}


void NoPathToThumbnails::Print()
{
    fprintf(stderr, "You haven't entered any path where to store the thumbnails\n");
}


CorruptedImage::CorruptedImage(const char *t)
{
    text = 0;
    if (t) text = t;
}


void CorruptedImage::Print()
{
    printf("Corrupted image %s\n", text);
}


void WrongPathToWebPage::Print()
{
    fprintf(stderr, "You have entered the wrong path to web page\n");
}


void NoPathToWebPage::Print()
{
	fprintf(stderr, "You have not specified the path to web page\n");
}
