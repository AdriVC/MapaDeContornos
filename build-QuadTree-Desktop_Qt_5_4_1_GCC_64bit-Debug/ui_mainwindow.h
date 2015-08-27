/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *b_fileOpen;
    QLineEdit *LE_imagePath;
    QLineEdit *LE_outputPath;
    QLabel *L_image;
    QLabel *L_output;
    QLabel *L_flecha;
    QLabel *L_titulo;
    QSpinBox *sB_profundidad;
    QLabel *L_profundidad;
    QPushButton *b_procesarImagen;
    QPushButton *b_exportarImagen;
    QLabel *label;
    QPushButton *all;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 540);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        b_fileOpen = new QPushButton(centralWidget);
        b_fileOpen->setObjectName(QStringLiteral("b_fileOpen"));
        b_fileOpen->setGeometry(QRect(20, 80, 25, 25));
        LE_imagePath = new QLineEdit(centralWidget);
        LE_imagePath->setObjectName(QStringLiteral("LE_imagePath"));
        LE_imagePath->setEnabled(false);
        LE_imagePath->setGeometry(QRect(50, 80, 271, 25));
        QFont font;
        font.setFamily(QStringLiteral("Bauhaus 93"));
        LE_imagePath->setFont(font);
        LE_outputPath = new QLineEdit(centralWidget);
        LE_outputPath->setObjectName(QStringLiteral("LE_outputPath"));
        LE_outputPath->setEnabled(false);
        LE_outputPath->setGeometry(QRect(410, 80, 271, 25));
        LE_outputPath->setFont(font);
        L_image = new QLabel(centralWidget);
        L_image->setObjectName(QStringLiteral("L_image"));
        L_image->setGeometry(QRect(50, 110, 270, 270));
        QFont font1;
        font1.setFamily(QStringLiteral("StarJedi Special Edition"));
        font1.setPointSize(15);
        L_image->setFont(font1);
        L_image->setAutoFillBackground(false);
        L_image->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width: 3px;\n"
"border-color:rgb(0, 0, 0);\n"
"background-color:rgb(255, 255, 255);"));
        L_image->setScaledContents(true);
        L_image->setAlignment(Qt::AlignCenter);
        L_output = new QLabel(centralWidget);
        L_output->setObjectName(QStringLiteral("L_output"));
        L_output->setGeometry(QRect(410, 110, 270, 270));
        QFont font2;
        font2.setFamily(QStringLiteral("Star Jedi"));
        font2.setPointSize(15);
        L_output->setFont(font2);
        L_output->setAutoFillBackground(false);
        L_output->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width: 3px;\n"
"border-color:rgb(0, 0, 0);\n"
"background-color:rgb(255, 255, 255);"));
        L_output->setScaledContents(true);
        L_output->setAlignment(Qt::AlignCenter);
        L_flecha = new QLabel(centralWidget);
        L_flecha->setObjectName(QStringLiteral("L_flecha"));
        L_flecha->setGeometry(QRect(300, 180, 128, 128));
        L_titulo = new QLabel(centralWidget);
        L_titulo->setObjectName(QStringLiteral("L_titulo"));
        L_titulo->setGeometry(QRect(80, 0, 581, 61));
        QFont font3;
        font3.setFamily(QStringLiteral("StarJedi Special Edition"));
        font3.setPointSize(50);
        L_titulo->setFont(font3);
        sB_profundidad = new QSpinBox(centralWidget);
        sB_profundidad->setObjectName(QStringLiteral("sB_profundidad"));
        sB_profundidad->setGeometry(QRect(50, 420, 121, 31));
        sB_profundidad->setFont(font1);
        sB_profundidad->setMinimum(-1);
        sB_profundidad->setValue(-1);
        L_profundidad = new QLabel(centralWidget);
        L_profundidad->setObjectName(QStringLiteral("L_profundidad"));
        L_profundidad->setGeometry(QRect(50, 400, 131, 16));
        L_profundidad->setFont(font1);
        b_procesarImagen = new QPushButton(centralWidget);
        b_procesarImagen->setObjectName(QStringLiteral("b_procesarImagen"));
        b_procesarImagen->setGeometry(QRect(190, 400, 121, 50));
        b_procesarImagen->setFont(font1);
        b_procesarImagen->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width: 3px;\n"
"border-color:rgb(0, 0, 0);\n"
"background-color:rgb(255, 255, 255);"));
        b_exportarImagen = new QPushButton(centralWidget);
        b_exportarImagen->setObjectName(QStringLiteral("b_exportarImagen"));
        b_exportarImagen->setGeometry(QRect(480, 400, 121, 50));
        b_exportarImagen->setFont(font1);
        b_exportarImagen->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width: 3px;\n"
"border-color:rgb(0, 0, 0);\n"
"background-color:rgb(255, 255, 255);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(440, 479, 271, 21));
        QFont font4;
        font4.setFamily(QStringLiteral("StarJedi Special Edition"));
        font4.setPointSize(12);
        label->setFont(font4);
        all = new QPushButton(centralWidget);
        all->setObjectName(QStringLiteral("all"));
        all->setGeometry(QRect(330, 400, 99, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        b_fileOpen->setText(QString());
        L_image->setText(QString());
        L_output->setText(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", 0));
        L_flecha->setText(QString());
        L_titulo->setText(QApplication::translate("MainWindow", "MAPA DE CoNToRNoS", 0));
        L_profundidad->setText(QApplication::translate("MainWindow", "Profundidad:", 0));
        b_procesarImagen->setText(QApplication::translate("MainWindow", "PRoCESAR", 0));
        b_exportarImagen->setText(QApplication::translate("MainWindow", "Exportar", 0));
        label->setText(QApplication::translate("MainWindow", "Por: Adriana vega y Fernando Reyes", 0));
        all->setText(QApplication::translate("MainWindow", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
