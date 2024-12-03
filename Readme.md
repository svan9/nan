# NAN LANGUAGE
![C++](https://img.shields.io/badge/cpp-blue)
![CMake](https://img.shields.io/badge/cmake-blue)
![GitHub last commit](https://img.shields.io/github/last-commit/svan9/nan)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/svan9/nan)
![GitHub License](https://img.shields.io/github/license/svan9/nan)
![GitHub Repo stars](https://img.shields.io/github/stars/svan9/nan)

___Nan Language___ compiler for ___Nan Virtual Machine___. Also includes own ___Nan Virtual Machine___. Uses _cmake_ for build. Binary ___nan___ ([./src](./src)) - test (in the future, a complete compiler for ___Nan Language___). Binary ___nanvm___ ([./vm](./vm)) - Nan Virtual Machine executable for `*.nb` file ak binary nvm files.


### Usage
```shell
./nan
```
```shell
./nanvm "path/to/file"
```

* Virtual Machine provides in [virtual.hpp](/include/virtual.hpp). 
* Virtual Machine Lib provides in [virtuallib.hpp](/include/virtuallib.hpp) 

> VM uses _virtual_ namespace. VM Lib uses _virtual::lib_ namespace


# References 
- [Virtual.hpp](./docs/virtual.md)
- [mewlib.h](./docs/mewlib.md)
