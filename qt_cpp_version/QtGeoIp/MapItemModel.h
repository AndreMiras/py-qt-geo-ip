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
    virtual ~MapItemModel();
    void setName(const QString& name);
    void setDescription(const QString& description);
    void setDownloadLink(const QString& downloadLink);
    void setImageLink(const QString& imageLink);
    QString getName() const;
    QString getDescription() const;
    QString getDownloadLink() const;
    QString getImageLink() const;
private:
    QString name;
    QString description;
    QString downloadLink;
    QString imageLink;
};

#endif	/* MAPITEMMODEL_H */

