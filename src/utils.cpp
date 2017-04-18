#include "utils.h"

utils::utils(){}

utils::~utils(){}

template<typename Out>
void utils::split(const std::string &s, char delim, Out result) {
    /* String is split and added to result */
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> utils::split(const std::string &s, char delim) {
    /* Split string into vector */
    std::vector<std::string> elems;
    utils u;
    u.split(s, delim, std::back_inserter(elems));
    return elems;
}

Filetypes utils::getFiletype(QString filename){
    /* Get the filetype based on the filename extension */
    if(filename.endsWith(".png", Qt::CaseInsensitive)){
        // PNG
        return Filetypes::PNG;
    } else if(filename.endsWith(".jpg", Qt::CaseInsensitive) || filename.endsWith(".jpeg", Qt::CaseInsensitive)) {
        // JPG
        return Filetypes::JPG;
    } else if(filename.endsWith(".mpg", Qt::CaseInsensitive) || filename.endsWith(".mpeg", Qt::CaseInsensitive)) {
        // MPEG
        return Filetypes::MPG;
    } else if(filename.endsWith(".avi", Qt::CaseInsensitive)) {
        // AVI
        return Filetypes::AVI;
    } else if(filename.endsWith(".mp4", Qt::CaseInsensitive)) {
        // MP4
        return Filetypes::MP4;
    } else if(filename.endsWith(".mov", Qt::CaseInsensitive)) {
        // MOV
        return Filetypes::MOV;
    } else if(filename.endsWith(".gif", Qt::CaseInsensitive)) {
        // GIF
        return Filetypes::GIF;
    } else{
        // Default to Generic
        return Filetypes::GENERIC;
    }
}
