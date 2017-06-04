#include <stdio.h>

#include "archive.h"

#include "Exceptions.h"


using namespace Wac;

//TODO: add exceptions for JPEG
LibArchiveEx::LibArchiveEx(archive *a)
{
    if (a && archive_error_string(a)) {
        SetErrMsg(archive_error_string(a));
    } else {
        SetErrMsg("unknown LibArchive error");
    }
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
{
    int len = sizeof MSG + strlen(t);
    char *_err_msg = (char *)malloc(len);

    snprintf(_err_msg, len, MSG "%s", t);

    SetErrMsg(_err_msg);
    free(_err_msg);
}
#undef MSG


const char *NoPathToWebPage::GetErrMsg() const
{
	return "You have not specified the path to web page";
}
