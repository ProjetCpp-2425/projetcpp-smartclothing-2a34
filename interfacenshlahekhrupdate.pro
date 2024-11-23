QT       += core gui widgets sql charts quick qml 3dcore 3dextras 3drender
QT += core
QT += widgets core gui
QT += axcontainer
#QT += xlsx
QT += charts



DEFINES += QTXLSX_EXPORTS

# Dossier de destination pour les fichiers compilés
DESTDIR = $$PWD/debug

# Activer les flags nécessaires
QMAKE_CXXFLAGS += -fPIC

# Post-build command
post-build.commands = echo "Build Finished" > $$OUT_PWD/build.log
QMAKE_POST_LINK = $$post-build.commands

# Configurer le standard C++ utilisé
CONFIG += c++17

# Nom et type de projet
TARGET = interfacenshlahekhrupdate
TEMPLATE = app



# Vos fichiers sources
SOURCES += \
    Article.cpp \
    articlenotifier.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp

# Vos fichiers d'en-tête
HEADERS += \
    Article.h \
    articlenotifier.h \
    connection.h \
    mainwindow.h \
    notification.h

# Vos fichiers UI
FORMS += \
    mainwindow.ui

# Vos ressources
RESOURCES += \
    PHOTO.qrc \
    icon.qrc \
    image.qrc \
    notification.qrc

# Règles par défaut pour le déploiement
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
