/********************************************************************************
** Form generated from reading UI file 'dictionary.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICTIONARY_H
#define UI_DICTIONARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dictionary
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QLabel *label;
    QLabel *label_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Dictionary)
    {
        if (Dictionary->objectName().isEmpty())
            Dictionary->setObjectName(QString::fromUtf8("Dictionary"));
        Dictionary->resize(584, 322);
        centralWidget = new QWidget(Dictionary);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(430, 30, 89, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Source Code Pro"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(140, 20, 181, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Source Code Pro"));
        font1.setPointSize(14);
        textEdit->setFont(font1);
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(140, 140, 361, 101));
        textEdit_2->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 71, 31));
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 140, 101, 91));
        label_2->setFont(font);
        Dictionary->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Dictionary);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Dictionary->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Dictionary);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Dictionary->setStatusBar(statusBar);

        retranslateUi(Dictionary);

        QMetaObject::connectSlotsByName(Dictionary);
    } // setupUi

    void retranslateUi(QMainWindow *Dictionary)
    {
        Dictionary->setWindowTitle(QApplication::translate("Dictionary", "Dictionary", nullptr));
        pushButton->setText(QApplication::translate("Dictionary", "Search", nullptr));
        label->setText(QApplication::translate("Dictionary", "Word", nullptr));
        label_2->setText(QApplication::translate("Dictionary", "Meaning", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dictionary: public Ui_Dictionary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICTIONARY_H
