QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_holder.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    two_spectrum_window.cpp

HEADERS += \
    data_holder.h \
    mainwindow.h \
    qcustomplot.h \
    two_spectrum_window.h

FORMS += \
    mainwindow.ui \
    two_spectrum_window.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
