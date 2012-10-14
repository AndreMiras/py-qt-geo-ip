/* 
 * File:   MapItemModel.cpp
 * Author: andre
 * 
 * Created on September 30, 2012, 3:15 PM
 */

#include "MapItemModel.h"

MapItemModel::MapItemModel(const QString& name)
{
    setName(name);
    setDescription("");
    setDownloadLink("");
}


MapItemModel::~MapItemModel()
{
}


void MapItemModel::setName(const QString& name)
{
    this->name = name;
}

void MapItemModel::setDescription(const QString& description)
{
    this->description = description;
}

void MapItemModel::setDownloadLink(const QString& downloadLink)
{
    this->downloadLink = downloadLink;
}

void MapItemModel::setImageLink(const QString& imageLink)
{
    this->imageLink = imageLink;
}

QString MapItemModel::getName() const
{
    return name;
}

QString MapItemModel::getDescription() const
{
    return description;
}

QString MapItemModel::getDownloadLink() const
{
    return downloadLink;
}

QString MapItemModel::getImageLink() const
{
    return imageLink;
}