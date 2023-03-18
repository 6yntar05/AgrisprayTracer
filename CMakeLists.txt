cmake_minimum_required(VERSION 3.10)
project(            AgrisprayTracer
    DESCRIPTION     "Trace .kml poly to flight-plan waypoints for agricultural drone"
    HOMEPAGE_URL    "https://github.com/6yntar05/FastBleed"
    LANGUAGES       CXX
)
include("./cmake/CompilerProperties.cmake")
include("./cmake/FindLibKML.cmake")

### OPTIONS ###
option(USE_Compiler_PROPERTIES "Use cringe compiler propertires" ON)
if(${USE_Compiler_PROPERTIES})
    SetCompilerProperties()
endif()

### COMPILE PROPERTIES ###
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)   # NOTE: conflict with gui.cpp 
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### LibKML ###
FIND_LibKML() # Write -l* to LibKML_LIBS for target_link_libraries()
# Requies Boost

### Finding QT ###
message         (">> Finding Qt")
find_package    (QT NAMES Qt5 Qt6 QUIET COMPONENTS Widgets)
find_package    (Qt${QT_VERSION_MAJOR} QUIET COMPONENTS Widgets)

### SRC FILES ###
file(GLOB_RECURSE SRCFILES "./src/*.cpp")
file(GLOB_RECURSE SRCFILES ${SRCFILES} "./src/ui/*")
include_directories(AFTER SYSTEM ./src)

if(QT_FOUND)
    if(QT_VERSION_MAJOR GREATER_EQUAL 6)
        qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SRCFILES})
        qt_finalize_executable(${PROJECT_NAME})
    else()
        add_executable(${PROJECT_NAME} ${SRCFILES})
    endif()
    target_link_libraries   (${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets ${LibKML_LIBS})
else()
    message(FATAL_ERROR "QT Not found! Install QT and add it to PATH if you use Windows")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ./src)
