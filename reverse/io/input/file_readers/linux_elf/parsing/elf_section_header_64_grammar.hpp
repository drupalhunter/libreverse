#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_64_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_64_GRAMMAR_HPP

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {
namespace parsing {

template <typename Iterator>
struct elf_section_header_64_grammar : boost::spirit::qi::grammar < Iterator, elf_section_header_64() > {
     elf_header_grammar ()
          : elf_header_grammar::base_type ( start ) {
     using boost::spirit::qi::char_;
     using boost::spirit::qi::repeat;
     using boost::spirit::qi::skip;
     using boost::spirit::qi::string;

     typedef boost::spirit::qi::uint_parser< boost::uint32_t, 10, 4, 4> uint4_t;
     typedef boost::spirit::qi::uint_parser< boost::uint64_t, 10, 8, 8> uint8_t;

     start = > uint4_t              // sh_name
             > uint4_t                    // sh_type
             > uint8_t                    // sh_flags
             > uint8_t                    // sh_addr
             > uint8_t                    // sh_offset
             > uint8_t                    // sh_size
             > uint4_t                    // sh_link
             > uint4_t                    // sh_info
             > uint8_t                    // sh_addralign
             > uint4_t;                   // sh_entsize
}

};

} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_64_GRAMMAR_HPP
