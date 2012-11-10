project(input_decoder_components)

set ( INPUT_DECODER_COMPONENTS_SOURCES
  java_assembly_actions.cpp
  java_decoder.cpp )

set ( INPUT_DECODER_COMPONENTS_HEADERS
  decoder.hpp
  java_assembly_actions.hpp
  java_decoder.hpp
  java_opcodes.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( input_decoder_components ${INPUT_DECODER_COMPONENTS_SOURCES} ${INPUT_DECODER_COMPONENTS_HEADERS} )


