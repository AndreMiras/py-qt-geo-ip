#!/bin/bash
# This delivery script should be ran to compile and copy files to be delivered

delivery_dir="delivery"
delivery_sub_dir="$delivery_dir/delivery-`date +%Y-%m-%d`"
ui_files="*.ui"
header_files="*.h"
source_files="*.cpp"
docs_dir="docs/"
nbproject_dir="nbproject/"
nbproject_files="configurations.xml project.xml
    qt-Debug.pro qt-Release.pro
    Makefile-Debug.mk Makefile-Release.mk
    Package-Debug.bash Package-Release.bash
    Makefile-variables.mk Makefile-impl.mk Makefile"
delivery_files="$ui_files $header_files $source_files"

# cleans and makes
make clean

if [ ! -d $delivery_sub_dir ]
then
    mkdir -p $delivery_sub_dir
fi

if [ ! -d "$delivery_sub_dir/$nbproject_dir" ]
then
    mkdir -p "$delivery_sub_dir/$nbproject_dir"
fi

# copies relevant files
cp -r $docs_dir $delivery_sub_dir
cp $delivery_files $delivery_sub_dir
for nbproject_file in $nbproject_files
do
    cp $nbproject_dir/$nbproject_file $delivery_sub_dir/$nbproject_dir
done

# makes a tar archive
tar -cvzf $delivery_sub_dir.tar.gz $delivery_sub_dir
