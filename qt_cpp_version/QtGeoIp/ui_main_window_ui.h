/********************************************************************************
** Form generated from reading UI file 'main_window_ui.ui'
**
** Created: Mon Sep 24 01:20:19 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_UI_H
#define UI_MAIN_WINDOW_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QFrame *mapFrame;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *middleVerticalLayout;
    QGroupBox *informationGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *longitudeLabel;
    QLabel *label_4;
    QLabel *regionLabel;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *latitudeLabel;
    QLabel *cityLabel;
    QLabel *countryLabel;
    QLabel *label_5;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QPushButton *searchButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(731, 599);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mapFrame = new QFrame(centralwidget);
        mapFrame->setObjectName(QString::fromUtf8("mapFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapFrame->sizePolicy().hasHeightForWidth());
        mapFrame->setSizePolicy(sizePolicy);
        mapFrame->setFrameShape(QFrame::Box);
        horizontalLayout = new QHBoxLayout(mapFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        middleVerticalLayout = new QVBoxLayout();
        middleVerticalLayout->setObjectName(QString::fromUtf8("middleVerticalLayout"));

        horizontalLayout->addLayout(middleVerticalLayout);


        gridLayout->addWidget(mapFrame, 5, 0, 1, 3);

        informationGroupBox = new QGroupBox(centralwidget);
        informationGroupBox->setObjectName(QString::fromUtf8("informationGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(informationGroupBox->sizePolicy().hasHeightForWidth());
        informationGroupBox->setSizePolicy(sizePolicy1);
        informationGroupBox->setMaximumSize(QSize(431, 122));
        gridLayout_3 = new QGridLayout(informationGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        longitudeLabel = new QLabel(informationGroupBox);
        longitudeLabel->setObjectName(QString::fromUtf8("longitudeLabel"));

        gridLayout_3->addWidget(longitudeLabel, 3, 1, 1, 1);

        label_4 = new QLabel(informationGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        regionLabel = new QLabel(informationGroupBox);
        regionLabel->setObjectName(QString::fromUtf8("regionLabel"));

        gridLayout_3->addWidget(regionLabel, 2, 1, 1, 1);

        label_2 = new QLabel(informationGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_6 = new QLabel(informationGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        label_3 = new QLabel(informationGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        latitudeLabel = new QLabel(informationGroupBox);
        latitudeLabel->setObjectName(QString::fromUtf8("latitudeLabel"));

        gridLayout_3->addWidget(latitudeLabel, 4, 1, 1, 1);

        cityLabel = new QLabel(informationGroupBox);
        cityLabel->setObjectName(QString::fromUtf8("cityLabel"));

        gridLayout_3->addWidget(cityLabel, 1, 1, 1, 1);

        countryLabel = new QLabel(informationGroupBox);
        countryLabel->setObjectName(QString::fromUtf8("countryLabel"));

        gridLayout_3->addWidget(countryLabel, 0, 1, 1, 1);

        label_5 = new QLabel(informationGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);


        gridLayout->addWidget(informationGroupBox, 1, 0, 1, 2);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ipLineEdit = new QLineEdit(frame);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));

        horizontalLayout_2->addWidget(ipLineEdit);

        searchButton = new QPushButton(frame);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        horizontalLayout_2->addWidget(searchButton);


        gridLayout->addWidget(frame, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 731, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(ipLineEdit, SIGNAL(returnPressed()), searchButton, SLOT(click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        informationGroupBox->setTitle(QApplication::translate("MainWindow", "IP Information", 0, QApplication::UnicodeUTF8));
        longitudeLabel->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Longitude:", 0, QApplication::UnicodeUTF8));
        regionLabel->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "City:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Country:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Region:", 0, QApplication::UnicodeUTF8));
        latitudeLabel->setText(QString());
        cityLabel->setText(QString());
        countryLabel->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Latitude:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "IP Address:", 0, QApplication::UnicodeUTF8));
        ipLineEdit->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_UI_H
