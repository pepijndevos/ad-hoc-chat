#include "utils.h"

std::string getExecPath(bool incl_name){
    /* Return the path of the executable
     * Based on: https://stackoverflow.com/questions/143174
     */
    int len = PATH_MAX;
    char pBuf[len];
    int bytes = 0;
#if _WINDOWS
        bytes = GetModuleFileName(NULL, pBuf, len);
        if(bytes == 0)
            bytes = -1;
#elif __APPLE__
    int ret;
    pid_t pid;

    pid = getpid();
    ret = proc_pidpath (pid, pBuf, PATH_MAX);
    pBuf[ret] = '\0';
#else
    bytes = ::readlink("/proc/self/exe", pBuf, len-1);
    if (bytes != -1) {
      pBuf[len] = '\0';
    }
#endif
    if(bytes >= 0){
        std::string ret_str = std::string(pBuf);
        int chop = ret_str.size();
        if (incl_name == false){
            std::size_t pos = ret_str.find_last_of(OS_SPLIT);
            chop = pos + 1;
        }
        return ret_str.substr(0, chop);
    }else{
        return "";
    }
}

std::string do_readlink(std::string const& path) {
    char buff[PATH_MAX];
    ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }

    return "";
}

void setExecName(std::string new_name){
    *exec_name = new_name;
}

void setComputerId(std::string id){
    *computer_id = id;
}
