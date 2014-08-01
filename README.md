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



Binary
------

Ubuntu: https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight
~~~
sudo add-apt-repository ppa:adrozdoff/marlight
sudo apt-get update
sudo apt-get install marlight-cli
~~~

Optionaly you can install development files:
~~~
sudo apt-get install libmarlight-dev
~~~

Also you can try without guarantees install .deb packages on Debian and other systems
differ Ubuntu Trusty:
- i386:
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/marlight-cli_0.1.0-1_i386.deb
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/libmarlight_0.1.0-1_i386.deb
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/libmarlight-dev_0.1.0-1_i386.deb
- x86_64:
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/marlight-cli_0.1.0-1_amd64.deb
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/libmarlight_0.1.0-1_amd64.deb
  - https://launchpad.net/~adrozdoff/+archive/ubuntu/marlight/+files/libmarlight-dev_0.1.0-1_amd64.deb

TODO:
- Windows MinGW build
- Windows MSVS builds
- Linux static build with static lib in tgz form

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


