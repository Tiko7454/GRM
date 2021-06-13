#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include "config.hxx"


namespace consts {
    const std::string PREFIX = "https://",
                      CLONE = "git clone ",
                      PULL = "git pull",
                      RESTORE = "git restore .",
                      RPL_LOCATION = config::RPS_LOCATION + "RPL";
}


bool is_link(std::string x) {
    return x.find(consts::PREFIX) == 0;  // if it starts with "https://"
}


void install(int argc, char** argv) {
    for(int i = 2; i < argc; i++) {
        std::string clone = consts::CLONE,  // local mutable string for each argument
                    arg = argv[i];  // add default github prefix if necessary    
        clone += arg + " " + config::RPS_LOCATION;
        if(is_link(arg))
            arg = arg.substr(8);
        clone += arg;
        if(std::system(clone.c_str()) == 0) {
            std::ofstream file(consts::RPL_LOCATION, std::ios_base::app);
            file << arg
                 << std::endl;
            file.close();
        }
    }
}


void update() {
    std::ifstream file(consts::RPL_LOCATION);
    while(file) {
        std::string line;
        file >> line;
        if(line == "")
            continue;
        std::cout << "Trying to update "
                  << line
                  << "..." 
                  << std::endl;
        std::string arg = config::RPS_LOCATION + line,
                    cd = "cd " + arg + "; ";
        std::cout << "Repairing local repository version..."
                  << std::endl;
        std::system((cd + consts::RESTORE).c_str());
        std::cout << "Updating from remote repository..."
                  << std::endl;
        std::system((cd + consts::PULL).c_str());
    }
    file.close();
}


void reinstall() {
    std::ifstream file(consts::RPL_LOCATION);
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
        std::system((
            consts::CLONE + consts::PREFIX + line + " " + config::RPS_LOCATION + line
        ).c_str());
    }
    file.close();
}


void remove(int argc, char** argv) {
    for(int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        std::queue <std::string> temp;
        std::ifstream fin(consts::RPL_LOCATION);
        while(fin) {
            std::string line;
            fin >> line;  // make a vector and store it there (or make a temp file)
            if(line == "")
                continue;
            temp.push(line);
        }
        fin.close();
        std::ofstream fout(consts::RPL_LOCATION);
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
}


void list() {
    std::ifstream file(consts::RPL_LOCATION);
    while(file) {
        std::string line;
        file >> line;
        if(line == "")
            continue;
        std::cout << line
                  << std::endl;
    }
    file.close();
}


void help() {
    std::cout << "grm <mode> <repo> ...\n\n"
              << "modes:\n"
              << config::INSTALL << " <repo>: install <repo>\n"
              << config::UPDATE << ": update all repos\n"
              << config::REINSTALL << ": reinstalling all repos\n"
              << config::REMOVE << " <repo>: removes <repo>\n"
              << config::LIST << ": shows installed repo list"
              << config::HELP << ": shows this\n";
}


int main(int argc, char** argv) {
    std::string mode;
    if(argc == 1)
        mode = config::HELP;
    else
        mode = argv[1];

    if(mode == config::INSTALL)
        install(argc, argv);
    else if(mode == config::UPDATE)
        update();
    else if(mode == config::REINSTALL)
        reinstall();
    else if(mode == config::REMOVE)
        remove(argc, argv);
    else if(mode == config::LIST)
        list();
    else if(mode == config::HELP)
        help();
    // add reinstall one mode
    return 0;
}
