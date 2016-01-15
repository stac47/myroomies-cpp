# My Roomies (C++ version)
Living together, living better

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

* boost >1.54 (log, filesystem, program_options, system)
* microhttpd
* httpserver (https://github.com/stac47/libhttpserver.git)
* libsqlite3
* rapidjson
* google-test (for unit testing)

### Procedure

First thing to do is to install the tools:

#### Boost

    sudo apt-get install libboost-all-dev

#### microhttpd

    sudo apt-get install libmicrohttpd-dev

#### google-test

    sudo apt-get install libgtest-dev
    cd /usr/src/gtest
    sudo cmake .
    sudo make
    sudo mv libg* /usr/lib/

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
    cd ~/local
    ln -s $HOME/rapidjson/include/rapidjson rapidjson

#### spdlog

    git clone https://github.com/gabime/spdlog.git
    cd ~/local
    ln -s $HOME/spdlog/include/spdlog spdlog
