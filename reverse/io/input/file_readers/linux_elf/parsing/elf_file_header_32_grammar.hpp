#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_32_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_32_GRAMMAR_HPP

#include <reverse/io/input/file_readers/linux_elf/elf_eident_header.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_file_header_32.hpp>

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
	    struct elf_file_header_32_grammar : boost::spirit::qi::grammar < Iterator, reverse::io::input::file_readers::linux_elf::elf_file_header_32() > {
	      elf_file_header_32_grammar ()
		: elf_file_header_32_grammar::base_type ( elf_file_header_info )
	      {
		using boost::spirit::qi::byte_;
		using boost::spirit::qi::char_;
		using boost::spirit::qi::dword;
		using boost::spirit::qi::word;
		using boost::spirit::repository::qi::advance;
		using boost::spirit::qi::string;

		elf_file_header_info = elf_eident_header_info
		  > e_type
		  > e_machine
		  > e_version
		  > e_entry
		  > e_phoff
		  > e_shoff
		  > e_flags
		  > e_ehsize
		  > e_phentsize
		  > e_phnum
		  > e_shentsize
		  > e_shnum
		  > e_shstrndx;

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

		e_type = word;
		e_machine = word;
		e_version = dword;
		e_entry = dword;
		e_phoff = dword;
		e_shoff = dword;
		e_flags = dword;
		e_ehsize = word;
		e_phentsize = word;
		e_phnum = word;
		e_shentsize = word;
		e_shnum = word;
		e_shstrndx = word;
      
		BOOST_SPIRIT_DEBUG_NODE ( elf_file_header_info );
		BOOST_SPIRIT_DEBUG_NODE ( elf_eident_header_info );
		BOOST_SPIRIT_DEBUG_NODE ( file_identification );
		BOOST_SPIRIT_DEBUG_NODE ( class_type );
		BOOST_SPIRIT_DEBUG_NODE ( data_encoding );
		BOOST_SPIRIT_DEBUG_NODE ( file_version );
		BOOST_SPIRIT_DEBUG_NODE ( osabi_identification );
		BOOST_SPIRIT_DEBUG_NODE ( abi_version );
		BOOST_SPIRIT_DEBUG_NODE ( e_type );
		BOOST_SPIRIT_DEBUG_NODE ( e_machine );
		BOOST_SPIRIT_DEBUG_NODE ( e_version );
		BOOST_SPIRIT_DEBUG_NODE ( e_entry );
		BOOST_SPIRIT_DEBUG_NODE ( e_phoff );
		BOOST_SPIRIT_DEBUG_NODE ( e_shoff );
		BOOST_SPIRIT_DEBUG_NODE ( e_flags );
		BOOST_SPIRIT_DEBUG_NODE ( e_ehsize );
		BOOST_SPIRIT_DEBUG_NODE ( e_phentsize );
		BOOST_SPIRIT_DEBUG_NODE ( e_phnum );
		BOOST_SPIRIT_DEBUG_NODE ( e_shentsize );
		BOOST_SPIRIT_DEBUG_NODE ( e_shnum );
		BOOST_SPIRIT_DEBUG_NODE ( e_shstrndx );

	      }

	      boost::spirit::qi::rule < Iterator, elf_file_header_32() > elf_file_header_info;
	      boost::spirit::qi::rule < Iterator, elf_eident_header() > elf_eident_header_info;
	      boost::spirit::qi::rule < Iterator, void() > file_identification;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > class_type;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > file_version;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > data_encoding;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > file_encoding;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > osabi_identification;
	      boost::spirit::qi::rule < Iterator, boost::uint8_t() > abi_version;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_type;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_machine;
	      boost::spirit::qi::rule < Iterator, boost::uint32_t() > e_version;
	      boost::spirit::qi::rule < Iterator, boost::uint32_t() > e_entry;
	      boost::spirit::qi::rule < Iterator, boost::uint32_t() > e_phoff;
	      boost::spirit::qi::rule < Iterator, boost::uint32_t() > e_shoff;
	      boost::spirit::qi::rule < Iterator, boost::uint32_t() > e_flags;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_ehsize;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_phentsize;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_phnum;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_shentsize;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_shnum;
	      boost::spirit::qi::rule < Iterator, boost::uint16_t() > e_shstrndx;

	    };

	  } // namespace parsing
	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_FILE_HEADER_32_GRAMMAR_HPP
