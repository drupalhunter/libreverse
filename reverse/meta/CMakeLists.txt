project(meta)

set ( META_SOURCES
  meta_object.cpp )

set ( META_HEADERS
  meta_object.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( meta ${META_SOURCES} ${META_HEADERS} )

