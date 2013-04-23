/********************************************************************************
** Form generated from reading UI file 'peaklist_info.ui'
**
** Created: Tue Apr 23 10:19:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEAKLIST_INFO_H
#define UI_PEAKLIST_INFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ms_data
{
public:
    QGridLayout *gridLayout;
    QTabWidget *ms_data_tab;
    QWidget *tab_3;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lb_genero;
    QLineEdit *organismo_genero;
    QLabel *lb_especie;
    QLineEdit *organismo_especie;
    QLabel *lb_estirpe;
    QLineEdit *organismo_estirpe;
    QLabel *lb_ID;
    QLineEdit *organismo_ID;

    void setupUi(QWidget *ms_data)
    {
        if (ms_data->objectName().isEmpty())
            ms_data->setObjectName(QString::fromUtf8("ms_data"));
        ms_data->setWindowModality(Qt::ApplicationModal);
        ms_data->resize(610, 354);
        ms_data->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ms_data);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 5, 0, 0);
        ms_data_tab = new QTabWidget(ms_data);
        ms_data_tab->setObjectName(QString::fromUtf8("ms_data_tab"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        formLayoutWidget = new QWidget(tab_3);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(1, 0, 591, 321));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setHorizontalSpacing(7);
        formLayout->setVerticalSpacing(10);
        formLayout->setContentsMargins(10, 10, 10, 0);
        lb_genero = new QLabel(formLayoutWidget);
        lb_genero->setObjectName(QString::fromUtf8("lb_genero"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lb_genero);

        organismo_genero = new QLineEdit(formLayoutWidget);
        organismo_genero->setObjectName(QString::fromUtf8("organismo_genero"));

        formLayout->setWidget(1, QFormLayout::FieldRole, organismo_genero);

        lb_especie = new QLabel(formLayoutWidget);
        lb_especie->setObjectName(QString::fromUtf8("lb_especie"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lb_especie);

        organismo_especie = new QLineEdit(formLayoutWidget);
        organismo_especie->setObjectName(QString::fromUtf8("organismo_especie"));

        formLayout->setWidget(2, QFormLayout::FieldRole, organismo_especie);

        lb_estirpe = new QLabel(formLayoutWidget);
        lb_estirpe->setObjectName(QString::fromUtf8("lb_estirpe"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lb_estirpe);

        organismo_estirpe = new QLineEdit(formLayoutWidget);
        organismo_estirpe->setObjectName(QString::fromUtf8("organismo_estirpe"));

        formLayout->setWidget(3, QFormLayout::FieldRole, organismo_estirpe);

        lb_ID = new QLabel(formLayoutWidget);
        lb_ID->setObjectName(QString::fromUtf8("lb_ID"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lb_ID);

        organismo_ID = new QLineEdit(formLayoutWidget);
        organismo_ID->setObjectName(QString::fromUtf8("organismo_ID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, organismo_ID);

        ms_data_tab->addTab(tab_3, QString());

        gridLayout->addWidget(ms_data_tab, 0, 0, 1, 1);


        retranslateUi(ms_data);

        ms_data_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ms_data);
    } // setupUi

    void retranslateUi(QWidget *ms_data)
    {
        ms_data->setWindowTitle(QApplication::translate("ms_data", "MS Info", 0, QApplication::UnicodeUTF8));
        lb_genero->setText(QApplication::translate("ms_data", "G\303\252nero", 0, QApplication::UnicodeUTF8));
        lb_especie->setText(QApplication::translate("ms_data", "Esp\303\251cie", 0, QApplication::UnicodeUTF8));
        lb_estirpe->setText(QApplication::translate("ms_data", "Estirpe", 0, QApplication::UnicodeUTF8));
        lb_ID->setText(QApplication::translate("ms_data", "ID", 0, QApplication::UnicodeUTF8));
        ms_data_tab->setTabText(ms_data_tab->indexOf(tab_3), QApplication::translate("ms_data", "Organismo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ms_data: public Ui_ms_data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEAKLIST_INFO_H
