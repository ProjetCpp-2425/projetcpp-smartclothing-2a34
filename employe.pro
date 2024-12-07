
QT += core gui sql charts multimedia multimediawidgets printsupport widgets axcontainer network serialport
QT += core-private




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INCLUDEPATH += $$PWD/QXlsx/QXlsx/header

SOURCES += \
    connection.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp\
    Article.cpp \
    arduinors.cpp \
    articlenotifier.cpp \
    transaction.cpp \
    vocale.cpp

HEADERS += \
    connection.h \
    employe.h \
    mainwindow.h\
    Article.h \
    arduinors.h \
    articlenotifier.h \
    notification.h \
    transaction.h \
    vocale.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    CHEMISES.qrc \
    Chemise.qrc \
    Enfant.qrc \
    PHOTO.qrc \
    ggggggggg.qrc \
    icon.qrc \
    image.qrc \
    images.qrc \
    notification.qrc \
    resources.qrc
