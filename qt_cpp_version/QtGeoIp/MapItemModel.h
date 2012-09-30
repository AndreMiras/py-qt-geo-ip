/* 
 * File:   MapItemModel.h
 * Author: andre
 *
 * Created on September 30, 2012, 3:15 PM
 */

#ifndef MAPITEMMODEL_H
#define	MAPITEMMODEL_H

#include <QString>

class MapItemModel {
public:
    MapItemModel(const QString& name);
    MapItemModel(const MapItemModel& orig);
    virtual ~MapItemModel();
    void setName(const QString& name);
    void setDescription(const QString& description);
    void setDownloadLink(const QString& downloadLink);
    QString getName();
    QString getDescription();
    QString getDownloadLink();
private:
    QString name;
    QString description;
    QString downloadLink;
};

#endif	/* MAPITEMMODEL_H */

