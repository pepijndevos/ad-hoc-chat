/*
 * Security.cpp
 *
 */

#include "Security.h"

Security::Security() {
}

Security::~Security() {
}

void Security::encrypt(){
    // TODO
}

void Security::decrypt(){
    // TODO
}

std::string Security::getMD5sum(std::string str){
    /* Get the MD5 sum of a string */
    MD5 md5;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    std::string ret_str = md5.digestString(cstr);
    delete[] cstr;
    return ret_str;
}

std::string Security::getFileMD5(std::string path){
    /* Get the MD5 sum of a file */
    MD5 md5;
    char *cstr = new char[path.length() + 1];
    strcpy(cstr, path.c_str());

    std::string ret_str = md5.digestFile(cstr);
    delete[] cstr;
    return ret_str;
}
