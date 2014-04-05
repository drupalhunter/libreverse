project(libreverse)

#add_subdirectory(components)
add_subdirectory(data_containers)
add_subdirectory(errors)
#add_subdirectory(formulas)
add_subdirectory(infrastructure)
add_subdirectory(io)
add_subdirectory(meta)

set ( REVERSE_SOURCE_DIR "${CMAKE_SOURCE_DIR}" CACHE INTERNAL "Include directory" )
include_directories ( ${CMAKE_SOURCE_DIR} ${JSON_SPIRIT_INCLUDE_DIR} )

set ( REVERSE_SOURCES
reverse.cpp
reverse_impl.cpp
trace.cpp
trace_state.cpp
sp_debug_hooks.cpp )

set ( REVERSE_HEADERS
assert/assert.hpp
assert/bad_assert.hpp
count/counter.hpp
input_types.hpp
output_types.hpp
preconditions.hpp
results.hpp
reverse.hpp
reverse_impl.hpp
trace.hpp
trace_area.hpp
trace_level.hpp
trace_state.hpp
transfer_types.hpp )

# io_windows_pe io_java_class io_mach io_readers reverse_exceptions comp_input comp_output inf_data_source inf_visitor comp_grnn comp_instruction_decoders )

add_library ( ${PROJECT_NAME} ${REVERSE_SOURCES} ${REVERSE_HEADERS} ${REVERSE_DEPENDENCIES} )

add_dependencies ( ${PROJECT_NAME} components reverse_data_containers infrastructure io meta )

INSTALL( TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib COMPONENT libraries
   ARCHIVE DESTINATION lib COMPONENT libraries )

install ( FILES ${REVERSE_HEADERS} DESTINATION include/reverse )
