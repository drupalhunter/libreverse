project(reverse_infrastructure)

add_subdirectory ( data_source )
add_subdirectory ( visitor )

file ( GLOB INFRASTRUCTURE_SOURCES *.cpp )
file ( GLOB INFRASTRUCTURE_HEADERS *.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} ${JSON_SPIRIT_INCLUDE_DIR} )

add_library ( ${PROJECT_NAME} ${INFRASTRUCTURE_SOURCES} ${INFRASTRUCTURE_HEADERS} )

install ( TARGETS ${PROJECT_NAME} LIBRARY
  DESTINATION lib COMPONENT libraries
  ARCHIVE DESTINATION lib COMPONENT libraries )
