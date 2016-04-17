Requirements:
- CMake
- gtest (gets installed automatically)

Use your package manager to install or download:
- cmake from: https://cmake.org

Binaries are put to "Cpp/Bin" folder.

Build steps to generate makefiles:
```sh
cd parallel-change/Cpp
mkdir build
cd build
cmake ../Source
make
```

On Windows for VS2012 replace step 4 by:
```sh
cmake -G"Visual Studio 12" ..\Source
```

On mac for XCode replace step 4 by:
```sh
cmake -G"XCode" ../Source
```

For Eclipse 4.4 with CDT4 replace step 4 by:
```sh
cmake -G"Eclipse CDT4 - Unix Makefiles" -D_ECLIPSE_VERSION=4.4 ../Source
```

For CodeLite replace step 4 by:
```sh
cmake -G"CodeLite - Unix Makefiles" ../Source
```

For CodeBlocks replace step 4 by:
```sh
cmake -G"CodeBlocks - Unix Makefiles" ../Source
```

