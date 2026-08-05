# CRUN
this is simple C/C++ builder

![](crun_logo.jpeg)
_logo_

# How to install?

<!-- ## build.sh
***debian/ubuntu/mint/kali/astra/...***
```shell
./build.sh --linux-debian
```
***Termux (Android)***
```shell
./build.sh --android-termux
``` -->

## CMake
***all system***
```shell
# in source directory
mkdir build && cd build
cmake ..
make
```

## Simpile compiling
```shell
cd CRun
g++ src/crun/*.cpp -o crun
```

# Usage
more information:

```bash
crun [--help|-h]
```

***Template*** ```build.crun```:
```build.crun
COMPILER=clang
OPTION={-g,-o}

# the path start with source dir (where is build.crun)
SRC={myapp.cpp,myapp2.cpp}

EXEC=myapp
LIBS={-lboost}
```

What and how?

```COMPILER``` - your compiler (`g++`, `gcc`, `clang`, `mingw`)

```OPTION``` - flags/options for compiling your project (flag '-o' put automatically)

```SRC``` - Adding the source file with the code (The path start with source dir - where is build.crun)

```EXEC``` - Adding an executable file

```LIBS``` - Connection of libraries

# New
- Update parser
- New parser CLI
- Upadate analyze errors
- New function
- Update work with directories
- write with zero XD

# TODO:
<!-- ***build.sh:***
- [x] debian
- [x] ubuntu
- [x] kali
- [x] astra
- [x] mint
- [ ] arch
- [ ] fedora
- [ ] void
- [x] termux (android) -->

***crun***
- [x] start
- [x] minimum depends
- [x] new parser
- [ ] more function

# Thank you <3
> More information of develope in:
> Telegram: https://tglink.me/BioNos0k