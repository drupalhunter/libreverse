cmake_minimum_required(VERSION 2.8)
project(libreverse)

include(CheckIncludeFiles)

add_subdirectory(reverse)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost)
IF(Boost_FOUND)
  include_directories ( ${Boost_INCLUDE_DIRS} )
  list ( APPEND ADDITIONAL_LIBS ${Boost_LIBRARY_DIRS} )
  set ( HAVE_BOOST 1 )
ENDIF(Boost_FOUND)

FIND_PACKAGE(ICU)
IF(ICU_FOUND)
  include_directories(${ICU_INCLUDE_DIR})
  list ( APPEND ADDITIONAL_LIBS ${ICU_LIBRARIES} )
  set ( HAVE_ICU 1 )
ENDIF(ICU_FOUND)

FIND_PACKAGE(EXPAT)
IF(EXPAT_FOUND)
  include_directories(${EXPAT_INCLUDE_DIR})
  list ( APPEND ADDITIONAL_LIBS ${EXPAT_LIBRARIES} )
  set ( HAVE_EXPAT 1 )  
ENDIF(EXPAT_FOUND)

configure_file(${CMAKE_SOURCE_DIR}/reverse/include/config.h.in ${CMAKE_BINARY_DIR}/reverse/include/config.h)

set ( CPACK_PACKAGE_DESCRIPTION "Library for reverse engineering binary programs" )
set ( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README" )
set ( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" )
set ( CPACK_PACKAGE_VERSION_MAJOR "1" )
set ( CPACK_PACKAGE_VERSION_MINOR "0" )
set ( CPACK_PACKAGE_VERSION_PATCH "0" )

set ( CPACK_RPM_PACKAGE_SUMMARY "${CPACK_PACKAGE_DESCRIPTION}" )
set ( CPACK_RPM_PACKAGE_NAME "reverse-devel" )
set ( CPACK_RPM_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION} )
set ( CPACK_RPM_PACKAGE_LICENSE "GPL" )
set ( CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries" )
set ( CPACK_RPM_PACKAGE_VENDOR "Stephen Torri<storri@torri.org>" )
set ( CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION} )

include(CPack)

