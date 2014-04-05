project(reverse_data_containers)

file ( GLOB DATA_CONTAINERS_SOURCES *.cpp )
file ( GLOB DATA_CONTAINERS_HEADERS *.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_library ( ${PROJECT_NAME} ${DATA_CONTAINERS_SOURCES} ${DATA_CONTAINERS_HEADERS} )

install ( TARGETS ${PROJECT_NAME} LIBRARY
  DESTINATION lib COMPONENT libraries
  ARCHIVE DESTINATION lib COMPONENT libraries )
