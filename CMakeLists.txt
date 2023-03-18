cmake_minimum_required(VERSION 3.10)
project(            AgrisprayTracer
    DESCRIPTION     "Trace .kml poly to flight-plan waypoints for agricultural drone"
    HOMEPAGE_URL    "https://github.com/6yntar05/FastBleed"
    LANGUAGES       CXX
)

### COMPILE PROPERTIES ###
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)   # NOTE: conflict with gui.cpp 
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -fcolor-diagnostics)
endif ()
add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -O3)

### SUBMODULES ###
function (submodules_update)
    find_package(Git QUIET)
    if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if (GIT_SUBMODULE)
            message (">> Update submodules")
            execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT
            )
            if (NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif ()
        endif ()
    endif ()
endfunction ()
submodules_update()

### Finding QT ###
message         (">> Finding Qt")
find_package    (QT NAMES Qt5 Qt6 QUIET COMPONENTS Widgets)
find_package    (Qt${QT_VERSION_MAJOR} QUIET COMPONENTS Widgets)

### Boost ###
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

### LibKML ###
#find_package (LibKML REQUIRED)
include_directories(${LibKML_INCLUDE_DIRS})
link_directories(${LibKML_LIBRARY_DIRS})
message("${LibKML_LIBRARY_DIRS}")
find_package(ZLIB REQUIRED)
find_library(MINIZIP_LIB MINIZIP)
find_package(URIPARSER REQUIRED)

### SRC FILES ###
file(GLOB_RECURSE SRCFILES "./src/*.cpp")
file(GLOB_RECURSE SRCFILES ${SRCFILES} "./src/ui/*")

include_directories(AFTER SYSTEM ./src)

if (QT_FOUND)
    if (QT_VERSION_MAJOR GREATER_EQUAL 6)
        qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SRCFILES})
        qt_finalize_executable(${PROJECT_NAME})
    else ()
        add_executable(${PROJECT_NAME} ${SRCFILES})
    endif ()
    target_link_libraries   (${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets kmlconvenience kmlengine kmldom kmlbase uriparser ${MINIZIP_LIBRARY})
else ()
    message                 (FATAL_ERROR "QT Not found! Install QT and add it to PATH")
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ./src)
