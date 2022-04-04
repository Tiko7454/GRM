#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include "config.hxx"


#ifdef WINDOWS
#include <algorithm>


std::string _path_to_win(std::string x) {
    std::replace(x.begin(), x.end(), '/', '\\');
    return x;
}


#endif

namespace consts {
    const std::string PREFIX = "https://",
        CLONE = "git clone ",
        PULL  = "git pull",
        RESTORE = "git restore .",
        RPS_LOCATION = config::GRM_LOCATION + ".RPs/",
        RPL_LOCATION = config::GRM_LOCATION + ".RPL";
}


bool _is_link(std::string x) {
    return x.find(consts::PREFIX) == 0;  /* if it starts with "https://" */
}


bool _check_safety(std::string arg) {
    std::string unsafe_symbols{"<>#%\" {}|^[]`;?:@&=+$,"};
    for (char symbol : unsafe_symbols)
        if (arg.find(symbol) != std::string::npos)
            return false;
    return true;
}


void _rm(std::string arg) {
    if (not _check_safety(arg))
        return;
    #ifdef WINDOWS
    std::replace(arg.begin(), arg.end(), '/', '\\');
    std::system(("del /Q /F /S " + arg).c_str());
    std::system(("rmdir /S /Q " + arg).c_str());
    #else
    std::system(("rm -rf " + arg).c_str());
    #endif
}


/* modes */
void install(int argc, char** argv) {
    for (int i = 2; i < argc; i++) {
        std::string clone = consts::CLONE;
        std::string arg = argv[i];
        /* TODO local mutable string for each argument */
        /* TODO add default github prefix if necessary */

        if (_is_link(arg))
            arg = arg.substr(8);
        clone += consts::PREFIX + arg + " " + consts::RPS_LOCATION + arg;
        if (not (_check_safety(arg) and _check_safety(consts::RPS_LOCATION)))
            continue;
        if (std::system(clone.c_str()) == 0) {
            std::ofstream file(consts::RPL_LOCATION, std::ios_base::app);
            file << arg
                 << std::endl;
        }
    }
}


void remove(int argc, char** argv) {
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        std::queue<std::string> temp;
        {
            std::ifstream fin(consts::RPL_LOCATION);
            while (fin) {
                std::string line;
                fin >> line;
                if (line == "")
                    continue;
                temp.push(line);
            }
        }
        std::ofstream fout(consts::RPL_LOCATION);
        while (not temp.empty()) {
            std::string line = temp.front();
            if (line == arg) {
                std::cout << "Removing "
                          << arg
                          << "..."
                          << std::endl;
                _rm(consts::RPS_LOCATION + arg);
            } else {
                fout << line
                     << std::endl;
            }
            temp.pop();
        }
    }
}


void reinstall(int argc, char** argv) {
    remove(argc, argv);
    install(argc, argv);
}


void update() {
    std::ifstream file(consts::RPL_LOCATION);
    while (file) {
        std::string line;
        file >> line;
        if (line == "")
            continue;
        std::cout << "Trying to update "
                  << line
                  << "..."
                  << std::endl;
        std::string arg = consts::RPS_LOCATION + line;
        if (not _check_safety(arg))
            return;
        std::string cd = "cd " + arg;
        #ifdef WINDOWS
        arg = _path_to_win(arg);
        #endif
        cd += "&& ";

        std::cout << "Repairing local repository version..."
                  << std::endl;
        std::system((cd + consts::RESTORE).c_str());
        std::cout << "Updating from remote repository..."
                  << std::endl;
        std::system((cd + consts::PULL).c_str());
    }
}


void list() {
    std::ifstream file(consts::RPL_LOCATION);
    while (file) {
        std::string line;
        file >> line;
        if (line == "")
            continue;
        std::cout << line
                  << std::endl;
    }
}


void open() {
    std::string path = consts::RPS_LOCATION;
    #ifdef WINDOWS
    path = _path_to_win(path);
    #endif
    if (_check_safety(path))
        std::system((config::FILE_MANAGER + " " + path).c_str());
}


void help() {
    std::cout << "grm <mode> <repo> ...\n\n"
              << "modes:\n"
              << config::INSTALL << " <repo>: install <repo>\n"
              << config::UPDATE << ": update all repos\n"
              << config::REINSTALL << ": reinstalling all repos\n"
              << config::REMOVE << " <repo>: removes <repo>\n"
              << config::LIST << ": shows installed repo list\n"
              << config::OPEN
              << ": opens the directory where the repos are downloaded\n"
              << config::HELP << ": shows this\n";
}


void command_not_found(std::string mode) {
    std::cout << "command " << mode << " does not exist" << std::endl
              << "try `grm help` for more instructions";
}


int main(int argc, char** argv) {
    std::string mode;
    if (argc == 1)
        mode = "";
    else
        mode = argv[1];

    if (mode == config::INSTALL)
        install(argc, argv);
    else if (mode == config::REMOVE)
        remove(argc, argv);
    else if (mode == config::REINSTALL)
        reinstall(argc, argv);
    else if (mode == config::UPDATE)
        update();
    else if (mode == config::LIST)
        list();
    else if (mode == config::OPEN)
        open();
    else if (mode == config::HELP)
        help();
    else
        command_not_found(mode);
    return 0;
}
