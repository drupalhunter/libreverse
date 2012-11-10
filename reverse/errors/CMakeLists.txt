project(exceptions)

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

add_library ( exceptions_static ${EXCEPTIONS_SOURCES} ${EXCEPTIONS_HEADERS} )
add_library ( exceptions SHARED ${EXCEPTIONS_SOURCES} ${EXCEPTIONS_HEADERS} )
set_target_properties ( exceptions_static PROPERTIES OUTPUT_NAME exceptions )

install ( TARGETS exceptions LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS exceptions_static ARCHIVE DESTINATION lib COMPONENT libraries )
