project(input_grnn_components)

set ( INPUT_GRNN_COMPONENTS_SOURCES
  compiler_classifier_algorithm_factory.cpp
  elf_input_tag_names.cpp
  elf_training_data.cpp
  elf_training_data_parser.cpp
  grnn_data_entry.cpp
  grnn_data_map.cpp
  grnn_data_types.cpp
  java_classifier_algorithm.cpp
  java_input_tag_names.cpp
  java_training_data.cpp
  java_training_data_parser.cpp
  variable_map.cpp
  windows_input_tag_names.cpp
  windows_training_data.cpp
  windows_training_data_parser.cpp )

set ( INPUT_GRNN_COMPONENTS_HEADERS
  candidate_solution.hpp
  compiler_classifier_algorithm_factory.hpp
  configuration.hpp
  elf_input_tag_names.hpp
  elf_training_data.hpp
  elf_training_data_parser.hpp
  grnn.hpp
  grnn_data_entry.hpp
  grnn_data_map.hpp
  grnn_data_types.hpp
  io.hpp
  java_classifier_algorithm.hpp
  java_input_tag_names.hpp
  java_training_data.hpp
  java_training_data_parser.hpp
  optimizer.hpp
  selection_policy.hpp
  statistical.hpp
  training_data.hpp
  training_set.hpp
  variable_map.hpp
  windows_input_tag_names.hpp
  windows_training_data.hpp
  windows_training_data_parser.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( input_grnn_components ${INPUT_GRNN_COMPONENTS_SOURCES} ${INPUT_GRNN_COMPONENTS_HEADERS} )

