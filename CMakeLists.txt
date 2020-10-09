cmake_minimum_required(VERSION 2.8)
project(pathplanning)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2")

#set(CMAKE_CXX_STANDARD_LIBRARIES -lpsapi)

set(SOURCE_FILES
        tinyxml2.cpp
        xmllogger.cpp
        isearch.cpp
        mission.cpp
        map.cpp
        dijkstra.cpp
        config.cpp
        astar.cpp
        main.cpp
        environmentoptions.cpp
        Coords.cpp
        OpenList.cpp
        theta.cpp
        usages.cpp
        CloseList.cpp
        jps.cpp
        )

set(HEADER_FILES
        tinyxml2.h
        node.h
        gl_const.h
        xmllogger.h
        isearch.h
        mission.h
        map.h
        ilogger.h
        dijkstra.h
        config.h
        astar.h
        searchresult.h
        environmentoptions.h
        Coords.h
        OpenList.h
        theta.h
        usages.h
        CloseList.h
        jps.h
        )

add_executable(pathplanning ${SOURCE_FILES} ${HEADER_FILES})
