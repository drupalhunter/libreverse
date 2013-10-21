/*
  Copyright (C) 2008 Stephen Torri

  This file is part of Libreverse.

  Libreverse is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3, or (at your
  option) any later version.

  Libreverse is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#include <reverse/io/input/file_readers/linux_elf/elf_file_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_parser.hpp>
#include <reverse/io/input/file_readers/linux_elf/parsing/elf_eident_grammar.hpp>
#include <reverse/io/input/file_readers/linux_elf/parsing/elf_file_header_32_grammar.hpp>
#include <reverse/io/input/file_readers/linux_elf/parsing/elf_program_header_32_grammar.hpp>
#include <reverse/io/input/file_readers/linux_elf/parsing/elf_section_header_32_grammar.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/trace.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  bool elf_parser::read ( char const* iter,
				  const char* end,
				  elf_file_32& output )
	  {
	    // Read Elf file header
	    bool result = read_elf_file_header ( iter, end, output.elf_file_header );
     
	    // 	 // Read Program Header
	    // 	 result = read_elf_program_header ( iter, end, output.program_header );
	 
	    // Read Section header table

	 
	    // For each section header entry
	    //   Read Section header
	 
	 
	 
	    return result;
	  }
	  bool elf_parser::read_elf_header_eident ( char const* iter,
						    char const* end,
						    elf_eident_header& elf_eident_header_obj )
	  {
	    linux_elf::parsing::elf_eident_header_grammar<char const*> eident_parser;

	    bool result = boost::spirit::qi::parse ( iter,
						     end,
						     eident_parser,
						     elf_eident_header_obj );

	    return result;
	  }

	  bool elf_parser::read_elf_file_header ( const char* iter,
						  const char* end, 
						  elf_file_header_32& elf_file_header_obj )
	  {
	    linux_elf::parsing::elf_file_header_32_grammar<char const*> elf_file_header_parser;
    
	    bool result = boost::spirit::qi::parse ( iter,
						     end,
						     elf_file_header_parser,
						     elf_file_header_obj );
    
	    return result;
	  }

	  bool elf_parser::read_elf_program_header ( const char* iter,
						     const char* end, 
						     elf_program_header_32& program_header_obj )
	  {
	    linux_elf::parsing::elf_program_header_32_grammar<char const*> program_header_parser;
    
	    bool result = boost::spirit::qi::parse ( iter,
						     end,
						     program_header_parser,
						     program_header_obj );
    
	    return result;
	  }

	  bool elf_parser::read_elf_section_header ( const char* iter,
						     const char* end, 
						     elf_section_header_32& section_header_obj )
	  {
	    linux_elf::parsing::elf_section_header_32_grammar<const char*> section_header_parser;
    
	    bool result = boost::spirit::qi::parse ( iter,
						     end,
						     section_header_parser,
						     section_header_obj );
    
	    return result;
	  }

	  //
	  //     void
	  //     Elf_File::read_Elf_Program_Header ( elf_types::Elf_Program_Header_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Elf_Program_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->p_type));
	  //         m_file.read(&(obj->p_offset));
	  //         m_file.read(&(obj->p_vaddr));
	  //         m_file.read(&(obj->p_paddr));
	  //         m_file.read(&(obj->p_filesz));
	  //         m_file.read(&(obj->p_memsz));
	  //         m_file.read(&(obj->p_flags));
	  //         m_file.read(&(obj->p_align));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Program_Header (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Elf_Program_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_File_Header ( elf_types::Elf_File_Header_32::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Elf_File_Header (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         elf_types::Elf_Header_Eident::ptr_t eident_ptr ( new Elf_Header_Eident() );
	  //
	  //         this->read_Elf_Header_Eident ( eident_ptr );
	  //         obj->e_ident = eident_ptr;
	  //
	  //         m_file.read(&(obj->e_type));
	  //         m_file.read(&(obj->e_machine));
	  //         m_file.read(&(obj->e_version));
	  //         m_file.read(&(obj->e_entry));
	  //         m_file.read(&(obj->e_phoff));
	  //         m_file.read(&(obj->e_shoff));
	  //         m_file.read(&(obj->e_flags));
	  //         m_file.read(&(obj->e_ehsize));
	  //         m_file.read(&(obj->e_phentsize));
	  //         m_file.read(&(obj->e_phnum));
	  //         m_file.read(&(obj->e_shentsize));
	  //         m_file.read(&(obj->e_shnum));
	  //         m_file.read(&(obj->e_shstrndx));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_File_Header (32-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Elf_File_Header (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_File_Header ( elf_types::Elf_File_Header_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Elf_File_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         elf_types::Elf_Header_Eident::ptr_t eident_ptr ( new Elf_Header_Eident() );
	  //
	  //         this->read_Elf_Header_Eident ( eident_ptr );
	  //         obj->e_ident = eident_ptr;
	  //
	  //         m_file.read(&(obj->e_type));
	  //         m_file.read(&(obj->e_machine));
	  //         m_file.read(&(obj->e_version));
	  //         m_file.read(&(obj->e_entry));
	  //         m_file.read(&(obj->e_phoff));
	  //         m_file.read(&(obj->e_shoff));
	  //         m_file.read(&(obj->e_flags));
	  //         m_file.read(&(obj->e_ehsize));
	  //         m_file.read(&(obj->e_phentsize));
	  //         m_file.read(&(obj->e_phnum));
	  //         m_file.read(&(obj->e_shentsize));
	  //         m_file.read(&(obj->e_shnum));
	  //         m_file.read(&(obj->e_shstrndx));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_File_Header (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Elf_File_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Section_Header ( elf_types::Elf_Section_Header_32::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Section_Header (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->sh_name));
	  //         m_file.read(&(obj->sh_type));
	  //         m_file.read(&(obj->sh_flags));
	  //         m_file.read(&(obj->sh_addr));
	  //         m_file.read(&(obj->sh_offset));
	  //         m_file.read(&(obj->sh_size));
	  //         m_file.read(&(obj->sh_link));
	  //         m_file.read(&(obj->sh_info));
	  //         m_file.read(&(obj->sh_addralign));
	  //         m_file.read(&(obj->sh_entsize));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Section_Header (32-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Section_Header (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Section_Header ( elf_types::Elf_Section_Header_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Section_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->sh_name));
	  //         m_file.read(&(obj->sh_type));
	  //         m_file.read(&(obj->sh_flags));
	  //         m_file.read(&(obj->sh_addr));
	  //         m_file.read(&(obj->sh_offset));
	  //         m_file.read(&(obj->sh_size));
	  //         m_file.read(&(obj->sh_link));
	  //         m_file.read(&(obj->sh_info));
	  //         m_file.read(&(obj->sh_addralign));
	  //         m_file.read(&(obj->sh_entsize));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Section_Header (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Section_Header (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Symbol ( elf_types::Elf_Symbol_32::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Symbol (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->st_name));
	  //         m_file.read(&(obj->st_value));
	  //         m_file.read(&(obj->st_size));
	  //         m_file.read(&(obj->st_info));
	  //         obj->m_symbol_type = static_cast<boost::uint8_t>(obj->st_info & 0xF);
	  //         obj->m_symbol_binding = static_cast<boost::uint8_t>(obj->st_info >> 4);
	  //         m_file.read(&(obj->st_other));
	  //         m_file.read(&(obj->st_shndx));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Symbol (32-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Symbol (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Symbol ( elf_types::Elf_Symbol_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Symbol (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->st_name));
	  //         m_file.read(&(obj->st_value));
	  //         m_file.read(&(obj->st_size));
	  //         m_file.read(&(obj->st_info));
	  //         obj->m_symbol_type = static_cast<boost::uint8_t>(obj->st_info & 0xF);
	  //         obj->m_symbol_binding = static_cast<boost::uint8_t>(obj->st_info >> 4);
	  //         m_file.read(&(obj->st_other));
	  //         m_file.read(&(obj->st_shndx));
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Symbol (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Symbol (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_32::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Relocation_Add (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->r_offset));
	  //         m_file.read(&(obj->r_info));
	  //         m_file.read(&(obj->r_addend));
	  //         obj->m_symbol_table_index = static_cast<boost::uint32_t>(obj->r_info >> 8);
	  //         obj->m_reloc_type = static_cast<boost::uint32_t>(obj->r_info & 0xFF);
	  //
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation_Add (32-bit)" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Relocation_Add (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Relocation_Add (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->r_offset));
	  //         m_file.read(&(obj->r_info));
	  //         m_file.read(&(obj->r_addend));
	  //         obj->m_symbol_table_index = static_cast<boost::uint64_t>(obj->r_info >> 32);
	  //         obj->m_reloc_type = static_cast<boost::uint64_t>(obj->r_info & 0xFFFFFFFF);
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation_Add (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Relocation_Add (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Relocation ( elf_types::Elf_Relocation_32::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Relocation (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->r_offset));
	  //         m_file.read(&(obj->r_info));
	  //         obj->m_symbol_table_index = static_cast<boost::uint32_t>(obj->r_info >> 8);
	  //         obj->m_reloc_type = static_cast<boost::uint32_t>(obj->r_info & 0xFF);
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation (32-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Relocation (32-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     void
	  //     Elf_File::read_Elf_Relocation ( elf_types::Elf_Relocation_64::ptr_t& obj)
	  //     {
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Entering Elf_File::read_Relocation (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //         m_file.init();
	  //
	  //         m_file.read(&(obj->r_offset));
	  //         m_file.read(&(obj->r_info));
	  //         obj->m_symbol_table_index = static_cast<boost::uint64_t>(obj->r_info >> 32);
	  //         obj->m_reloc_type = static_cast<boost::uint64_t>(obj->r_info & 0xFFFFFFFF);
	  //
	  //
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DATA,
	  // 			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation (64-bit)\n%s" )
	  // 					  % obj->to_String() ) );
	  //
	  //         Trace::write_Trace ( TraceArea::IO,
	  //                              TraceLevel::DETAIL,
	  //                              "Exiting Elf_File::read_Relocation (64-bit)" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //     }
	  //
	  //     boost::uint32_t
	  //     Elf_File::size ( void ) const
	  //     {
	  // #ifdef LIBREVERSE_DEBUG
	  //         Trace::write_Trace ( TraceArea::IO,
	  // 			     TraceLevel::DETAIL,
	  // 			     "Inside Elf_File::size" );
	  // #endif /* LIBREVERSE_DEBUG */
	  //
	  //
	  //       return m_file.size();
	  //     }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse
