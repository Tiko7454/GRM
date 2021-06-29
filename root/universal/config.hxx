#include <iostream>
// #define WINDOWS
// uncomment the line above if you are on windows

namespace config {  // configs mustn't contain spaces
    const std::string RPS_LOCATION   =     "/home/tiko7454/temp/test/GRM/.RPs/",  // change RPS_LOCATION only right after installation (it must end with /)
                      INSTALL        =     "install",
                      UPDATE         =     "update",
                      REINSTALL      =     "reinstall",
                      REMOVE         =     "remove",
                      LIST           =     "list",
                      HELP           =     "help";
}
// rebuild the project after changing configs