#ifndef ADHOC_H
#define ADHOC_H

#include <cstdlib>
#include <string>
#include <iostream>
#include "utils.h"

/*
    Path to the scripts for setting up, joining/leaving the ad-hoc network and restoring the network settings
*/
#if _WINDOWS
// Windows
static const std::string script_setup = "adhoc_join.bat";
static const std::string script_desetup = "adhoc_remove.bat";
static const std::string script_leave = "adhoc_leave.bat";
#else
// Otherwise (assume) Linux
static const std::string script_setup = "adhoc_setup";
static const std::string script_desetup = "adhoc_desetup";
static const std::string script_leave = "";
#endif

// Setup an Adhoc network by calling the setup script
void adhoc_setup(std::string net_interface, std::string group_no, std::string computer_id);
// Restore the network settings
void adhoc_desetup(std::string net_interface, std::string group_no);

#endif // ADHOC_H

