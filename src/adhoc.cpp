#include "adhoc.h"

void adhoc_setup(std::string net_interface, std::string group_no, std::string computer_id){
    // Setup an Adhoc network by calling the setup script
    if(WINDOWS){
        std::cerr << "[!] On Windows it is needed to create a network called groep" << group_no << " under \"Network and Sharing Center\".\n";
    }

    std::string exec_directory = getExecPath(false);

    std::string pcall = exec_directory + script_setup + " " + net_interface + " " + group_no + " " + computer_id;
    system(pcall.c_str());
}

void adhoc_desetup(std::string net_interface, std::string group_no){
    // Restore the network settings
    std::string exec_directory = getExecPath(false);

   if(WINDOWS){
        std::string leave_call = exec_directory + script_leave + " " + net_interface;
        std::string restore_call = exec_directory + script_desetup + " " + group_no;
        system(leave_call.c_str());
        system(restore_call.c_str());
    }else{
        std::string restore_call = exec_directory + script_desetup + " " + net_interface;
        system(restore_call.c_str());
    }
}
