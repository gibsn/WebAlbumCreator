#include <string.h>
#include <stdio.h>

#include "archive.h"

#include "Exceptions.h"


//TODO: add exceptions for JPEG
LibArchiveEx::LibArchiveEx(archive *a)
{
    if (a) SetText(archive_error_string(a));
}

ReadDirEx::ReadDirEx(const char *t)
{
    if (t) SetText(t);
}

const char *WrongPathToArchive::GetErrMsg() const
{
    return "You have entered the wrong path to the archive";
}


const char *NoPathToArchive::GetErrMsg() const
{
    return "You haven't enered any path to the archive";
}


const char *WrongPathToUnpack::GetErrMsg() const
{
    return "You have entered the wrong path where to unpack";
}


const char *WrongPathToOriginals::GetErrMsg() const
{
    return "You have entered the wrong path to the original photos";
}


const char *NoPathToOriginals::GetErrMsg() const
{
    return "You haven't entered any path to the original photos";
}


const char *WrongPathToThumbnails::GetErrMsg() const
{
    return "You have entered the wrong thumbnails destination path";
}


const char *NoPathToThumbnails::GetErrMsg() const
{
    return "You haven't entered any path where to store the thumbnails";
}


#define MSG "Corrupted image "
CorruptedImage::CorruptedImage(const char *t)
    : text(NULL)
{
    text = (char *)malloc(sizeof MSG + strlen(t));
    sprintf(text, MSG "%s", t);
}
#undef MSG


const char *WrongPathToWebPage::GetErrMsg() const
{
    return "You have entered the wrong path to web page";
}


const char *NoPathToWebPage::GetErrMsg() const
{
	return "You have not specified the path to web page";
}
