function(FIND_LibKML)

    find_package(Boost REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    find_library(MINIZIP_LIB MINIZIP)
    find_package(URIPARSER QUIET)

    find_package(LibKML QUIET)
    if(LibKML)
        include_directories(${LibKML_INCLUDE_DIRS})
        link_directories(${LibKML_LIBRARY_DIRS})
    endif()

    set(LibKML_LIBS kmlconvenience kmlengine kmldom kmlbase uriparser ${MINIZIP_LIBRARY} PARENT_SCOPE)

endfunction(FIND_LibKML)

