# Requirements
* cmake (Use your package manager or go to: https://cmake.org/)
* gtest (Gets installed automatically)

# Build Instructions
Binaries are put to "bin" folder.
Build steps to generate plain makefiles and build the projects:
```
mkdir build
pushd build
   cmake ../Source
popd
cmake --build build --config Debug
```

Run the following command to get a list of generators available for your platform.
```
cmake -G
```

E.g. for CodeLite replace step 4 by:
```sh
cmake -G"CodeLite - Unix Makefiles" ../Source
```

On Windows for VS2012 replace step 4 by:
```sh
cmake -G"Visual Studio 11 2012" ..\Source
```

For Eclipse 4.4 with CDT4 replace step 4 by:
```sh
cmake -G"Eclipse CDT4 - Unix Makefiles" -D_ECLIPSE_VERSION=4.4 ../Source
```
