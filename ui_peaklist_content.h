/********************************************************************************
** Form generated from reading UI file 'peaklist_content.ui'
**
** Created: Tue Apr 23 10:19:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEAKLIST_CONTENT_H
#define UI_PEAKLIST_CONTENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pk_content
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *pk_content_tab;
    QWidget *pk_tables_plots;
    QGridLayout *gridLayout;
    QWidget *pk_tables;
    QGridLayout *gridLayout_5;
    QWidget *pk_plots;
    QGridLayout *gridLayout_4;
    QWidget *pk_proteins;
    QGridLayout *gridLayout_6;
    QWidget *pk_groups;
    QGridLayout *gridLayout_7;
    QWidget *pk_distance;
    QGridLayout *gridLayout_8;
    QWidget *pk_informations;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *pk_content)
    {
        if (pk_content->objectName().isEmpty())
            pk_content->setObjectName(QString::fromUtf8("pk_content"));
        pk_content->resize(902, 320);
        pk_content->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(pk_content);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pk_content_tab = new QTabWidget(pk_content);
        pk_content_tab->setObjectName(QString::fromUtf8("pk_content_tab"));
        pk_content_tab->setEnabled(true);
        pk_tables_plots = new QWidget();
        pk_tables_plots->setObjectName(QString::fromUtf8("pk_tables_plots"));
        pk_tables_plots->setEnabled(true);
        gridLayout = new QGridLayout(pk_tables_plots);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pk_content_tab->addTab(pk_tables_plots, QString());
        pk_tables = new QWidget();
        pk_tables->setObjectName(QString::fromUtf8("pk_tables"));
        gridLayout_5 = new QGridLayout(pk_tables);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pk_content_tab->addTab(pk_tables, QString());
        pk_plots = new QWidget();
        pk_plots->setObjectName(QString::fromUtf8("pk_plots"));
        gridLayout_4 = new QGridLayout(pk_plots);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pk_content_tab->addTab(pk_plots, QString());
        pk_proteins = new QWidget();
        pk_proteins->setObjectName(QString::fromUtf8("pk_proteins"));
        gridLayout_6 = new QGridLayout(pk_proteins);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pk_content_tab->addTab(pk_proteins, QString());
        pk_groups = new QWidget();
        pk_groups->setObjectName(QString::fromUtf8("pk_groups"));
        gridLayout_7 = new QGridLayout(pk_groups);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pk_content_tab->addTab(pk_groups, QString());
        pk_distance = new QWidget();
        pk_distance->setObjectName(QString::fromUtf8("pk_distance"));
        gridLayout_8 = new QGridLayout(pk_distance);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pk_content_tab->addTab(pk_distance, QString());
        pk_informations = new QWidget();
        pk_informations->setObjectName(QString::fromUtf8("pk_informations"));
        pk_informations->setEnabled(false);
        gridLayout_3 = new QGridLayout(pk_informations);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pk_content_tab->addTab(pk_informations, QString());

        gridLayout_2->addWidget(pk_content_tab, 0, 0, 1, 1);


        retranslateUi(pk_content);

        pk_content_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(pk_content);
    } // setupUi

    void retranslateUi(QWidget *pk_content)
    {
        pk_content->setWindowTitle(QApplication::translate("pk_content", "Form", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_tables_plots), QApplication::translate("pk_content", "Tables / Plots", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_tables), QApplication::translate("pk_content", "Tables", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_plots), QApplication::translate("pk_content", "Plots", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_proteins), QApplication::translate("pk_content", "Proteins", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_groups), QApplication::translate("pk_content", "Groups", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_distance), QApplication::translate("pk_content", "Distance", 0, QApplication::UnicodeUTF8));
        pk_content_tab->setTabText(pk_content_tab->indexOf(pk_informations), QApplication::translate("pk_content", "Informations", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pk_content: public Ui_pk_content {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEAKLIST_CONTENT_H
