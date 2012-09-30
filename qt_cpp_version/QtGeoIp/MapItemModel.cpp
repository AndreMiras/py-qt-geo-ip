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
}

MapItemModel::MapItemModel(const MapItemModel& orig)
{
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

QString MapItemModel::getName()
{
    return name;
}

QString MapItemModel::getDescription()
{
    return description;
}

QString MapItemModel::getDownloadLink()
{
    return downloadLink;
}