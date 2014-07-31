marlight-cli
============

Library and console tool to control Marlight lamps via WiFi Router

Build
-----

Build depends:
- Common:  cmake >= 2.8
- Library: gcc >= 4.0.0
- Tool:    g++ >= 4.7.3 (C++11 required)

Build library and application:
- Create build directory under source root: mkdir build
- Change current directory to build: cd build
- Run cmake: cmake ..
- Run make: make

Build only library:
- Create build_lib directory under source root
- Change current directory to build_lib: cd build_lib
- Run cmake: cmake ../lib
- Run make: make

Currently installation rules does not provided. Copy it manually:
~~~
cp build/lib/libmarlight.so /usr/local/lib/
mkdir -p /usr/local/include/marlight
cp lib/*.h /usr/local/include/marlight/
cp build/marlight-cli /usr/local/bin/
~~~


Run
---

Simple run 'marlight-cli' without parameters or with '--help'

By default all commands work with Channel 1. To select channel for configuration run
~~~
marlight-cli --host HOST channel_on #
~~~

where # - is a channel number between 1..4

To deselect channel from configuration run:
~~~
marlight-cli --host HOST channel_off #
~~~
