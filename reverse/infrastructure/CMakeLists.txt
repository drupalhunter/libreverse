project(reverse_infrastructure)

add_subdirectory ( data_source )
add_subdirectory ( visitor )

set ( INFRASTRUCTURE_SOURCES
        component_data.cpp
	component_graph.cpp
	component_source_state.cpp
	component_state.cpp
	component_working_state.cpp
	configuration_data.cpp
	configuration_tag_names.cpp
	configurator.cpp
	formula_list.cpp
	formula_parser.cpp
	formula_tag_names.cpp
	grnn_data_parser.cpp
	grnn_data_tag_names.cpp
	master_formula_parser.cpp
	master_formula_tag_names.cpp
        xmlexpatparser.cpp )

set ( INFRASTRUCTURE_HEADERS
	component.hpp
        component_actor.hpp
        component_data.hpp
	component_state.hpp
	component_state_algorithm.hpp
	component_source_state.hpp
	component_types.hpp
	component_working_state.hpp
	component_graph.hpp
	configuration_data.hpp
	configuration_tag_names.hpp
	configurator.hpp
	formula_list.hpp
	formula_parser.hpp
	formula_tag_names.hpp
	graph_types.hpp
	grnn_data_parser.hpp
	grnn_data_tag_names.hpp
	master_formula_parser.hpp
	master_formula_tag_names.hpp
        xmlexpatparser.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} ${JSON_SPIRIT_INCLUDE_DIR} )

add_library ( ${PROJECT_NAME} ${INFRASTRUCTURE_SOURCES} ${INFRASTRUCTURE_HEADERS} )

install ( TARGETS ${PROJECT_NAME} LIBRARY
  DESTINATION lib COMPONENT libraries
  ARCHIVE DESTINATION lib COMPONENT libraries )
