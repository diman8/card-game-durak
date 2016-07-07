TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Card.cpp \
    Deck.cpp \
    Pair.cpp \
    Player.cpp \
    Table.cpp

HEADERS += \
    Card.h \
    Deck.h \
    Pair.h \
    Player.h \
    Table.h
