#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

    #define _WINDOWS true
    #define OS_SPLIT "\"
    #include <Windows.h>
    static const bool WINDOWS = true;
#else // It is a *nix system
    #define _WINDOWS false
    #define OS_SPLIT "/"
    static const bool WINDOWS = false;

#if __APPLE__
    #include <libproc.h>
#endif

#endif // If Windows

static std::string *exec_name = new std::string("chat");
static std::string *computer_id = new std::string("1");

std::string do_readlink(std::string const& path); // Implement readlink
std::string getExecPath(bool incl_name);     // Path of the executable

void setExecName(std::string new_name);      // Set exec_name
void setComputerId(std::string id);          // Set computer_id
#endif // UTILS_H

