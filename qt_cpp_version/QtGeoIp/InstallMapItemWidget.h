/* 
 * File:   InstallMapItemWidget.h
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 */

#ifndef _INSTALLMAPITEMWIDGET_H
#define	_INSTALLMAPITEMWIDGET_H

#include "ui_InstallMapItemWidget.h"
#include "MapItemModel.h"

class InstallMapItemWidget : public QWidget {
    Q_OBJECT
public:
    InstallMapItemWidget(MapItemModel* mapItemModel);
    virtual ~InstallMapItemWidget();
    MapItemModel* getMapItemModel();
    void setMapItemModel(MapItemModel* mapItemModel);
private:
    Ui::InstallMapItemWidget widget;
    MapItemModel* mapItemModel;
    void updateWidget();
};

#endif	/* _INSTALLMAPITEMWIDGET_H */
