cmake_minimum_required(VERSION 2.8.12.1)
project(libreverse)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")

include(CheckIncludeFiles)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options )
FIND_PACKAGE(ICU REQUIRED)
FIND_PACKAGE(EXPAT)

add_subdirectory(reverse)
add_subdirectory(testing)
add_subdirectory(tools)

configure_file(${CMAKE_SOURCE_DIR}/reverse/include/config.h.in ${CMAKE_BINARY_DIR}/reverse/include/config.h)

set ( CPACK_RPM_PACKAGE_SUMMARY "${CPACK_PACKAGE_DESCRIPTION}" )
set ( CPACK_RPM_PACKAGE_NAME "${PROJECT_NAME}" )
set ( CPACK_RPM_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION} )
set ( CPACK_RPM_PACKAGE_GROUP "Development/Libraries" )
set ( CPACK_RPM_PACKAGE_VENDOR "Stephen Torri<storri@torri.org>" )
set ( CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION} )

set ( CPACK_PACKAGE_DESCRIPTION "Library for reverse engineering binary programs" )
set ( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README" )
set ( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" )
set ( CPACK_PACKAGE_VERSION_MAJOR "1" )
set ( CPACK_PACKAGE_VERSION_MINOR "0" )
set ( CPACK_PACKAGE_VERSION_PATCH "0" )

set ( CPACK_RPM_PACKAGE_LICENSE "GPL" )


include(CPack)

