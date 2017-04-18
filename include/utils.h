#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <string>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

enum Filetypes {
    PNG,
    JPG,
    MPG,
    AVI,
    MP4,
    MOV,
    GIF,
    GENERIC     // Files not displayed in the UI
};

class utils
{
public:
    utils();
    ~utils();

    template<typename Out>
    void split(const std::string &s, char delim, Out result);

    std::vector<std::string> static split(const std::string &s, char delim);
    Filetypes static getFiletype(QString filename);
};

#endif // UTILS_H
