project(input_components)

add_subdirectory(grnn)
add_subdirectory(instruction_decoders)

set ( INPUT_COMPONENT_SOURCES
  arch_type_detector.cpp
  arch_type_detector_algorithm_factory.cpp
  arch_type_detector_elf32_algorithm.cpp
  arch_type_detector_elf64_algorithm.cpp
  arch_type_detector_java_algorithm.cpp
  arch_type_detector_wpef32_algorithm.cpp
  arch_type_detector_wpef64_algorithm.cpp
  code_section_detector.cpp
  code_section_detector_algorithm_factory.cpp
  code_section_detector_elf32_algorithm.cpp
  code_section_detector_elf64_algorithm.cpp
  code_section_detector_java_algorithm.cpp
  code_section_detector_wpef32_algorithm.cpp
  code_section_detector_wpef64_algorithm.cpp
  compiler_classifier.cpp
  data_section_detector.cpp
  data_section_detector_algorithm_factory.cpp
  data_section_detector_elf32_algorithm.cpp
  data_section_detector_elf64_algorithm.cpp
  data_section_detector_java_algorithm.cpp
  data_section_detector_wpef32_algorithm.cpp
  data_section_detector_wpef64_algorithm.cpp
  entry_point_detector.cpp
  entry_point_detector_algorithm_factory.cpp
  entry_point_detector_elf32_algorithm.cpp
  entry_point_detector_elf64_algorithm.cpp
  entry_point_detector_java_algorithm.cpp
  entry_point_detector_wpef32_algorithm.cpp
  entry_point_detector_wpef64_algorithm.cpp
  file_header_printer.cpp
  file_type_detector.cpp
  memory_map_producer.cpp
  tevis_unknown_region_checker.cpp
  tevis_unknown_region_checker_algorithm_factory.cpp
  tevis_unknown_region_checker_elf_algorithm.cpp
  tevis_unknown_region_checker_wpef_algorithm.cpp
  tevis_zero_filled_checker.cpp
  tevis_zero_filled_checker_algorithm_factory.cpp
  tevis_zero_filled_checker_elf_algorithm.cpp
  tevis_zero_filled_checker_wpef_algorithm.cpp
  unpacker.cpp
  unpacker_algorithm_factory.cpp
  unpacker_java_algorithm.cpp
  unpacker_x86_algorithm.cpp )

set ( INPUT_COMPONENT_HEADERS
  arch_type_detector.hpp
  arch_type_detector_algorithm.hpp
  arch_type_detector_algorithm_factory.hpp
  arch_type_detector_elf32_algorithm.hpp
  arch_type_detector_elf64_algorithm.hpp
  arch_type_detector_java_algorithm.hpp
  arch_type_detector_wpef32_algorithm.hpp
  arch_type_detector_wpef64_algorithm.hpp
  code_section_detector.hpp
  code_section_detector_algorithm.hpp
  code_section_detector_algorithm_factory.hpp
  code_section_detector_elf32_algorithm.hpp
  code_section_detector_elf64_algorithm.hpp
  code_section_detector_java_algorithm.hpp
  code_section_detector_wpef32_algorithm.hpp
  code_section_detector_wpef64_algorithm.hpp
  compiler_classifier.hpp
  data_section_detector.hpp
  data_section_detector_algorithm.hpp
  data_section_detector_algorithm_factory.hpp
  data_section_detector_elf32_algorithm.hpp
  data_section_detector_elf64_algorithm.hpp
  data_section_detector_java_algorithm.hpp
  data_section_detector_wpef32_algorithm.hpp
  data_section_detector_wpef64_algorithm.hpp
  entry_point_detector.hpp
  entry_point_detector_algorithm.hpp
  entry_point_detector_algorithm_factory.hpp
  entry_point_detector_elf32_algorithm.hpp
  entry_point_detector_elf64_algorithm.hpp
  entry_point_detector_java_algorithm.hpp
  entry_point_detector_wpef32_algorithm.hpp
  entry_point_detector_wpef64_algorithm.hpp
  file_header_printer.hpp
  file_type_detector.hpp
  memory_map_producer.hpp
  tevis_unknown_region_checker.hpp
  tevis_unknown_region_checker_algorithm.hpp
  tevis_unknown_region_checker_algorithm_factory.hpp
  tevis_unknown_region_checker_elf_algorithm.hpp
  tevis_unknown_region_checker_wpef_algorithm.hpp
  tevis_zero_filled_checker.hpp
  tevis_zero_filled_checker_algorithm.hpp
  tevis_zero_filled_checker_algorithm_factory.hpp
  tevis_zero_filled_checker_elf_algorithm.hpp
  tevis_zero_filled_checker_wpef_algorithm.hpp
  unpacker.hpp
  unpacker_algorithm.hpp
  unpacker_algorithm_factory.hpp
  unpacker_java_algorithm.hpp
  unpacker_x86_algorithm.hpp )

include_directories ( ${REVERSE_SOURCE_DIR} )

add_library ( input_components ${INPUT_COMPONENT_SOURCES} ${INPUT_COMPONENT_HEADERS} )
target_link_libraries ( input_components input_grnn_components input_decoder_components )

