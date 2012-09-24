/* 
 * File:   CustomMarbleWidget.cpp
 * Author: andre
 * 
 * Created on September 24, 2012, 1:25 AM
 */

#include "CustomMarbleWidget.h"
#include <marble/GeoPainter.h>

CustomMarbleWidget::CustomMarbleWidget()
{
    this->marker = NULL; // TODO: DRY
}

CustomMarbleWidget::~CustomMarbleWidget()
{
    if(marker != NULL)
    {
        delete marker;
        marker = NULL;
   }
}

void CustomMarbleWidget::addMarker(const Marker& marker)
{
    this->marker = new Marker;
    this->marker->latitude = marker.latitude;
    this->marker->longitude = marker.longitude;
    this->marker->text = marker.text;
    repaint();
}

void CustomMarbleWidget::customPaint(GeoPainter* painter)
{
        if (marker != NULL)
        {
            painter->setPen(Qt::black);
            GeoDataCoordinates home(
                marker->longitude,
                marker->latitude,
                0.0, GeoDataCoordinates::Degree);
            painter->drawEllipse(home, 7, 7);
            painter->drawText(home, QString::fromStdString(marker->text));
        }
}