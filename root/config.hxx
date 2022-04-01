#include <iostream>
// #define WINDOWS
// uncomment the line above if you are on windows

namespace config {  // configs mustn't contain spaces
    const std::string GRM_LOCATION   =     "/home/tiko7454/Projects/GRM/",  // change GRM_LOCATION only right after installation (it must end with /)
                      FILE_MANAGER   =     "lf",
                      INSTALL        =     "install",
                      UPDATE         =     "update",
                      REINSTALL      =     "reinstall",
                      REMOVE         =     "remove",
                      LIST           =     "list",
                      HELP           =     "help",
                      OPEN           =     "open";
}
// rebuild the project after changing configs
