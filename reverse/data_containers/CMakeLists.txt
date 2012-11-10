project(data_containers)

set ( DATA_CONTAINERS_SOURCES
  basic_block.cpp
  control_flow_graph.cpp
  control_flow_graph_sequence.cpp
  data_types.cpp
  filename.cpp
  java_assembly_instruction.cpp
  memory_map.cpp )

set ( DATA_CONTAINERS_HEADERS
  basic_block.hpp
  control_flow_graph.hpp
  control_flow_graph_sequence.hpp
  data_types.hpp
  filename.hpp
  instruction.hpp
  java_assembly_instruction.hpp
  memory_map.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( data_containers_static ${DATA_CONTAINERS_SOURCES} ${DATA_CONTAINERS_HEADERS} )
add_library ( data_containers SHARED ${DATA_CONTAINERS_SOURCES} ${DATA_CONTAINERS_HEADERS} )
set_target_properties ( data_containers_static PROPERTIES OUTPUT_NAME data_containers )

install ( TARGETS data_containers LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS data_containers_static ARCHIVE DESTINATION lib COMPONENT libraries )
