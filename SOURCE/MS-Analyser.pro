include( $${PWD}/../Base/Base.pro )
include( $${PWD}/Plot/plot.pri )
#include( $${PWD}/Plot/plot.prf )

QT += xml
QT += sql

LIBS += -lyat -lgsl -lcblas -latlas -lm -lcgraph
#-IImageMagick `Magick++-config --cppflags --cxxflags --ldflags --libs`
#-L$${PWD}/SPECLUST/lib/Cgraph -lcgraph
#-L$${PWD}/SPECLUST/lib/libcluster.a

#CONFIG += qwt
CONFIG += uitools

message(----------------------------------------------------------------------)
message($${INCLUDEPATH})
message(----------------------------------------------------------------------)

DEPENDPATH += $${PWD}

INCLUDEPATH = $${PWD} \
    $${PWD}/Base \
    $${PWD}/MS-Analyser \
    $${PWD}/Plot \
    $${PWD}/UI \
    $${PWD}/SPECLUST/lib \
#    $${PWD}/SPECLUST/lib/Cgraph \
    $${PWD}/SPECLUST/tcd \
    $${PWD}/SPECLUST/pic \
    $${PWD}/QXT \
    $${INCLUDEPATH}

HEADERS += \
    MS-Analyser/msanalyser.h \
    MS-Analyser/peaklist.h \
    UI/tableview.h \
    Plot/plot.h \
    Plot/picker.h \
    Plot/complexnumber.h \
    Plot/histogram.h \
    UI/listwidget.h \
    UI/fancytabwidget.h \
    UI/stylehelper.h \
    UI/styledbar.h \
    UI/variantdelegate.h \
    MS-Analyser/modemanager.h \
    Base/database.h \
    SPECLUST/lib/Distance.h \
    SPECLUST/lib/DistancePearson.h \
    SPECLUST/lib/DistanceEuclid.h \
    SPECLUST/lib/DistanceLiberal.h \
    SPECLUST/lib/DistanceConservative.h \
    SPECLUST/lib/cluster/cluster.h \
#    SPECLUST/lib/Cgraph/cgraph.h
#    SPECLUST/tcd/TreeNode.h
    SPECLUST/tcd/DrawTree.h \
    SPECLUST/pic/Cluster.h \
    SPECLUST/pic/Peak.h \
    SPECLUST/pic/Spectrum.h \
    SPECLUST/pic/pic.h \
    QXT/qxtglobal.h \
    QXT/qxtnamespace.h \
    QXT/qxtspanslider_p.h \
    QXT/qxtspanslider.h \
    MS-Analyser/painter.h
#    MS-Analyser/cluster.h

SOURCES += \
    MS-Analyser/msanalyser.cpp \
    MS-Analyser/peaklist.cpp \
    Plot/plot.cpp \
    Plot/picker.cpp \
    Plot/histogram.cpp \
    UI/tableview.cpp \
    UI/listwidget.cpp \
    UI/fancytabwidget.cpp \
    UI/stylehelper.cpp \
    UI/styledbar.cpp \
    UI/variantdelegate.cpp \
    MS-Analyser/modemanager.cpp \
    Base/database.cpp \
    SPECLUST/lib/Distance.cc \
    SPECLUST/lib/DistancePearson.cc \
    SPECLUST/lib/DistanceEuclid.cc \
    SPECLUST/lib/DistanceLiberal.cc \
    SPECLUST/lib/DistanceConservative.cc \
    SPECLUST/lib/cluster/cluster.c \
    SPECLUST/tcd/DrawTree.cc \
#    SPECLUST/pic/pic.cc \
#    MS-Analyser/cluster.cpp
    SPECLUST/pic/Cluster.cc \
    SPECLUST/pic/Peak.cc \
    SPECLUST/pic/Spectrum.cc \
    SPECLUST/pic/pic.cc \
    QXT/qxtspanslider.cpp \
    MS-Analyser/painter.cpp

OTHER_FILES += \
    QSS/default.qss

RESOURCES += \
    ms-analyser.qrc

FORMS += \
    UI/settings.ui \
    UI/peaklist_content.ui \
    UI/peaklist_list.ui \
    UI/peaklist_info.ui













