# Development

## Compilation
MyRoomies relies on several libraries. Some are very common, hence they are
often part of your linux distribution or easily installable from your package
manager like Homebrew on MacOSX. Some other are more experimental libraries,
and as so, they have to be manually compiled/installed on your system before
starting working on this project.

### Dependencies
#### Tools

* OS: Unix based systems (no Windows support)
* compiler: gcc 4.6/clang 3.5
* build: Scons 2.4
* Python 3.4

#### Libraries

* boost >1.54 (log, filesystem, program_options, system, test...)
* microhttpd
* httpserver (https://github.com/stac47/libhttpserver.git)
* libsqlite3
* rapidjson

### Procedure

First thing to do is to install the tools:

#### Boost

    sudo apt-get install libboost-all-dev

#### microhttpd

    sudo apt-get install libmicrohttpd-dev

#### httpserver

Note that if gcc installed on your system, there is a change in the libc++ ABI.
Make sure you compile the library and myroomies with the same g++ version. For
sure, compiling the libhttpserver with clang++ and myroomies with g++ will
cause a linkage error.

    cd ~
    mkdir local
    git clone https://github.com/stac47/libhttpserver.git
    ./bootstrap
     mkdir build
     cd build
     ../configure --prefix=$HOME/local CXX=/usr/bin/g++
     make
     make install
     make doxygen-doc # if you want to build the code reference

#### rapidjson

    git clone https://github.com/miloyip/rapidjson.git
    cd ~/local/include
    ln -s $HOME/rapidjson/include/rapidjson rapidjson

#### spdlog

    git clone https://github.com/gabime/spdlog.git
    cd ~/local/include
    ln -s $HOME/spdlog/include/spdlog spdlog

## Tests

Tests comes in two flavours: unit tests and regression tests. Unit tests are
checking the C++ code small pieces by small pieces. They are written in C++ and
we use Boost UTF.

Regression tests aims at testing the whole application. They start a server,
shoot HTTP/JSON queries and check the response. Regression tests are written in
Python 3 and use the standard __unittest__ module.

### Unit tests

When you build the application, the unit tests are also build in a dedicated
binary. Simply run this binary to start the unit test suite.

    ./myroomies-unittest

### Regression

To run the regression, move to the __myroomies/backend/test/regression__ and
run the follwing command to run the whole regression campaign:

    python3 -m unittest

To run a single test, simply provide the path to your test as follow:

    python3 -m unittest package.module[.class[.method]]
