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
* CppCheck 1.73

#### Libraries

* boost >1.54 (log, filesystem, program_options, system, test...)
* microhttpd
* httpserver (https://github.com/stac47/libhttpserver.git)
* libsqlite3
* rapidjson
* soci
* libscrypt

### Procedure

First thing to do is to install the tools:

#### Boost

    sudo apt-get install libboost-all-dev

#### microhttpd

    sudo apt-get install libmicrohttpd-dev

#### libscrypt

    sudo apt-get install libscrypt-dev

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

#### SOCI

SOCI is used as a tiny layer on top of sqlite3 API. This lib is available in
the major linux distributions and Mac OSX package managers (homebrew, macport).

    sudo apt-get install libsoci-dev

Nevertheless, for debian, SOCI is only available from __Stretch__ version. So
if you work on __Jessie__ or a prior version, you will have to install the lib
by yourself. Hereafter is the procedure we can use for MyRoomies project. For
more information, go to http://soci.sourceforge.net/doc/3.2/installation.html .

    git clone https://github.com/SOCI/soci.git
    mkdir build
    cd build
    cmake -G"Unix Makefiles" -DWITH_BOOST=ON -DSOCI_TESTS=ON \
    -DWITH_SQLITE3=ON -DWITH_FIREBIRD=OFF -DWITH_MYSQL=OFF \
    -DWITH_ODBC=OFF -DWITH_ORACLE=OFF -DWITH_POSTGRESQL=OFF \
    -DWITH_DB2=OFF -DSOCI_HAVE_CXX_C11=ON -DSOCI_CXX_C11=ON \
    -DSOCI_LIBDIR=lib -DCMAKE_INSTALL_PREFIX=$HOME/local <path/to/soci>
    make
    make test
    make install

### Building the application

Scons is used to build the application. By default, running scons alone will
only compile the source. To link into an executable, use the option
__--build-exe__. To use several compilation threads, you can use __-j <N>__
option.

    scons --compile-tests --build-exe -j8

## Tests

Tests comes in two flavours: unit tests and regression tests. Unit tests are
checking the C++ code small pieces by small pieces. They are written in C++ and
we use Boost UTF.

Regression tests aims at testing the whole application. They start a server,
shoot HTTP/JSON queries and check the response. Regression tests are written in
Python 3 and use the standard __unittest__ module.

### Unit tests

To compile the tests and build the binary, set the 2 options
__--compile-tests__ and __--build-exe__, then run the binary:

    ./myroomies-unittest-<toolchain>

### Regression

To run the regression, you have to build the executable of
''myroomies-server'', move to the __myroomies/backend/test/regression__ and run
the follwing command to run the whole regression campaign:

    python3 -m unittest

To run a single test, simply provide the path to your test as follow:

    python3 -m unittest package.module[.class[.method]]
