/*
 * File:   InstallMapItemWidget.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 */

#include "InstallMapItemWidget.h"

InstallMapItemWidget::InstallMapItemWidget(MapItemModel* mapItemModel)
{
    widget.setupUi(this);
    setMapItemModel(mapItemModel);
}

InstallMapItemWidget::~InstallMapItemWidget()
{
}

void InstallMapItemWidget::updateWidget()
{
    if (mapItemModel != NULL)
    {
        widget.mapTitleLabel->setText(mapItemModel->getName());
        widget.mapDescriptionLabel->setText(mapItemModel->getDescription());
    }
}

MapItemModel* InstallMapItemWidget::getMapItemModel()
{
    return mapItemModel;
}

void InstallMapItemWidget::setMapItemModel(MapItemModel* mapItemModel)
{
    this->mapItemModel = mapItemModel;
    updateWidget();
}