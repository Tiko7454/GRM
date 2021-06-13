#include <iostream>

namespace config {  // configs mustn't contain spaces
    const std::string RPS_LOCATION   =     "/home/tiko7454/temp/GRM/.RPs/",  // change RPS_LOCATION only right after installation
                      INSTALL        =     "install",
                      UPDATE         =     "update",
                      REINSTALL      =     "reinstall",
                      REMOVE         =     "remove",
                      LIST           =     "list",
                      HELP           =     "help";
}
// rebuild the project after changing configs
