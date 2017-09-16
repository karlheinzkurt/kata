# Requirements
* cmake (Use your package manager or go to: https://cmake.org/)
* gtest (Gets installed automatically)

# Build Instructions
Binaries are put to "bin" folder.
Steps to generate makefiles/solutions/workspaces and build the projects:
```
mkdir build
pushd build
   cmake ../Source
popd
cmake --build build/... --config Debug
```

Run the following command to get a list of generators available 
for your platform. Place matching generator argument when calling 
cmake in line 3 above.
```
cmake -G
```
