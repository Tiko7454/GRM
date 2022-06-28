# GRM

[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Tiko7454/GRM.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Tiko7454/GRM/context:cpp)
![License](https://img.shields.io/github/license/Tiko7454/GRM?color=blue)  
Git Repo Manager is a repository manager for Github, Gitlab and all other software hosting providers which use Git.
GRM groups git repositories and provides one command updates for all of them. There is no need to install, update, remove and group them manually. GRM does everything instead of the user.


# Dependencies
* git
* g++


# Usage
Download grm somewhere.


Edit config.hxx:
> Set as `GRM_LOCATION` the location, where all grm files are located. (use slashes (/) instead of backslashes (\\))  
> Set as `FILE_MANAGER` the default file manager you use on your OS.  
> Set as `INSTALL` the command, which you want to use to install packages (mustn't contain spaces)  
> and etc


Compile grm.cxx:
> `g++ grm.cxx -o grm`
