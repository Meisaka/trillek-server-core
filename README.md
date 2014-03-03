Trillek-server
====

Dependancies
----

[rapidjson](https://code.google.com/p/rapidjson/)

Configuring
----

Trillek server requires CMake (version 2.8 or higher) and a C++11 compatible tool chain.

Run cmake in a new `build` directory:

```
mkdir build
cd build
cmake ..
```

Building
----

#### Linux:

 * run `make` to compile.
 * gcc 4.8.1 is known to work

#### Windows / MSVC:

 * Open the generated solution file
 * set `trillek-server` to be the StartUp project
 * build the solution
 * Visual Studio 2012 and higher are known to work.

