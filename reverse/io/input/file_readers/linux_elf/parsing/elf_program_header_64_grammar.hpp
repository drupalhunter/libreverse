#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_GRAMMAR_64_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_GRAMMAR_64_HPP

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>

namespace reverse {
namespace io {
namespace input {
namespace file_readers {
namespace linux_elf {
namespace parsing {

template <typename Iterator>
struct elf_program_header_64_grammar : boost::spirit::qi::grammar < Iterator, elf_program_header_64() > {
     elf_program_header_64_grammar ()
          : elf_program_header_64_grammar::base_type ( elf_program_header_64_info ) {
     using boost::spirit::qi::dword;
     using boost::spirit::qi::qword;

     elf_program_header_64_info = program_type
                                  > segment_offset
                                  > segment_virtual_address
                                  > segment_physical_address
                                  > filesize
                                  > image_size
                                  > flags
                                  > segment_alignment;

     program_type = dword;

     segment_offset = qword;

     segment_virtual_address = qword;

     segment_physical_address = qword;

     filesize = qword;

     image_size = qword;

     flags = qword;

     segment_alignment = qword;

     BOOST_SPIRIT_DEBUG_NODE ( elf_program_header_64_info );
     BOOST_SPIRIT_DEBUG_NODE ( program_type );
     BOOST_SPIRIT_DEBUG_NODE ( segment_offset );
     BOOST_SPIRIT_DEBUG_NODE ( segment_virtual_address );
     BOOST_SPIRIT_DEBUG_NODE ( segment_physical_address );
     BOOST_SPIRIT_DEBUG_NODE ( filesize );
     BOOST_SPIRIT_DEBUG_NODE ( image_size );
     BOOST_SPIRIT_DEBUG_NODE ( flags );
     BOOST_SPIRIT_DEBUG_NODE ( segment_alignment );
}


boost::spirit::qi::rule < Iterator, elf_program_header_64() > elf_program_header_64_info;
boost::spirit::qi::rule < Iterator, boost::uint32_t() > program_type;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > segment_offset;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > segment_virtual_address;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > segment_physical_address;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > filesize;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > image_size;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > flags;
boost::spirit::qi::rule < Iterator, boost::uint64_t() > segment_alignment;

};
} // namespace parsing
} // namespace linux_elf
} // namespace file_readers
} // namespace input
} //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_PROGRAM_HEADER_GRAMMAR_64_HPP
