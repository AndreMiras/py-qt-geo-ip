# Introduction #

This installation note guides you through QtGeoIp installation.


# Install deps #
You need to install Qt library as well as Marble library to be able to build the code.
Here is how to do it on both Ubuntu and Gentoo.

## Ubuntu ##
```bash

sudo apt-get install libqt4-dev libmarble-dev
```

## Gentoo ##
```bash

emerge -av x11-libs/qt-core x11-libs/qt-gui kde-base/marble
```


# Compile #
```bash

make QMAKE=/usr/bin/qmake CONF=Release
```


# Update GeoIp databases #
You need to download GeoIp updates, this might take a while.
Using the script (on Gentoo):
```bash

sudo geoipupdate.sh
```
Or downloading and copying at least GeoLiteCity manually:
```bash

wget geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
sudo gunzip -fdc GeoLiteCity.dat.gz > /usr/share/GeoIP/GeoLiteCity.dat
```

# Run #
```bash

dist/Release/GNU-Linux-x86/QtGeoIp
```