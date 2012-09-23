from PyKDE4.marble import Marble
from PyQt4 import QtCore


class CustomMarbleWidget(Marble.MarbleWidget):
    """
    Extends Marble.MarbleWidget marking it possible to easily add
    markers on the map.
    I've made it that way because MarbleWidget Model seems broken
    in Marble 4.8.5 Python binding.
    """
    def __init__(self):
        super(CustomMarbleWidget, self).__init__()
        self.marker = None

    def addMarker(self, geoDataCoordinates, text):
        self.marker = {
            'geoDataCoordinates': geoDataCoordinates,
            'text': text
        }
        self.repaint()

    def customPaint(self, painter):
        marker = self.marker
        if marker:
            painter.setPen(QtCore.Qt.black)
            home = Marble.GeoDataCoordinates(
                marker['geoDataCoordinates'].longitude(),
                marker['geoDataCoordinates'].latitude(),
                0.0, Marble.GeoDataCoordinates.Degree)
            painter.drawEllipse(home, 7, 7)
            painter.drawText(home, marker['text'])
