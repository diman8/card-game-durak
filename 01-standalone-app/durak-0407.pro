TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Card.cpp \
    Deck.cpp \
    Turn.cpp \
    Pair.cpp \
    Player.cpp

HEADERS += \
    Card.h \
    Deck.h \
    Turn.h \
    Pair.h \
    Player.h
