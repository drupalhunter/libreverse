#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_GRAMMAR_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_section_header_32.hpp>

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>

namespace reverse {
    namespace io
    {
        namespace input
        {
            namespace file_readers
            {
                namespace linux_elf
                {
                    namespace parsing
                    {

                        template <typename Iterator>
                        struct elf_section_header_32_grammar : boost::spirit::qi::grammar < Iterator, elf_section_header_32() >
                        {
                            elf_section_header_32_grammar ()
                            : elf_section_header_32_grammar::base_type ( elf_section_header_32_info ) {
                                using boost::spirit::qi::dword;

                                elf_section_header_32_info = section_header_name
                                > section_header_type
                                > section_header_flags
                                > section_header_address
                                > section_header_offset
                                > section_header_size
                                > section_header_link
                                > section_header_info
                                > section_header_address_alignment
                                > section_header_entsize;

                                section_header_name = dword;

                                section_header_type = dword;

                                section_header_flags = dword;

                                section_header_address = dword;

                                section_header_offset = dword;

                                section_header_size = dword;

                                section_header_link = dword;

                                section_header_info = dword;

                                section_header_address_alignment = dword;

                                section_header_entsize = dword;
                            }

                            boost::spirit::qi::rule < Iterator, elf_section_header_32() > elf_section_header_32_info;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_name;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_type;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_flags;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_address;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_offset;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_size;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_link;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_info;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_address_alignment;
                            boost::spirit::qi::rule < Iterator, boost::uint32_t() > section_header_entsize;

                        };

                    } // namespace parsing
                } // namespace linux_elf
            } // namespace file_readers
        } // namespace input
    } //  namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_SECTION_HEADER_32_GRAMMAR_HPP