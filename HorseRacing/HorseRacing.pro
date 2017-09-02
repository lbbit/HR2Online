#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T11:12:45
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += multimedia
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HorseRacing
TEMPLATE = app
RC_FILE = icon.rc

SOURCES += main.cpp\
    start.cpp \
    login.cpp \
    register.cpp \
    menu.cpp \
    gameselect.cpp \
    rank.cpp \
    rule.cpp \
    management.cpp \
    gamestart.cpp \
    mainwidget.cpp \
    quitswitch.cpp \
    changename.cpp \
    changecode.cpp \
    rankc.cpp \
    user.cpp \
    timeblock.cpp \
    globalvariable.cpp \
    gamestop.cpp \
    gamecomplete.cpp \
    adminwindow.cpp \
    gameover.cpp \
    aboutdialog.cpp \
    notice.cpp \
    log.cpp \
    dbconnection.cpp

HEADERS  += \
    start.h \
    login.h \
    register.h \
    menu.h \
    gameselect.h \
    rank.h \
    rule.h \
    management.h \
    gamestart.h \
    mainwidget.h \
    quitswitch.h \
    changename.h \
    changecode.h \
    rankc.h \
    user.h \
    timeblock.h \
    globalvariable.h \
    gamestop.h \
    gamecomplete.h \
    adminwindow.h \
    gameover.h \
    aboutdialog.h \
    notice.h \
    log.h \
    dbconnection.h

RESOURCES += \
    index.qrc \
    music.qrc

FORMS += \
    start.ui \
    login.ui \
    register.ui \
    menu.ui \
    gameselect.ui \
    rank.ui \
    rule.ui \
    management.ui \
    gamestart.ui \
    quitswitch.ui \
    changename.ui \
    changecode.ui \
    gamestop.ui \
    gamecomplete.ui \
    adminwindow.ui \
    gameover.ui \
    aboutdialog.ui \
    notice.ui

DISTFILES += \
    icon.rc
