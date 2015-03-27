# Introduction #

This is the compilation instructions draft for Windows.


# Requirements #

You will need the following:
  * CMake http://www.cmake.org/cmake/resources/software.html
  * Qt Windows qt-win-opensource-4.8.1-mingw.exe
  * TODO add stuffs


# Compile Marble #

Compile for MinGW by following Windows compiling wiki:
http://techbase.kde.org/Projects/Marble/WindowsCompiling

```bash

cmake -G"MSYS Makefiles" -DQTONLY=ON -DCMAKE_BUILD_TYPE=Release ../marble-1.2.0-source/ -DCMAKE_INSTALL_PREFIX=/mingw/local/marble -DMARBLE_DATA_PATH=/mingw/local/marble/data -Wno-dev
make
make install
```

Symlink to the defaults MinGW include and library paths:
http://www.mingw.org/wiki/IncludePathHOWTO
```bash

ln -sfn /mingw/local/marble/include/marble /mingw/include/
ln -sfn /mingw/local/marble/libmarblewidget.dll /mingw/lib/
```

# GeoIP #

## Install zlib ##
zlib is a dependancy of GeoIP
http://zlib.net/
http://wiki.openttd.org/Compiling_on_MinGW#Compiling_zlib

```bash

wget http://zlib.net/zlib-1.2.7.tar.gz
tar xvfz zlib-1.2.7.tar.gz
cd zlib-1.2.7
make -f win32/Makefile.gcc BINARY_PATH=/mingw/bin INCLUDE_PATH=/mingw/include LIBRARY_PATH=/mingw/lib install
```

## Compile GeoIP ##

http://splunk-base.splunk.com/answers/55680/how-can-i-use-the-c-api-of-maxmind-geolite

```bash

./configure --prefix=/mingw
make
make install
```

If you get the following error during the make:
```bash

mv -f .deps/GeoIP.Tpo .deps/GeoIP.Plo
mv: cannot stat `.deps/GeoIP.Tpo': No such file or directory
make[1]: *** [GeoIP.lo] Error 1
make[1]: Leaving directory `/c/Users/Andre/Downloads/GeoIP-1.4.8/libGeoIP'
make: *** [all-recursive] Error 1
```

Run libtoolize and re-run from configure step:
```bash

libtoolize -f
./configure
make
make install
```

If you get the following error:
```bash

In file included from GeoIP.c:21:0:
GeoIP.h:36:21: fatal error: wspiapi.h: No such file or directory
compilation terminated.
make[1]: *** [GeoIP.lo] Error 1
make[1]: Leaving directory `/c/Users/Andre/Downloads/GeoIP-1.4.8/libGeoIP'
make: *** [all-recursive] Error 1
```

You need to patch GeoIP with geoip\_wspiapi.patch (in the download section):
```bash

patch -p0 -i ../geoip_wspiapi.patch
```

If you get the following errors:
```bash

...
undefined reference to `getaddrinfo@16'
...
```
Take a look at this post http://programmingrants.blogspot.fr/2009/09/tips-on-undefined-reference-to.html

# Compile QuaZip #
```bash

qmake
make
INSTALL_ROOT=/mingw make install
```

# Qt Static #
If you want to statically link the project, Qt will have to be built statically so you can refer to .lib
```bash

configure -static -platform win32-g++ -qt-libjpeg -no-phonon -no-phonon-backend -fast -release -opensource -confirm-license -no-qt3support -no-sql-sqlite -no-openvg -no-script -no-scripttools -nomake examples -nomake demos
mingw32-make
```