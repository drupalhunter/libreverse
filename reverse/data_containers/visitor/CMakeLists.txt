project(data_visitor)

set ( DATA_VISITOR_SOURCES
  Control_Flow_Graph_Graphviz_Visitor.cpp )

set ( DATA_VISITOR_HEADERS
  Control_Flow_Graph_Graphviz_Visitor.h )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( data_visitor_static ${DATA_VISITOR_SOURCES} ${DATA_VISITOR_HEADERS} )
add_library ( data_visitor SHARED ${DATA_VISITOR_SOURCES} ${DATA_VISITOR_HEADERS} )
set_target_properties ( data_visitor_static PROPERTIES OUTPUT_NAME data_visitor )

install ( TARGETS data_visitor LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS data_visitor_static ARCHIVE DESTINATION lib COMPONENT libraries )
