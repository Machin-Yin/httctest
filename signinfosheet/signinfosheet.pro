#-------------------------------------------------
#
# Project created by QtCreator 2018-12-20T10:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = signinfosheet
TEMPLATE = app

INCLUDEPATH += ./qjsonlib
LIBS += -L./qjsonlib -lqjson

SOURCES += main.cpp\
    addcompanydialog.cpp \
    selectpkgdialog.cpp \
    addpackagedialog.cpp \
    signinfotabledialog.cpp \
    companydetaildialog.cpp

HEADERS  += addcompanydialog.h \
    selectpkgdialog.h \
    addpackagedialog.h \
    signinfotabledialog.h \
    companydetaildialog.h

FORMS    += \
    addcompanydialog.ui \
    selectpkgdialog.ui \
    addpackagedialog.ui \
    signinfotabledialog.ui \
    companydetaildialog.ui
