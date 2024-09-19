#-------------------------------------------------
#
# Project created by QtCreator 2024-09-17T11:53:10
#
#-------------------------------------------------

QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gestion_note
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ajoutetudiant.cpp \
    modifieretudiant.cpp \
    menu.cpp \
    matiere.cpp \
    notematiere.cpp \
    modifiernote.cpp

HEADERS  += mainwindow.h \
    ajoutetudiant.h \
    modifieretudiant.h \
    menu.h \
    matiere.h \
    notematiere.h \
    modifiernote.h

FORMS    += mainwindow.ui \
    ajoutetudiant.ui \
    modifieretudiant.ui \
    menu.ui \
    matiere.ui \
    notematiere.ui \
    modifiernote.ui

win32: LIBS += -L$$PWD/../../Desktop/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../Desktop
DEPENDPATH += $$PWD/../../Desktop

win32: LIBS += -L$$PWD/../../Desktop/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../Desktop
DEPENDPATH += $$PWD/../../Desktop
