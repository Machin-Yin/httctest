#-------------------------------------------------
#
# Project created by QtCreator 2019-01-11T09:06:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = showpkginfo
TEMPLATE = app


SOURCES += main.cpp\
    shownonadapterdialog.cpp \
    adapterfactorydialog.cpp \
    devicefactorydialog.cpp

HEADERS  += \
    shownonadapterdialog.h \
    adapterfactorydialog.h \
    devicefactorydialog.h

FORMS    += \
    shownonadapterdialog.ui \
    adapterfactorydialog.ui \
    devicefactorydialog.ui
