#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include "config.h"


bool is_link(std::string x) {
    return x.find("https://") == 0;  // if it starts with "https://"
}


// grm install ...
int main(int argc, char** argv) {
    const std::string PREFIX = "https://",
                      CLONE = "git clone ",
                      PULL = "git pull",
                      RESTORE = "git restore .",
                      RPL_LOCATION = config::RPS_LOCATION + "RPL";
    std::string mode = argv[1];

    if(mode == config::INSTALL)
        for(int i = 2; i < argc; i++) {
            std::string clone = CLONE,  // local mutable string for each argument
                        arg = argv[i];  // add default github prefix if necessary
            
            clone += arg + " " + config::RPS_LOCATION;
            if(is_link(arg))
                arg = arg.substr(8);
            clone += arg;
            if(std::system(clone.c_str()) == 0) {
                std::ofstream file(RPL_LOCATION, std::ios_base::app);
                file << arg
                     << std::endl;
                file.close();
            }
        }
    else if(mode == config::UPDATE) {
        std::ifstream file(RPL_LOCATION);
        while(file){
            std::string line;
            file >> line;
            if(line == "")
                continue;
            std::cout << "Trying to update "
                      << line
                      << "..." << std::endl;
            std::string arg = config::RPS_LOCATION + line,
                        cd = "cd " + arg + "; ";
            std::system((cd + RESTORE).c_str());
            std::system((cd + PULL).c_str());
        }
    } else if(mode == config::REINSTALL) {
        std::ifstream file(RPL_LOCATION);
        while(file) {
            std::string line;
            file >> line;
            if(line == "")
                continue;
            std::cout << "Reinstalling " 
                      << line 
                      << "..."
                      << std::endl;
            std::string arg = " " + config::RPS_LOCATION + line;
            std::system(("rm -rf" + arg).c_str());
            std::system((CLONE + PREFIX + line + " " + config::RPS_LOCATION + line).c_str());
        }
    } else if(mode == config::REMOVE) {
        for(int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            std::queue <std::string> temp;
            std::ifstream fin(RPL_LOCATION);
            while(fin) {
                std::string line;
                fin >> line;  // make a vector and store it there (or make a temp file)
                if(line == "")
                    continue;
                temp.push(line);
            }
            fin.close();
            std::ofstream fout(RPL_LOCATION);
            while(not temp.empty()) {
                std::string line = temp.front();
                if(line == arg) {
                    std::cout << "Removing "
                              << arg
                              << "..."
                              << std::endl;
                    std::system(("rm -rf " + config::RPS_LOCATION + arg).c_str());
                } else
                    fout << line
                         << std::endl;
                
                temp.pop();
            }
            fout.close();
        }
                
    } else if(mode == config::LIST) {
        std::ifstream file(RPL_LOCATION);
        while(file) {
            std::string line;
            file >> line;
            if(line == "")
                continue;
            std::cout << line << std::endl;
        }
    } else if(mode == config::HELP) {  // not finished
        
    }  // add reinstall one mode
    return 0;
}
