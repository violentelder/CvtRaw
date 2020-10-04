/********************************************************************************
** Form generated from reading UI file 'cvtraw.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CVTRAW_H
#define UI_CVTRAW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CvtRawClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_Mono8;
    QRadioButton *radioButton_bayer8;
    QRadioButton *radioButton_RGB8;
    QRadioButton *radioButton_ABC32;
    QRadioButton *radioButton_ABC32F;
    QRadioButton *radioButton_ABC32FP;
    QRadioButton *radioButton_C32;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_width;
    QLineEdit *lineEdit_width;
    QLabel *label_height;
    QCheckBox *checkBox_chunkdata;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_8bit;
    QRadioButton *radioButton_16bit;
    QRadioButton *radioButton_ply;
    QPushButton *pushButton_convert;
    QLineEdit *lineEdit_height;
    QPushButton *pushButton_change;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_openfile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CvtRawClass)
    {
        if (CvtRawClass->objectName().isEmpty())
            CvtRawClass->setObjectName(QStringLiteral("CvtRawClass"));
        CvtRawClass->resize(1072, 753);
        centralWidget = new QWidget(CvtRawClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_Mono8 = new QRadioButton(groupBox_2);
        radioButton_Mono8->setObjectName(QStringLiteral("radioButton_Mono8"));

        verticalLayout_3->addWidget(radioButton_Mono8);

        radioButton_bayer8 = new QRadioButton(groupBox_2);
        radioButton_bayer8->setObjectName(QStringLiteral("radioButton_bayer8"));

        verticalLayout_3->addWidget(radioButton_bayer8);

        radioButton_RGB8 = new QRadioButton(groupBox_2);
        radioButton_RGB8->setObjectName(QStringLiteral("radioButton_RGB8"));

        verticalLayout_3->addWidget(radioButton_RGB8);

        radioButton_ABC32 = new QRadioButton(groupBox_2);
        radioButton_ABC32->setObjectName(QStringLiteral("radioButton_ABC32"));

        verticalLayout_3->addWidget(radioButton_ABC32);

        radioButton_ABC32F = new QRadioButton(groupBox_2);
        radioButton_ABC32F->setObjectName(QStringLiteral("radioButton_ABC32F"));

        verticalLayout_3->addWidget(radioButton_ABC32F);

        radioButton_ABC32FP = new QRadioButton(groupBox_2);
        radioButton_ABC32FP->setObjectName(QStringLiteral("radioButton_ABC32FP"));

        verticalLayout_3->addWidget(radioButton_ABC32FP);

        radioButton_C32 = new QRadioButton(groupBox_2);
        radioButton_C32->setObjectName(QStringLiteral("radioButton_C32"));
        radioButton_C32->setAutoRepeat(true);

        verticalLayout_3->addWidget(radioButton_C32);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        label_width = new QLabel(centralWidget);
        label_width->setObjectName(QStringLiteral("label_width"));
        sizePolicy.setHeightForWidth(label_width->sizePolicy().hasHeightForWidth());
        label_width->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_width, 4, 0, 1, 2);

        lineEdit_width = new QLineEdit(centralWidget);
        lineEdit_width->setObjectName(QStringLiteral("lineEdit_width"));
        sizePolicy.setHeightForWidth(lineEdit_width->sizePolicy().hasHeightForWidth());
        lineEdit_width->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_width, 5, 0, 1, 2);

        label_height = new QLabel(centralWidget);
        label_height->setObjectName(QStringLiteral("label_height"));
        sizePolicy.setHeightForWidth(label_height->sizePolicy().hasHeightForWidth());
        label_height->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_height, 6, 0, 1, 2);

        checkBox_chunkdata = new QCheckBox(centralWidget);
        checkBox_chunkdata->setObjectName(QStringLiteral("checkBox_chunkdata"));
        checkBox_chunkdata->setChecked(false);

        gridLayout->addWidget(checkBox_chunkdata, 8, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(28, 28, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 9, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioButton_8bit = new QRadioButton(groupBox);
        radioButton_8bit->setObjectName(QStringLiteral("radioButton_8bit"));
        radioButton_8bit->setCheckable(true);
        radioButton_8bit->setChecked(true);
        radioButton_8bit->setAutoExclusive(true);

        verticalLayout_2->addWidget(radioButton_8bit);

        radioButton_16bit = new QRadioButton(groupBox);
        radioButton_16bit->setObjectName(QStringLiteral("radioButton_16bit"));

        verticalLayout_2->addWidget(radioButton_16bit);

        radioButton_ply = new QRadioButton(groupBox);
        radioButton_ply->setObjectName(QStringLiteral("radioButton_ply"));

        verticalLayout_2->addWidget(radioButton_ply);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        pushButton_convert = new QPushButton(centralWidget);
        pushButton_convert->setObjectName(QStringLiteral("pushButton_convert"));

        gridLayout->addWidget(pushButton_convert, 10, 0, 1, 2);

        lineEdit_height = new QLineEdit(centralWidget);
        lineEdit_height->setObjectName(QStringLiteral("lineEdit_height"));
        sizePolicy.setHeightForWidth(lineEdit_height->sizePolicy().hasHeightForWidth());
        lineEdit_height->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_height, 7, 0, 1, 2);

        pushButton_change = new QPushButton(centralWidget);
        pushButton_change->setObjectName(QStringLiteral("pushButton_change"));

        gridLayout->addWidget(pushButton_change, 9, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setAutoFillBackground(true);
        graphicsView->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(graphicsView, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(241, 20));
        lineEdit->setCursor(QCursor(Qt::ForbiddenCursor));
        lineEdit->setMouseTracking(false);
        lineEdit->setFocusPolicy(Qt::NoFocus);
        lineEdit->setAcceptDrops(false);

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_openfile = new QPushButton(centralWidget);
        pushButton_openfile->setObjectName(QStringLiteral("pushButton_openfile"));

        horizontalLayout->addWidget(pushButton_openfile);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        CvtRawClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CvtRawClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1072, 26));
        CvtRawClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CvtRawClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CvtRawClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CvtRawClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CvtRawClass->setStatusBar(statusBar);

        retranslateUi(CvtRawClass);

        QMetaObject::connectSlotsByName(CvtRawClass);
    } // setupUi

    void retranslateUi(QMainWindow *CvtRawClass)
    {
        CvtRawClass->setWindowTitle(QApplication::translate("CvtRawClass", "CvtRaw", 0));
        groupBox_2->setTitle(QString());
        radioButton_Mono8->setText(QApplication::translate("CvtRawClass", "Mono8", 0));
        radioButton_bayer8->setText(QApplication::translate("CvtRawClass", "Bayer8 GB", 0));
        radioButton_RGB8->setText(QApplication::translate("CvtRawClass", "RGB 8", 0));
        radioButton_ABC32->setText(QApplication::translate("CvtRawClass", "ABC32", 0));
        radioButton_ABC32F->setText(QApplication::translate("CvtRawClass", "ABC32f", 0));
        radioButton_ABC32FP->setText(QApplication::translate("CvtRawClass", "ABC32f_Planer", 0));
        radioButton_C32->setText(QApplication::translate("CvtRawClass", "C32", 0));
        label_3->setText(QApplication::translate("CvtRawClass", "\346\225\260\346\215\256\346\240\274\345\274\217\357\274\232", 0));
        label_width->setText(QApplication::translate("CvtRawClass", "\345\233\276\345\203\217\345\256\275\345\272\246\357\274\232", 0));
        label_height->setText(QApplication::translate("CvtRawClass", "\345\233\276\345\203\217\351\253\230\345\272\246\357\274\232", 0));
        checkBox_chunkdata->setText(QApplication::translate("CvtRawClass", "Chunk Data", 0));
        groupBox->setTitle(QString());
        radioButton_8bit->setText(QApplication::translate("CvtRawClass", "8Bit(Mono8)", 0));
        radioButton_16bit->setText(QApplication::translate("CvtRawClass", "16Bit(RGB556)", 0));
        radioButton_ply->setText(QApplication::translate("CvtRawClass", "\347\202\271\344\272\221\357\274\210*.ply\357\274\211", 0));
        pushButton_convert->setText(QApplication::translate("CvtRawClass", "\350\275\254\346\215\242", 0));
        pushButton_change->setText(QApplication::translate("CvtRawClass", "\344\272\256\345\272\246\345\233\276", 0));
        label->setText(QApplication::translate("CvtRawClass", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", 0));
        pushButton_openfile->setText(QApplication::translate("CvtRawClass", "\346\211\223\345\274\200", 0));
    } // retranslateUi

};

namespace Ui {
    class CvtRawClass: public Ui_CvtRawClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CVTRAW_H
