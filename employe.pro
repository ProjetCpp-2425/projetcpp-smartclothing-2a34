QT       += core gui
QT       += core gui sql
QT += core-private
QT += charts
QT += network
QT += core gui serialport
QT += axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/QXlsx/QXlsx/header
# Include the directory where qrcodegen.hpp is located

# Header Files
HEADERS += \
    $$PWD/QXlsx/QXlsx/header/xlsxabstractooxmlfile.h \
    $$PWD/QXlsx/QXlsx/header/xlsxabstractooxmlfile_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxabstractsheet.h \
    $$PWD/QXlsx/QXlsx/header/xlsxabstractsheet_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcell.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcell_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcellformula.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcellformula_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcelllocation.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcellrange.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcellreference.h \
    $$PWD/QXlsx/QXlsx/header/xlsxchart.h \
    $$PWD/QXlsx/QXlsx/header/xlsxchart_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxchartsheet.h \
    $$PWD/QXlsx/QXlsx/header/xlsxchartsheet_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcolor_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxconditionalformatting.h \
    $$PWD/QXlsx/QXlsx/header/xlsxconditionalformatting_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxcontenttypes_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdatavalidation.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdatavalidation_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdatetype.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdocpropsapp_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdocpropscore_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdocument.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdocument_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdrawing_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxdrawinganchor_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxformat.h \
    $$PWD/QXlsx/QXlsx/header/xlsxformat_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxglobal.h \
    $$PWD/QXlsx/QXlsx/header/xlsxmediafile_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxnumformatparser_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxrelationships_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxrichstring.h \
    $$PWD/QXlsx/QXlsx/header/xlsxrichstring_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxsharedstrings_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxsimpleooxmlfile_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxstyles_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxtheme_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxutility_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxworkbook.h \
    $$PWD/QXlsx/QXlsx/header/xlsxworkbook_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxworksheet.h \
    $$PWD/QXlsx/QXlsx/header/xlsxworksheet_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxzipreader_p.h \
    $$PWD/QXlsx/QXlsx/header/xlsxzipwriter_p.h \
    Article.h \
    arduinors.h \
    articlenotifier.h \
    client.h \
    notification.h \
    transaction.h \
    vocale.h

# Source Files
SOURCES += \
    $$PWD/QXlsx/QXlsx/source/xlsxabstractooxmlfile.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxabstractsheet.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcell.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcellformula.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcelllocation.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcellrange.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcellreference.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxchart.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxchartsheet.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcolor.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxconditionalformatting.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxcontenttypes.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdatavalidation.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdocpropsapp.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdocpropscore.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdocument.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdrawing.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxdrawinganchor.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxformat.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxmediafile.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxnumformatparser.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxrelationships.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxrichstring.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxsharedstrings.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxsimpleooxmlfile.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxstyles.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxtheme.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxutility.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxworkbook.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxworksheet.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxzipreader.cpp \
    $$PWD/QXlsx/QXlsx/source/xlsxzipwriter.cpp \
    Article.cpp \
    arduinors.cpp \
    articlenotifier.cpp \
    client.cpp \
    transaction.cpp \
    vocale.cpp


SOURCES += \
    connection.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connection.h \
    employe.h \
    mainwindow.h

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
