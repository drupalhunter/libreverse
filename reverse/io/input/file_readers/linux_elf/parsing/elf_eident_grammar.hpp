#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_PARSING_ELF_EIDENT_HEADER_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_PARSING_ELF_EIDENT_HEADER_GRAMMAR_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_eident_header.hpp>

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_advance.hpp>

namespace reverse {
    namespace io {
        namespace input {
            namespace file_readers {
                namespace linux_elf {
                    namespace parsing {

                        template <typename Iterator>
                        struct elf_eident_header_grammar : boost::spirit::qi::grammar < Iterator, elf_eident_header() > {
                            elf_eident_header_grammar ()
                            : elf_eident_header_grammar::base_type ( elf_eident_header_info ) {
                                using boost::spirit::qi::char_;
                                using boost::spirit::qi::byte_;
                                using boost::spirit::repository::qi::advance;
                                using boost::spirit::qi::string;

                                elf_eident_header_info = file_identification
                                > class_type
                                > data_encoding
                                > file_version
                                > osabi_identification
                                > abi_version
                                > advance ( 7 );

                                file_identification = char_ ( 0x7f )
                                > string ( "ELF" );

                                class_type = byte_;

                                data_encoding = byte_;

                                file_version = byte_;

                                osabi_identification = byte_;

                                abi_version = byte_;

                                BOOST_SPIRIT_DEBUG_NODE ( elf_eident_header_info );
                                BOOST_SPIRIT_DEBUG_NODE ( file_identification );
                                BOOST_SPIRIT_DEBUG_NODE ( class_type );
                                BOOST_SPIRIT_DEBUG_NODE ( data_encoding );
                                BOOST_SPIRIT_DEBUG_NODE ( file_version );
                                BOOST_SPIRIT_DEBUG_NODE ( osabi_identification );
                                BOOST_SPIRIT_DEBUG_NODE ( abi_version );
                            }

                            boost::spirit::qi::rule < Iterator, elf_eident_header() > elf_eident_header_info;
                            boost::spirit::qi::rule < Iterator, void() > file_identification;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > class_type;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > file_version;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > data_encoding;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > file_encoding;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > osabi_identification;
                            boost::spirit::qi::rule < Iterator, boost::uint8_t() > abi_version;
                        };

                    } //namespace parsing
                } // namespace linux_elf
            } // namespace file_readers
        } // namespace input
    } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_PARSING_ELF_EIDENT_HEADER_GRAMMAR_HPP
