#-------------------------------------------------
#
# Project created by QtCreator 2011-02-26T12:08:02
#
#-------------------------------------------------

TARGET = pathplanning
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -O2 -Wall -Wextra

win32 {
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}

SOURCES += \
    tinyxml2.cpp \
    xmllogger.cpp \
    isearch.cpp \
    mission.cpp \
    map.cpp \
    dijkstra.cpp \
    config.cpp \
    astar.cpp \
    main.cpp \
    environmentoptions.cpp \
    Coords.cpp \
    OpenList.cpp \
    CloseList.cpp \
    theta.cpp


HEADERS += \
    tinyxml2.h \
    node.h \
    gl_const.h \
    xmllogger.h \
    isearch.h \
    mission.h \
    map.h \
    ilogger.h \
    dijkstra.h \
    config.h \
    astar.h \
    searchresult.h \
    environmentoptions.h \
    Coords.h \
    OpenList.h \
    CloseList.h \
    theta.h
