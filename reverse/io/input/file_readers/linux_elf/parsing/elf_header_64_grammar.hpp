#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_GRAMMAR_HPP
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_GRAMMAR_HPP

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {
	  namespace parsing {

	    template <typename Iterator>
	    struct elf_header_32_grammar : boost::spirit::qi::grammar < Iterator, elf_header_64() >
	    {
	      elf_header_grammar ()
		: elf_header_grammar::base_type ( start )
	      {
		using boost::spirit::qi::char_;
		using boost::spirit::qi::repeat;
		using boost::spirit::qi::skip;
		using boost::spirit::qi::string;

		typedef boost::spirit::qi::uint_parser< boost::uint8_t, 10, 1, 1> uint1_t;
		typedef boost::spirit::qi::uint_parser< boost::uint16_t, 10, 2, 2> uint2_t;
		typedef boost::spirit::qi::uint_parser< boost::uint32_t, 10, 4, 4> uint4_t;
		typedef boost::spirit::qi::uint_parser< boost::uint64_t, 10, 8, 8> uint8_t;

		start = > uint2_t                    // e_type
		  > uint2_t                    // e_machine
		  > uint4_t                    // e_version
		  > uint8_t                    // e_entry
		  > uint8_t                    // e_phoff
		  > uint8_t                    // e_shoff
		  > uint4_t                    // e_flags
		  > uint2_t                    // e_ehsize
		  > uint2_t                    // e_phentsize
		  > uint2_t                    // e_phnum
		  > uint2_t                    // e_shentsize
		  > uint2_t                    // e_shnum
		  > uint2_t;                    // e_shstrndx
	      }

	    };

} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_HEADER_GRAMMAR_HPP
