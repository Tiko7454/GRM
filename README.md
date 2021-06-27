# GRM

![License](https://img.shields.io/github/license/Tiko7454/GRM?color=blue)  
Git Repo Manager is a repository manager for Github, Gitlab and all other software hosting providers which use Git.
GRM groups git repositories and provides one command updates for all of them. There is no need to install, update, remove and group them manually. GRM does everything instead of the user.


# Dependencies
* git
* g++


# Usage
Download grm somewhere.


Edit config.hxx:
> Set as `RPS_LOCATION` the location, where you want your installed repos be downloaded.  
> Set as `INSTALL` the command, which you want to use to install packages (mustn't contain spaces)  
> and etc


Compile grm.cxx:
> `g++ grm.cxx -o grm` (GNU/Linux)  
> `g++ grmw.cxx -o grmw.exe` (Windows)

Finally, use the binary file. You can move it anywhere you like and it will continue to work correctly.

