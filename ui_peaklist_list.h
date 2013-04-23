/********************************************************************************
** Form generated from reading UI file 'peaklist_list.ui'
**
** Created: Tue Apr 23 10:19:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEAKLIST_LIST_H
#define UI_PEAKLIST_LIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_listView
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *pk_bt_info;
    QPushButton *pk_bt_uncheck;
    QPushButton *pk_bt_clean;
    QPushButton *pk_bt_peaklist;
    QPushButton *pk_bt_replica;
    QPushButton *pk_bt_analyzer_peaklist;

    void setupUi(QWidget *listView)
    {
        if (listView->objectName().isEmpty())
            listView->setObjectName(QString::fromUtf8("listView"));
        listView->resize(285, 62);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(listView);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 3, 0, 0);
        pk_bt_info = new QPushButton(listView);
        pk_bt_info->setObjectName(QString::fromUtf8("pk_bt_info"));
        pk_bt_info->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pk_bt_info->sizePolicy().hasHeightForWidth());
        pk_bt_info->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pk_bt_info, 1, 0, 1, 1);

        pk_bt_uncheck = new QPushButton(listView);
        pk_bt_uncheck->setObjectName(QString::fromUtf8("pk_bt_uncheck"));
        pk_bt_uncheck->setEnabled(false);
        sizePolicy1.setHeightForWidth(pk_bt_uncheck->sizePolicy().hasHeightForWidth());
        pk_bt_uncheck->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pk_bt_uncheck, 1, 1, 1, 1);

        pk_bt_clean = new QPushButton(listView);
        pk_bt_clean->setObjectName(QString::fromUtf8("pk_bt_clean"));
        pk_bt_clean->setEnabled(false);
        sizePolicy1.setHeightForWidth(pk_bt_clean->sizePolicy().hasHeightForWidth());
        pk_bt_clean->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pk_bt_clean, 1, 2, 1, 1);

        pk_bt_peaklist = new QPushButton(listView);
        pk_bt_peaklist->setObjectName(QString::fromUtf8("pk_bt_peaklist"));
        sizePolicy1.setHeightForWidth(pk_bt_peaklist->sizePolicy().hasHeightForWidth());
        pk_bt_peaklist->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pk_bt_peaklist, 2, 0, 1, 1);

        pk_bt_replica = new QPushButton(listView);
        pk_bt_replica->setObjectName(QString::fromUtf8("pk_bt_replica"));
        sizePolicy1.setHeightForWidth(pk_bt_replica->sizePolicy().hasHeightForWidth());
        pk_bt_replica->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pk_bt_replica, 2, 1, 1, 1);

        pk_bt_analyzer_peaklist = new QPushButton(listView);
        pk_bt_analyzer_peaklist->setObjectName(QString::fromUtf8("pk_bt_analyzer_peaklist"));
        pk_bt_analyzer_peaklist->setEnabled(false);
        sizePolicy1.setHeightForWidth(pk_bt_analyzer_peaklist->sizePolicy().hasHeightForWidth());
        pk_bt_analyzer_peaklist->setSizePolicy(sizePolicy1);
        pk_bt_analyzer_peaklist->setChecked(false);

        gridLayout_2->addWidget(pk_bt_analyzer_peaklist, 2, 2, 1, 1);


        retranslateUi(listView);

        QMetaObject::connectSlotsByName(listView);
    } // setupUi

    void retranslateUi(QWidget *listView)
    {
        listView->setWindowTitle(QApplication::translate("listView", "Form", 0, QApplication::UnicodeUTF8));
        pk_bt_info->setText(QApplication::translate("listView", "Export", 0, QApplication::UnicodeUTF8));
        pk_bt_uncheck->setText(QApplication::translate("listView", "Uncheck All", 0, QApplication::UnicodeUTF8));
        pk_bt_clean->setText(QApplication::translate("listView", "Clean", 0, QApplication::UnicodeUTF8));
        pk_bt_peaklist->setText(QApplication::translate("listView", "Peaklist", 0, QApplication::UnicodeUTF8));
        pk_bt_replica->setText(QApplication::translate("listView", "Replica", 0, QApplication::UnicodeUTF8));
        pk_bt_analyzer_peaklist->setText(QApplication::translate("listView", "Database", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class listView: public Ui_listView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEAKLIST_LIST_H
