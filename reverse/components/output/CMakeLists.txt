project(output_components)

set ( OUTPUT_COMPONENTS_SOURCES
    meta_writer.cpp )

set ( OUTPUT_COMPONENTS_HEADERS
  meta_writer.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( output_components_static STATIC ${OUTPUT_COMPONENTS_SOURCES} ${OUTPUT_COMPONENTS_HEADERS} )
add_library ( output_components SHARED ${OUTPUT_COMPONENTS_SOURCES} ${OUTPUT_COMPONENTS_HEADERS} )
set_target_properties ( output_components_static PROPERTIES OUTPUT_NAME output_components )

install ( TARGETS output_components LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS output_components_static ARCHIVE DESTINATION lib COMPONENT libraries )
