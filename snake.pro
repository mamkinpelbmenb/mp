TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        difficultyselection.cpp \
        game.cpp \
        main.cpp \
        mainmenu.cpp

HEADERS += \
    difficultyselection.h \
    game.h \
    mainmenu.h

QT += widgets quick
