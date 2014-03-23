# - Try to find Libreverse
# Once done, this will define 
#
# LIBREVERSE_FOUND - system has Libreverse
# LIBREVERSE_INCLUDE_DIR - the Libreverse include directories
# LIBREVERSE_LIBRARIES - link these to use Libreverse

# Main include dir
find_path ( LIBREVERSE_INCLUDE_DIR
	  NAMES reverse.hpp 
	  PATH_SUFFIXES include/reverse
	  PATHS
	  /usr
	  /usr/local
)

# Look for the libraries
find_library ( LIBREVERSE_LIBRARY
	     NAMES reverse reverse_iofind_library
	     PATH_SUFFIXES lib
	     PATHS
	     /usr
	     /usr/local
)

set(LIBREVERSE_LIBRARIES ${LIBREVERSE_LIBRARY})


# handle the QUIETLY and REQUIRED arguments and set GIF_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBREVERSE  REQUIRED_VARS  LIBREVERSE_LIBRARIES  LIBREVERSE_INCLUDE_DIR)

mark_as_advanced(LIBREVERSE_INCLUDE_DIR LIBREVERSE_LIBRARIES)




