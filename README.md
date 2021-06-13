# GRM
Git Repo Manager

This is a repository manager for Github, Gitlab and all other software hosting providers which use Git.
GRM groupes git repositories and provides one command updates for all of them. There is no need to install them, update them, remove them, group them manually. GRM does everything instrad of the user.

# Dependencies
* git
* g++

# Usage
Download grm somewhere.

Edit config.hxx:
Set as RPS_LOCATION the location, where you want your installed repos be downloaded
Set as INSTALL the command, which you want to use to install packages (mustn't contain spaces)
and etc.

Compile GRM.cxx:
(g++ GRM.cxx -o grm) (GNU/Linux)
(g++ GRM.cxx -o grm.exe) (Windows)

Finally you can use the binery file, moving it anywhere you like and it will work correctly
