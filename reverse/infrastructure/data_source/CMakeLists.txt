project(data_source)

file ( GLOB DATA_SOURCE_SOURCES *.cpp )
file ( GLOB DATA_SOURCE_HEADERS *.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_library ( ${PROJECT_NAME} ${DATA_SOURCE_SOURCES} ${DATA_SOURCE_HEADERS} )

install ( TARGETS ${PROJECT_NAME} LIBRARY
  DESTINATION lib COMPONENT libraries
  ARCHIVE DESTINATION lib COMPONENT libraries )


