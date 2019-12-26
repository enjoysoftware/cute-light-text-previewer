QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET=text-previewer
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    main.cpp \
    viewer_mainwin.cpp

HEADERS += \
    aboutdialog.h \
    viewer_mainwin.h

FORMS += \
    aboutdialog.ui \
    viewer_mainwin.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    translations.qrc
TRANSLATIONS = \
    translations/text-previewer_ja_JP.ts
#LUPDATE = $$[QT_INSTALL_BINS]/lupdate -locations absolute -no-obsolete
LRELEASE = $$QMAKE_LRELEASE
isEmpty(LRELEASE):LRELEASE = $$[QT_INSTALL_BINS]/lrelease
#lupdate.commands = $$LUPDATE  -ts $$TRANSLATIONS
#QMAKE_EXTRA_TARGETS += lupdate
updateqm.input = TRANSLATIONS
updateqm.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
isEmpty(vcproj):updateqm.variable_out = PRE_TARGETDEPS
updateqm.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
updateqm.name = LRELEASE ${QMAKE_FILE_IN}
updateqm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm
