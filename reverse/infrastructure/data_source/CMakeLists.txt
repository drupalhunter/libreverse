project(data_source)

set ( DATA_SOURCE_SOURCES
  data_object.cpp
  data_source_factory.cpp
  database_data_source_config.cpp
  database_data_transfer.cpp
  file_data_source_config.cpp
  file_data_transfer.cpp
  memory_data_source_config.cpp
  memory_data_transfer.cpp
  output_visitor.cpp )

set ( DATA_SOURCE_HEADERS
  data_object.hpp
  data_source_base.hpp
  data_source_config_base.hpp
  data_source_factory.hpp
  data_source_factory_base.hpp
  data_source_t.hpp
  data_transfer_base.hpp
  database_data_source_config.hpp
  database_data_transfer.hpp
  file_data_source_config.hpp
  file_data_transfer.hpp
  memory_data_source_config.hpp
  memory_data_transfer.hpp
  output_visitor.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( data_source_static ${DATA_SOURCE_SOURCES} ${DATA_SOURCE_HEADERS} )
add_library ( data_source SHARED ${DATA_SOURCE_SOURCES} ${DATA_SOURCE_HEADERS} )
set_target_properties ( data_source_static PROPERTIES OUTPUT_NAME data_source )

install ( TARGETS data_source LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS data_source_static ARCHIVE DESTINATION lib COMPONENT libraries )

