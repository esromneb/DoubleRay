/********************************************************************************
** Form generated from reading ui file 'control.ui'
**
** Created: Mon Mar 19 23:43:27 2007
**      by: Qt User Interface Compiler version 4.2.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

class Ui_control
{
public:
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *asdf;
    QSlider *kr;
    QLabel *label_6;
    QSlider *ks;
    QLabel *asdf_2;
    QSlider *kt;
    QLineEdit *nEdit;
    QLineEdit *selected;
    QSlider *ka;
    QWidget *layoutWidget_6;
    QHBoxLayout *hboxLayout;
    QLineEdit *kdR;
    QLineEdit *kdG;
    QLineEdit *kdB;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_8;
    QLineEdit *iaG;
    QLineEdit *iaB;
    QLineEdit *c;
    QLineEdit *iaR;
    QGroupBox *groupBox_2;
    QLabel *numLights;
    QLabel *label_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *hboxLayout1;
    QLineEdit *lightR;
    QLineEdit *lightG;
    QLineEdit *lightB;
    QLabel *label_10;
    QWidget *layoutWidget_3;
    QHBoxLayout *hboxLayout2;
    QLineEdit *lightx;
    QLineEdit *lighty;
    QLineEdit *lightz;
    QLabel *label_5;
    QLineEdit *lightEdit;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget_4;
    QHBoxLayout *hboxLayout3;
    QLineEdit *cameradx;
    QLineEdit *camerady;
    QLineEdit *cameradz;
    QWidget *layoutWidget_5;
    QHBoxLayout *hboxLayout4;
    QLineEdit *upx;
    QLineEdit *upy;
    QLineEdit *upz;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_11;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout5;
    QLineEdit *camerax;
    QLineEdit *cameray;
    QLineEdit *cameraz;
    QPushButton *exitButton;
    QGroupBox *groupBox_5;
    QLabel *label_14;
    QLineEdit *resolution;
    QLabel *label_15;
    QLineEdit *maxDepth;
    QPushButton *traceButton;

    void setupUi(QWidget *control)
    {
    control->setObjectName(QString::fromUtf8("control"));
    groupBox_3 = new QGroupBox(control);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    groupBox_3->setGeometry(QRect(210, 10, 161, 301));
    label_3 = new QLabel(groupBox_3);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(15, 20, 141, 28));
    label_9 = new QLabel(groupBox_3);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(85, 50, 16, 16));
    label_7 = new QLabel(groupBox_3);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(15, 90, 71, 16));
    label_4 = new QLabel(groupBox_3);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(15, 140, 129, 16));
    asdf = new QLabel(groupBox_3);
    asdf->setObjectName(QString::fromUtf8("asdf"));
    asdf->setGeometry(QRect(15, 180, 129, 16));
    kr = new QSlider(groupBox_3);
    kr->setObjectName(QString::fromUtf8("kr"));
    kr->setGeometry(QRect(15, 200, 129, 16));
    kr->setSliderPosition(50);
    kr->setOrientation(Qt::Horizontal);
    label_6 = new QLabel(groupBox_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(15, 220, 129, 16));
    ks = new QSlider(groupBox_3);
    ks->setObjectName(QString::fromUtf8("ks"));
    ks->setGeometry(QRect(15, 240, 129, 16));
    ks->setSliderPosition(50);
    ks->setOrientation(Qt::Horizontal);
    asdf_2 = new QLabel(groupBox_3);
    asdf_2->setObjectName(QString::fromUtf8("asdf_2"));
    asdf_2->setGeometry(QRect(15, 260, 129, 16));
    kt = new QSlider(groupBox_3);
    kt->setObjectName(QString::fromUtf8("kt"));
    kt->setGeometry(QRect(15, 280, 129, 16));
    kt->setSliderPosition(50);
    kt->setOrientation(Qt::Horizontal);
    nEdit = new QLineEdit(groupBox_3);
    nEdit->setObjectName(QString::fromUtf8("nEdit"));
    nEdit->setGeometry(QRect(105, 50, 31, 22));
    selected = new QLineEdit(groupBox_3);
    selected->setObjectName(QString::fromUtf8("selected"));
    selected->setGeometry(QRect(15, 50, 31, 22));
    selected->setReadOnly(true);
    ka = new QSlider(groupBox_3);
    ka->setObjectName(QString::fromUtf8("ka"));
    ka->setGeometry(QRect(15, 160, 129, 16));
    ka->setSliderPosition(25);
    ka->setOrientation(Qt::Horizontal);
    layoutWidget_6 = new QWidget(groupBox_3);
    layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
    layoutWidget_6->setGeometry(QRect(16, 110, 121, 24));
    hboxLayout = new QHBoxLayout(layoutWidget_6);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    kdR = new QLineEdit(layoutWidget_6);
    kdR->setObjectName(QString::fromUtf8("kdR"));

    hboxLayout->addWidget(kdR);

    kdG = new QLineEdit(layoutWidget_6);
    kdG->setObjectName(QString::fromUtf8("kdG"));

    hboxLayout->addWidget(kdG);

    kdB = new QLineEdit(layoutWidget_6);
    kdB->setObjectName(QString::fromUtf8("kdB"));

    hboxLayout->addWidget(kdB);

    groupBox = new QGroupBox(control);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 181, 131));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 20, 47, 14));
    label_8 = new QLabel(groupBox);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(10, 70, 116, 16));
    iaG = new QLineEdit(groupBox);
    iaG->setObjectName(QString::fromUtf8("iaG"));
    iaG->setGeometry(QRect(60, 90, 41, 22));
    iaB = new QLineEdit(groupBox);
    iaB->setObjectName(QString::fromUtf8("iaB"));
    iaB->setGeometry(QRect(110, 90, 41, 22));
    c = new QLineEdit(groupBox);
    c->setObjectName(QString::fromUtf8("c"));
    c->setGeometry(QRect(10, 40, 41, 22));
    iaR = new QLineEdit(groupBox);
    iaR->setObjectName(QString::fromUtf8("iaR"));
    iaR->setGeometry(QRect(10, 90, 41, 22));
    groupBox_2 = new QGroupBox(control);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(10, 160, 181, 181));
    numLights = new QLabel(groupBox_2);
    numLights->setObjectName(QString::fromUtf8("numLights"));
    numLights->setGeometry(QRect(61, 20, 13, 16));
    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 80, 97, 16));
    layoutWidget_2 = new QWidget(groupBox_2);
    layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
    layoutWidget_2->setGeometry(QRect(10, 147, 121, 24));
    hboxLayout1 = new QHBoxLayout(layoutWidget_2);
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    lightR = new QLineEdit(layoutWidget_2);
    lightR->setObjectName(QString::fromUtf8("lightR"));

    hboxLayout1->addWidget(lightR);

    lightG = new QLineEdit(layoutWidget_2);
    lightG->setObjectName(QString::fromUtf8("lightG"));

    hboxLayout1->addWidget(lightG);

    lightB = new QLineEdit(layoutWidget_2);
    lightB->setObjectName(QString::fromUtf8("lightB"));

    hboxLayout1->addWidget(lightB);

    label_10 = new QLabel(groupBox_2);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(10, 130, 101, 16));
    layoutWidget_3 = new QWidget(groupBox_2);
    layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
    layoutWidget_3->setGeometry(QRect(10, 100, 121, 24));
    hboxLayout2 = new QHBoxLayout(layoutWidget_3);
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    lightx = new QLineEdit(layoutWidget_3);
    lightx->setObjectName(QString::fromUtf8("lightx"));

    hboxLayout2->addWidget(lightx);

    lighty = new QLineEdit(layoutWidget_3);
    lighty->setObjectName(QString::fromUtf8("lighty"));

    hboxLayout2->addWidget(lighty);

    lightz = new QLineEdit(layoutWidget_3);
    lightz->setObjectName(QString::fromUtf8("lightz"));

    hboxLayout2->addWidget(lightz);

    label_5 = new QLabel(groupBox_2);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(10, 20, 150, 28));
    lightEdit = new QLineEdit(groupBox_2);
    lightEdit->setObjectName(QString::fromUtf8("lightEdit"));
    lightEdit->setGeometry(QRect(10, 50, 31, 22));
    groupBox_4 = new QGroupBox(control);
    groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
    groupBox_4->setGeometry(QRect(210, 320, 161, 181));
    layoutWidget_4 = new QWidget(groupBox_4);
    layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
    layoutWidget_4->setGeometry(QRect(10, 90, 121, 24));
    hboxLayout3 = new QHBoxLayout(layoutWidget_4);
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    cameradx = new QLineEdit(layoutWidget_4);
    cameradx->setObjectName(QString::fromUtf8("cameradx"));

    hboxLayout3->addWidget(cameradx);

    camerady = new QLineEdit(layoutWidget_4);
    camerady->setObjectName(QString::fromUtf8("camerady"));

    hboxLayout3->addWidget(camerady);

    cameradz = new QLineEdit(layoutWidget_4);
    cameradz->setObjectName(QString::fromUtf8("cameradz"));

    hboxLayout3->addWidget(cameradz);

    layoutWidget_5 = new QWidget(groupBox_4);
    layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
    layoutWidget_5->setGeometry(QRect(10, 140, 121, 24));
    hboxLayout4 = new QHBoxLayout(layoutWidget_5);
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    upx = new QLineEdit(layoutWidget_5);
    upx->setObjectName(QString::fromUtf8("upx"));

    hboxLayout4->addWidget(upx);

    upy = new QLineEdit(layoutWidget_5);
    upy->setObjectName(QString::fromUtf8("upy"));

    hboxLayout4->addWidget(upy);

    upz = new QLineEdit(layoutWidget_5);
    upz->setObjectName(QString::fromUtf8("upz"));

    hboxLayout4->addWidget(upz);

    label_12 = new QLabel(groupBox_4);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(10, 70, 51, 16));
    label_13 = new QLabel(groupBox_4);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(10, 120, 51, 16));
    label_11 = new QLabel(groupBox_4);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(10, 20, 41, 16));
    layoutWidget = new QWidget(groupBox_4);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 40, 121, 24));
    hboxLayout5 = new QHBoxLayout(layoutWidget);
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    camerax = new QLineEdit(layoutWidget);
    camerax->setObjectName(QString::fromUtf8("camerax"));

    hboxLayout5->addWidget(camerax);

    cameray = new QLineEdit(layoutWidget);
    cameray->setObjectName(QString::fromUtf8("cameray"));

    hboxLayout5->addWidget(cameray);

    cameraz = new QLineEdit(layoutWidget);
    cameraz->setObjectName(QString::fromUtf8("cameraz"));

    hboxLayout5->addWidget(cameraz);

    exitButton = new QPushButton(control);
    exitButton->setObjectName(QString::fromUtf8("exitButton"));
    exitButton->setGeometry(QRect(10, 520, 81, 24));
    groupBox_5 = new QGroupBox(control);
    groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
    groupBox_5->setGeometry(QRect(10, 350, 191, 91));
    label_14 = new QLabel(groupBox_5);
    label_14->setObjectName(QString::fromUtf8("label_14"));
    label_14->setGeometry(QRect(10, 20, 53, 16));
    resolution = new QLineEdit(groupBox_5);
    resolution->setObjectName(QString::fromUtf8("resolution"));
    resolution->setGeometry(QRect(10, 40, 31, 22));
    label_15 = new QLabel(groupBox_5);
    label_15->setObjectName(QString::fromUtf8("label_15"));
    label_15->setGeometry(QRect(110, 20, 61, 16));
    maxDepth = new QLineEdit(groupBox_5);
    maxDepth->setObjectName(QString::fromUtf8("maxDepth"));
    maxDepth->setGeometry(QRect(110, 40, 31, 22));
    traceButton = new QPushButton(control);
    traceButton->setObjectName(QString::fromUtf8("traceButton"));
    traceButton->setGeometry(QRect(300, 520, 75, 24));

    retranslateUi(control);

    QSize size(397, 554);
    size = size.expandedTo(control->minimumSizeHint());
    control->resize(size);


    QMetaObject::connectSlotsByName(control);
    } // setupUi

    void retranslateUi(QWidget *control)
    {
    control->setWindowTitle(QApplication::translate("control", "ToolBox", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QApplication::translate("control", "Objects", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("control", "Click on a object to select it\n"
"Current Poly:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("control", "N:", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("control", "Kd (Also color):", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("control", "Ka", 0, QApplication::UnicodeUTF8));
    asdf->setText(QApplication::translate("control", "Kr", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("control", "Ks", 0, QApplication::UnicodeUTF8));
    asdf_2->setText(QApplication::translate("control", "Kt", 0, QApplication::UnicodeUTF8));
    nEdit->setText(QApplication::translate("control", "2", 0, QApplication::UnicodeUTF8));
    selected->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    kdR->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    kdG->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    kdB->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("control", "Global", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("control", "Const C:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("control", "Ambient Intensity (Color):", 0, QApplication::UnicodeUTF8));
    iaG->setText(QApplication::translate("control", "5", 0, QApplication::UnicodeUTF8));
    iaB->setText(QApplication::translate("control", "5", 0, QApplication::UnicodeUTF8));
    c->setText(QApplication::translate("control", "5", 0, QApplication::UnicodeUTF8));
    iaR->setText(QApplication::translate("control", "5", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("control", "Lights", 0, QApplication::UnicodeUTF8));
    numLights->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("control", "Direction Vector:", 0, QApplication::UnicodeUTF8));
    lightR->setText(QApplication::translate("control", "-1", 0, QApplication::UnicodeUTF8));
    lightG->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    lightB->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("control", "Light Intensity (Color):", 0, QApplication::UnicodeUTF8));
    lightx->setText(QApplication::translate("control", "-1", 0, QApplication::UnicodeUTF8));
    lighty->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    lightz->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("control", "There are     lights in this scene.\n"
"Choose one to edit.", 0, QApplication::UnicodeUTF8));
    lightEdit->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    groupBox_4->setTitle(QApplication::translate("control", "Camera", 0, QApplication::UnicodeUTF8));
    cameradx->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    camerady->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    cameradz->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    upx->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    upy->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    upz->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("control", "Direction:", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("control", "Up:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("control", "Origin:", 0, QApplication::UnicodeUTF8));
    camerax->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    cameray->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    cameraz->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    exitButton->setText(QApplication::translate("control", "Exit", 0, QApplication::UnicodeUTF8));
    groupBox_5->setTitle(QApplication::translate("control", "Rendering:", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("control", "Resolution:", 0, QApplication::UnicodeUTF8));
    resolution->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    label_15->setText(QApplication::translate("control", "Max Depth:", 0, QApplication::UnicodeUTF8));
    maxDepth->setText(QApplication::translate("control", "0", 0, QApplication::UnicodeUTF8));
    traceButton->setText(QApplication::translate("control", "Ray Trace", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(control);
    } // retranslateUi

};

namespace Ui {
    class control: public Ui_control {};
} // namespace Ui

#endif // UI_CONTROL_H
