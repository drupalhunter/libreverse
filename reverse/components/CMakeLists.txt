project(reverse_components)

add_subdirectory(input)
add_subdirectory(output)

set ( COMPONENT_SOURCES
  component_factory.cpp
  null_component.cpp )

set ( COMPONENT_HEADERS
  component_factory.hpp 
  null_component.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} ${JSON_SPIRIT_INCLUDE_DIR} )

add_library ( components ${COMPONENT_SOURCES} ${COMPONENT_HEADERS} )
target_link_libraries ( components input_components output_components )
