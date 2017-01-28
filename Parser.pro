#-------------------------------------------------
#
# Project created by QtCreator 2017-01-14T16:32:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11

DESTDIR=bin #Target file directory
OBJECTS_DIR=generated_files #Intermediate object files directory
MOC_DIR=generated_files #Intermediate moc files directory

SOURCES += main.cpp\
        mainwindow.cpp \
    CYK.cpp \
    Grammar.cpp \
    Lexer.cpp \
    ll1parser.cpp \
    Node.cpp \
    ParseTree.cpp

HEADERS  += mainwindow.h \
    CYK.h \
    Grammar.h \
    Lexer.h \
    ll1parser.h \
    Node.h \
    ParseTree.h

FORMS    += mainwindow.ui
