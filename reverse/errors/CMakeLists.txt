project(reverse_errors)

set ( EXCEPTIONS_SOURCES
  api_exception.cpp
  cpu_exception.cpp
  component_exception.cpp
  configuration_exception.cpp
  data_source_exception.cpp
  file_reader_exception.cpp
  io_exception.cpp
  internal_exception.cpp
  meta_exception.cpp
  parsing_exception.cpp
  reverse_exception.cpp )

set ( EXCEPTIONS_HEADERS
  api_exception.hpp
  cpu_exception.hpp
  component_exception.hpp
  configuration_exception.hpp
  data_source_exception.hpp
  file_reader_exception.hpp
  io_exception.hpp
  internal_exception.hpp
  meta_exception.hpp
  parsing_exception.hpp
  reverse_exception.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( ${PROJECT_NAME} ${EXCEPTIONS_SOURCES} ${EXCEPTIONS_HEADERS} )

install ( TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT libraries )
