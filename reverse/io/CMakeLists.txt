project(reverse_io)

add_subdirectory ( input/file_readers )

set ( IO_SOURCES
   file.cpp
   file_id.cpp )

set ( IO_HEADERS
   byte_converter.hpp
   file.hpp
   file_id.hpp
   output.hpp
   string_converter.hpp )

include_directories ( ${CMAKE_SOURCE_DIR} )

add_library ( reverse_io_static ${IO_SOURCES} ${IO_HEADERS} )
add_library ( reverse_io SHARED ${IO_SOURCES} ${IO_HEADERS} )
set_target_properties ( reverse_io_static PROPERTIES OUTPUT_NAME reverse_io )

#target_link_libraries ( reverse_io_static io_readers io_elf io_java_class io_mach io_windows_pe )
#target_link_libraries ( reverse_io io_readers io_elf io_java_class io_mach io_windows_pe )
target_link_libraries ( reverse_io_static io_readers io_elf )
target_link_libraries ( reverse_io io_readers io_elf )

install ( TARGETS reverse_io LIBRARY DESTINATION lib COMPONENT libraries )
install ( TARGETS reverse_io_static ARCHIVE DESTINATION lib COMPONENT libraries )



