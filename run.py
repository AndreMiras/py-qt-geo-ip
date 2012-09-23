#!/usr/bin/python2 -d
"""
Runs the GUI and hooks signals and slots.
"""
import sys
import GeoIP
from PyKDE4.marble import Marble
from PyQt4 import QtCore, QtGui
from main_window_ui import Ui_MainWindow as MainWindowUi
from custom_marble_widget import CustomMarbleWidget


class MainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        # QtGui.QWidget.__init__(self, parent)
        # super(MainWindow, self).__init__(parent)
        QtGui.QMainWindow.__init__(self)
        self.ui = MainWindowUi()
        self.ui.setupUi(self)
        QtCore.QObject.connect(
            self.ui.searchButton,
            QtCore.SIGNAL("clicked()"),
            self.geocode_ip)

        self.marble = CustomMarbleWidget()
        self.marble.resize(640, 640)
        self.marble.adjustSize()
        # self.marble.setMapThemeId("earth/openstreetmap/openstreetmap.dgml")
        # self.marble.setMapThemeId("earth/bluemarble/bluemarble.dgml")
        self.marble.setMapThemeId("earth/plain/plain.dgml")
        # self.setCentralWidget(self.marble)
        self.ui.middleVerticalLayout.addWidget(self.marble)
        # self.marble.zoomView(1500)
        self.marble.zoomView(1000)
        self.marble.setAnimationsEnabled(True)

    def get_ip_record(self, ip):
        """
        Returns the ip information dictionary from ip.
        """
        gi = GeoIP.open(
            "/usr/share/GeoIP/GeoLiteCity.dat",
            GeoIP.GEOIP_STANDARD)
        record_by_addr = gi.record_by_addr(ip)
        if record_by_addr:
            record_by_addr.update({'ip': ip})
        return record_by_addr

    def update_labels_from_record(self, record_by_addr):
        """
        Updates the IP information box labels.
        """
        city = 'Unknown'
        region_name = 'Unknown'
        country_name = 'Unknown'
        latitude = 'Unknown'
        longitude = 'Unknown'
        if record_by_addr:
            latitude = record_by_addr["latitude"]
            longitude = record_by_addr["longitude"]
            city = record_by_addr['city']
            region_name = record_by_addr['region_name']
            country_name = record_by_addr['country_name']
        # setting labels
        self.ui.cityLabel.setText(city)
        self.ui.regionLabel.setText(region_name)
        self.ui.countryLabel.setText(country_name)
        self.ui.longitudeLabel.setText(str(longitude))
        self.ui.latitudeLabel.setText(str(latitude))

    def update_map_from_record(self, record_by_addr):
        """
        Adds map marker from ip dictionary information (lat, long).
        """
        if record_by_addr:
            ip = record_by_addr["ip"]
            latitude = record_by_addr["latitude"]
            longitude = record_by_addr["longitude"]
            coordinates = Marble.GeoDataCoordinates(longitude, latitude)
            self.marble.addMarker(coordinates, ip)
            self.marble.centerOn(longitude, latitude, True)
            # self.marble.zoomView(1500, Marble.Linear)

    def geocode_ip(self):
        """
        Geocodes IP:
            - retrieves IP information
            - places map marker from ip lat/long
        """
        ip = str(self.ui.ipLineEdit.text())
        record_by_addr = self.get_ip_record(ip)
        self.update_labels_from_record(record_by_addr)
        self.update_map_from_record(record_by_addr)


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = MainWindow()
    myapp.show()
    sys.exit(app.exec_())
