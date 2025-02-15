cmake_minimum_required(VERSION 3.16)

project(BrowserGame LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND git rev-list --count HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_COUNT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-DMAJOR="1")
add_definitions(-DMINOR="3")
add_definitions(-DPATCH="${GIT_COMMIT_COUNT}")
add_definitions(-DGIT_INFO="${GIT_BRANCH}/${GIT_HASH}")
string(TIMESTAMP CURRENT_TIME "%Y/%m/%d %H:%M:%S")
add_definitions(-DBUILD_TIME="${CURRENT_TIME}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core WebSockets Network Sql Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebSockets Network Sql Quick)



include_directories( ${CMAKE_SOURCE_DIR} )


set(CMAKE_PREFIX_PATH "C:/mongocxx/mongo-cxx-mingw-13.1.0-install/lib/cmake/bsoncxx-3.10.2" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "C:/mongocxx/mongo-cxx-mingw-13.1.0-install/lib/cmake/mongocxx-3.10.2" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "C:/mongocxx/mongo-cxx-mingw-13.1.0-install/lib/cmake/mongoc-1.0" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "C:/mongocxx/mongo-cxx-mingw-13.1.0-install/lib/cmake/bson-1.0" ${CMAKE_PREFIX_PATH})

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

find_package( Wt REQUIRED )


add_library(MongoCore
    MongoCore/item.h
    MongoCore/item.cpp
    MongoCore/db.h
    MongoCore/db.cpp
    MongoCore/listitem.h
    MongoCore/listitem.cpp
    MongoCore/mongoheaders.h
    MongoCore/MongoCore.h MongoCore/MongoCore.cpp
    MongoCore/ListItemNoDB.h
)

target_link_libraries(MongoCore PUBLIC mongo::mongocxx_shared Qt${QT_VERSION_MAJOR}::Core )


add_executable(BrowserGame main.cpp)
target_link_libraries(BrowserGame PUBLIC wt wthttp Wt::Dbo )


include(GNUInstallDirs)
install(TARGETS BrowserGame
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
