/* 
 * File:   CustomMarbleWidget.h
 * Author: andre
 *
 * Created on September 24, 2012, 1:25 AM
 */

#ifndef CUSTOMMARBLEWIDGET_H
#define	CUSTOMMARBLEWIDGET_H

#include <marble/MarbleWidget.h>

using namespace Marble;
using namespace std;


typedef struct MarkerTag {
	float latitude;
	float longitude;
        string text;
} Marker;

class CustomMarbleWidget : public MarbleWidget {
public:
    CustomMarbleWidget();
    virtual ~CustomMarbleWidget();

    /**
     * 
     * @param marker
     * @return 
     */
    void addMarker(const Marker& marker);

protected:
    virtual void customPaint(GeoPainter* painter);
private:
    Marker* marker;

};

#endif	/* CUSTOMMARBLEWIDGET_H */

