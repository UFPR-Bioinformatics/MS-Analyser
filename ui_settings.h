/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Tue Apr 23 10:19:52 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QWidget *formLayoutWidget_4;
    QFormLayout *settingsPeakLayout_4;
    QLabel *presenceLabel_4;
    QSpinBox *presenceSpinBox_4;
    QLabel *toleranceLabel_4;
    QSpinBox *toleranceSpinBox;
    QLabel *toleranceLabel_5;
    QDoubleSpinBox *cutoffSpinBox;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QVBoxLayout *set_clust_layout;
    QRadioButton *clust_avg;
    QRadioButton *clust_max;
    QRadioButton *clust_sing;
    QGroupBox *groupBox_3;
    QWidget *formLayoutWidget_6;
    QVBoxLayout *set_dist_layout;
    QRadioButton *dist_eucl;
    QRadioButton *dist_city;
    QRadioButton *dist_correl;
    QRadioButton *dist_abs;
    QRadioButton *dist_uncent;
    QRadioButton *dist_abs_uncent;
    QRadioButton *dist_spear;
    QRadioButton *dist_kend;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(431, 259);
        Form->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(Form);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayoutWidget_4 = new QWidget(groupBox_2);
        formLayoutWidget_4->setObjectName(QString::fromUtf8("formLayoutWidget_4"));
        formLayoutWidget_4->setGeometry(QRect(40, 17, 141, 98));
        settingsPeakLayout_4 = new QFormLayout(formLayoutWidget_4);
        settingsPeakLayout_4->setObjectName(QString::fromUtf8("settingsPeakLayout_4"));
        settingsPeakLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        settingsPeakLayout_4->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        settingsPeakLayout_4->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        settingsPeakLayout_4->setHorizontalSpacing(20);
        settingsPeakLayout_4->setContentsMargins(0, 0, 0, 0);
        presenceLabel_4 = new QLabel(formLayoutWidget_4);
        presenceLabel_4->setObjectName(QString::fromUtf8("presenceLabel_4"));
        presenceLabel_4->setEnabled(false);

        settingsPeakLayout_4->setWidget(0, QFormLayout::LabelRole, presenceLabel_4);

        presenceSpinBox_4 = new QSpinBox(formLayoutWidget_4);
        presenceSpinBox_4->setObjectName(QString::fromUtf8("presenceSpinBox_4"));
        presenceSpinBox_4->setEnabled(false);
        presenceSpinBox_4->setReadOnly(true);
        presenceSpinBox_4->setSingleStep(5);
        presenceSpinBox_4->setValue(60);

        settingsPeakLayout_4->setWidget(0, QFormLayout::FieldRole, presenceSpinBox_4);

        toleranceLabel_4 = new QLabel(formLayoutWidget_4);
        toleranceLabel_4->setObjectName(QString::fromUtf8("toleranceLabel_4"));

        settingsPeakLayout_4->setWidget(1, QFormLayout::LabelRole, toleranceLabel_4);

        toleranceSpinBox = new QSpinBox(formLayoutWidget_4);
        toleranceSpinBox->setObjectName(QString::fromUtf8("toleranceSpinBox"));
        toleranceSpinBox->setValue(2);

        settingsPeakLayout_4->setWidget(1, QFormLayout::FieldRole, toleranceSpinBox);

        toleranceLabel_5 = new QLabel(formLayoutWidget_4);
        toleranceLabel_5->setObjectName(QString::fromUtf8("toleranceLabel_5"));

        settingsPeakLayout_4->setWidget(2, QFormLayout::LabelRole, toleranceLabel_5);

        cutoffSpinBox = new QDoubleSpinBox(formLayoutWidget_4);
        cutoffSpinBox->setObjectName(QString::fromUtf8("cutoffSpinBox"));
        cutoffSpinBox->setDecimals(1);
        cutoffSpinBox->setMaximum(1);
        cutoffSpinBox->setSingleStep(0.1);
        cutoffSpinBox->setValue(0.7);

        settingsPeakLayout_4->setWidget(2, QFormLayout::FieldRole, cutoffSpinBox);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(40, 21, 88, 77));
        set_clust_layout = new QVBoxLayout(formLayoutWidget);
        set_clust_layout->setObjectName(QString::fromUtf8("set_clust_layout"));
        set_clust_layout->setContentsMargins(0, 0, 0, 0);
        clust_avg = new QRadioButton(formLayoutWidget);
        clust_avg->setObjectName(QString::fromUtf8("clust_avg"));
        clust_avg->setChecked(true);

        set_clust_layout->addWidget(clust_avg);

        clust_max = new QRadioButton(formLayoutWidget);
        clust_max->setObjectName(QString::fromUtf8("clust_max"));

        set_clust_layout->addWidget(clust_max);

        clust_sing = new QRadioButton(formLayoutWidget);
        clust_sing->setObjectName(QString::fromUtf8("clust_sing"));

        set_clust_layout->addWidget(clust_sing);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(Form);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayoutWidget_6 = new QWidget(groupBox_3);
        formLayoutWidget_6->setObjectName(QString::fromUtf8("formLayoutWidget_6"));
        formLayoutWidget_6->setGeometry(QRect(20, 20, 176, 212));
        set_dist_layout = new QVBoxLayout(formLayoutWidget_6);
        set_dist_layout->setObjectName(QString::fromUtf8("set_dist_layout"));
        set_dist_layout->setContentsMargins(0, 0, 0, 0);
        dist_eucl = new QRadioButton(formLayoutWidget_6);
        dist_eucl->setObjectName(QString::fromUtf8("dist_eucl"));
        dist_eucl->setChecked(true);

        set_dist_layout->addWidget(dist_eucl);

        dist_city = new QRadioButton(formLayoutWidget_6);
        dist_city->setObjectName(QString::fromUtf8("dist_city"));

        set_dist_layout->addWidget(dist_city);

        dist_correl = new QRadioButton(formLayoutWidget_6);
        dist_correl->setObjectName(QString::fromUtf8("dist_correl"));

        set_dist_layout->addWidget(dist_correl);

        dist_abs = new QRadioButton(formLayoutWidget_6);
        dist_abs->setObjectName(QString::fromUtf8("dist_abs"));

        set_dist_layout->addWidget(dist_abs);

        dist_uncent = new QRadioButton(formLayoutWidget_6);
        dist_uncent->setObjectName(QString::fromUtf8("dist_uncent"));

        set_dist_layout->addWidget(dist_uncent);

        dist_abs_uncent = new QRadioButton(formLayoutWidget_6);
        dist_abs_uncent->setObjectName(QString::fromUtf8("dist_abs_uncent"));

        set_dist_layout->addWidget(dist_abs_uncent);

        dist_spear = new QRadioButton(formLayoutWidget_6);
        dist_spear->setObjectName(QString::fromUtf8("dist_spear"));

        set_dist_layout->addWidget(dist_spear);

        dist_kend = new QRadioButton(formLayoutWidget_6);
        dist_kend->setObjectName(QString::fromUtf8("dist_kend"));

        set_dist_layout->addWidget(dist_kend);


        gridLayout->addWidget(groupBox_3, 0, 1, 2, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Form", "Peaks", 0, QApplication::UnicodeUTF8));
        presenceLabel_4->setText(QApplication::translate("Form", "Presence", 0, QApplication::UnicodeUTF8));
        presenceSpinBox_4->setSuffix(QApplication::translate("Form", " %", 0, QApplication::UnicodeUTF8));
        toleranceLabel_4->setText(QApplication::translate("Form", "Tolerance", 0, QApplication::UnicodeUTF8));
        toleranceSpinBox->setSuffix(QApplication::translate("Form", " Da", 0, QApplication::UnicodeUTF8));
        toleranceLabel_5->setText(QApplication::translate("Form", "Cutoff", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Form", "Cluster", 0, QApplication::UnicodeUTF8));
        clust_avg->setText(QApplication::translate("Form", "Average", 0, QApplication::UnicodeUTF8));
        clust_avg->setShortcut(QApplication::translate("Form", "A", 0, QApplication::UnicodeUTF8));
        clust_max->setText(QApplication::translate("Form", "Maximum", 0, QApplication::UnicodeUTF8));
        clust_max->setShortcut(QApplication::translate("Form", "M", 0, QApplication::UnicodeUTF8));
        clust_sing->setText(QApplication::translate("Form", "Single", 0, QApplication::UnicodeUTF8));
        clust_sing->setShortcut(QApplication::translate("Form", "S", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("Form", "Distance", 0, QApplication::UnicodeUTF8));
        dist_eucl->setText(QApplication::translate("Form", "Euclidian", 0, QApplication::UnicodeUTF8));
        dist_eucl->setShortcut(QApplication::translate("Form", "E", 0, QApplication::UnicodeUTF8));
        dist_city->setText(QApplication::translate("Form", "City-block", 0, QApplication::UnicodeUTF8));
        dist_city->setShortcut(QApplication::translate("Form", "B", 0, QApplication::UnicodeUTF8));
        dist_correl->setText(QApplication::translate("Form", "Correlation", 0, QApplication::UnicodeUTF8));
        dist_correl->setShortcut(QApplication::translate("Form", "C", 0, QApplication::UnicodeUTF8));
        dist_abs->setText(QApplication::translate("Form", "Absolute Correlation", "a", QApplication::UnicodeUTF8));
        dist_uncent->setText(QApplication::translate("Form", "Uncentered Correlation", "u", QApplication::UnicodeUTF8));
        dist_abs_uncent->setText(QApplication::translate("Form", "Abs.  Unc. Correlation", "x", QApplication::UnicodeUTF8));
        dist_spear->setText(QApplication::translate("Form", "Spearman", "s", QApplication::UnicodeUTF8));
        dist_kend->setText(QApplication::translate("Form", "Kendall", "k", QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
