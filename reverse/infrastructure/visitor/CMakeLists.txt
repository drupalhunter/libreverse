project(infrastructure_visitor)

set ( INFRASTRUCTURE_VISITOR_SOURCES
  graph_visitor.cpp
  graphviz_visitor.cpp )

set ( INFRASTRUCTURE_VISITOR_HEADERS
  graph_visitor.hpp
  graphviz_visitor.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( infrastructure_visitor_static ${INFRASTRUCTURE_VISITOR_SOURCES} ${INFRASTRUCTURE_VISITOR_HEADERS} )
add_library ( infrastructure_visitor SHARED ${INFRASTRUCTURE_VISITOR_SOURCES} ${INFRASTRUCTURE_VISITOR_HEADERS} )
set_target_properties ( infrastructure_visitor_static PROPERTIES OUTPUT_NAME infrastructure_visitor )

install ( TARGETS infrastructure_visitor LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS infrastructure_visitor_static ARCHIVE DESTINATION lib COMPONENT libraries )

