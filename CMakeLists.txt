CMAKE_MINIMUM_REQUIRED (VERSION 2.9)

project(TCP_METRIC_SERVER)

if(WIN32)
    message(STATUS "System detected as Windows. Trying to determine compiler path...")
    set(BOOST_INCLUDEDIR "")

endif()

find_package(Boost REQUIRED COMPONENTS 
    system
)

IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)


add_executable(TCP_METRIC_SERVER main.cpp
Server.cpp
Server.h
Session.cpp
Session.h
Storage.h
Utility.cpp
Utility.h
Logger.h
)