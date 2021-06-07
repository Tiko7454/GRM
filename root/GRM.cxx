#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "config.h"


bool is_link(std::string x){
    return x.find("https://") == 0;  // if it starts with "https://"
}

// grm install ...
int main(int argc, char** argv){
    const std::string GIRHUB_PREFIX = "https://github.com/",
                      CLONE = "git clone ",
                      PULL = "git pull";
    std::string mode = argv[1];

    if(mode == "install"){
        for(int i = 2; i < argc; i++){
            std::string clone = CLONE;  // local mutable string for each argument
            std::string arg = argv[i];  // add default github prefix if necessary
            
            clone += arg + " " + config::RPS_LOCATION;
            // unlinking arg
            if(is_link(arg))
                arg = arg.substr(8);
            // end
            clone += arg;
            if(std::system(clone.c_str()) == 0){
                std::ofstream file("RPL", std::ios_base::app);
                file << arg << std::endl;
                file.close();
            }
        }
    }
    return 0;
}
