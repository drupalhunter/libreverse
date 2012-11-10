/*  Elf_File_T.cpp

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

#include "Elf_File.h"

#include "io/File_ID.h"
#include "errors/IO_Exception.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    Elf_File::Elf_File ( io_types::File_ID::const_ptr_t filename )
        : m_file ( filename )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_File constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File::read_Elf_Header_Eident ( elf_types::Elf_Header_Eident::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Elf_Header_Eident" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->m_magic));
        m_file.read(&(obj->m_class));
        m_file.read(&(obj->m_data_encoding));
        m_file.read(&(obj->m_file_version));
        m_file.read(&(obj->m_os_abi));
        m_file.read(&(obj->m_abi_version));

        m_file.seek(Elf_Header_Eident::SIZE);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Header_Eident\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Elf_Header_Eident" );
#endif /* LIBREVERSE_DEBUG */


    }

    bool Elf_File::init (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::init" );
#endif /* LIBREVERSE_DEBUG */


        bool result = m_file.init();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::init" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    void
    Elf_File::seek ( boost::uint32_t offset )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::seek" );
#endif /* LIBREVERSE_DEBUG */


        m_file.seek ( offset );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::seek" );
#endif /* LIBREVERSE_DEBUG */

    }

    data_types::Memory_Map::ptr_t
    Elf_File::subset ( boost::uint32_t length )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::subset" );
#endif /* LIBREVERSE_DEBUG */


        data_types::Memory_Map::ptr_t file_map_ptr = m_file.get_Map_Ptr();

        std::pair<data_types::Memory_Map::ptr_t,boost::int8_t> subset_ptr = file_map_ptr->subset ( length );

        if ( subset_ptr.second != data_types::Memory_Map::SUCCESS )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::subset" );
#endif /* LIBREVERSE_DEBUG */

        
        return subset_ptr.first;
    }

    void
    Elf_File::read_Elf_Program_Header ( elf_types::Elf_Program_Header_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Elf_Program_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->p_type));
        m_file.read(&(obj->p_offset));
        m_file.read(&(obj->p_vaddr));
        m_file.read(&(obj->p_paddr));
        m_file.read(&(obj->p_filesz));
        m_file.read(&(obj->p_memsz));
        m_file.read(&(obj->p_flags));
        m_file.read(&(obj->p_align));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Program_Header (32-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Elf_Program_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_Program_Header ( elf_types::Elf_Program_Header_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Elf_Program_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->p_type));
        m_file.read(&(obj->p_offset));
        m_file.read(&(obj->p_vaddr));
        m_file.read(&(obj->p_paddr));
        m_file.read(&(obj->p_filesz));
        m_file.read(&(obj->p_memsz));
        m_file.read(&(obj->p_flags));
        m_file.read(&(obj->p_align));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Program_Header (64-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Elf_Program_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_File_Header ( elf_types::Elf_File_Header_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Elf_File_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        elf_types::Elf_Header_Eident::ptr_t eident_ptr ( new Elf_Header_Eident() );

        this->read_Elf_Header_Eident ( eident_ptr );
        obj->e_ident = eident_ptr;

        m_file.read(&(obj->e_type));
        m_file.read(&(obj->e_machine));
        m_file.read(&(obj->e_version));
        m_file.read(&(obj->e_entry));
        m_file.read(&(obj->e_phoff));
        m_file.read(&(obj->e_shoff));
        m_file.read(&(obj->e_flags));
        m_file.read(&(obj->e_ehsize));
        m_file.read(&(obj->e_phentsize));
        m_file.read(&(obj->e_phnum));
        m_file.read(&(obj->e_shentsize));
        m_file.read(&(obj->e_shnum));
        m_file.read(&(obj->e_shstrndx));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_File_Header (32-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Elf_File_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_File_Header ( elf_types::Elf_File_Header_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Elf_File_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        elf_types::Elf_Header_Eident::ptr_t eident_ptr ( new Elf_Header_Eident() );

        this->read_Elf_Header_Eident ( eident_ptr );
        obj->e_ident = eident_ptr;

        m_file.read(&(obj->e_type));
        m_file.read(&(obj->e_machine));
        m_file.read(&(obj->e_version));
        m_file.read(&(obj->e_entry));
        m_file.read(&(obj->e_phoff));
        m_file.read(&(obj->e_shoff));
        m_file.read(&(obj->e_flags));
        m_file.read(&(obj->e_ehsize));
        m_file.read(&(obj->e_phentsize));
        m_file.read(&(obj->e_phnum));
        m_file.read(&(obj->e_shentsize));
        m_file.read(&(obj->e_shnum));
        m_file.read(&(obj->e_shstrndx));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_File_Header (64-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Elf_File_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_Section_Header ( elf_types::Elf_Section_Header_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Section_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->sh_name));
        m_file.read(&(obj->sh_type));
        m_file.read(&(obj->sh_flags));
        m_file.read(&(obj->sh_addr));
        m_file.read(&(obj->sh_offset));
        m_file.read(&(obj->sh_size));
        m_file.read(&(obj->sh_link));
        m_file.read(&(obj->sh_info));
        m_file.read(&(obj->sh_addralign));
        m_file.read(&(obj->sh_entsize));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Section_Header (32-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Section_Header (32-bit)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File::read_Elf_Section_Header ( elf_types::Elf_Section_Header_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Section_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->sh_name));
        m_file.read(&(obj->sh_type));
        m_file.read(&(obj->sh_flags));
        m_file.read(&(obj->sh_addr));
        m_file.read(&(obj->sh_offset));
        m_file.read(&(obj->sh_size));
        m_file.read(&(obj->sh_link));
        m_file.read(&(obj->sh_info));
        m_file.read(&(obj->sh_addralign));
        m_file.read(&(obj->sh_entsize));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Section_Header (64-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Section_Header (64-bit)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File::read_Elf_Symbol ( elf_types::Elf_Symbol_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Symbol (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->st_name));
        m_file.read(&(obj->st_value));
        m_file.read(&(obj->st_size));
        m_file.read(&(obj->st_info));
        obj->m_symbol_type = static_cast<boost::uint8_t>(obj->st_info & 0xF);
        obj->m_symbol_binding = static_cast<boost::uint8_t>(obj->st_info >> 4);
        m_file.read(&(obj->st_other));
        m_file.read(&(obj->st_shndx));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Symbol (32-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Symbol (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_Symbol ( elf_types::Elf_Symbol_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Symbol (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->st_name));
        m_file.read(&(obj->st_value));
        m_file.read(&(obj->st_size));
        m_file.read(&(obj->st_info));
        obj->m_symbol_type = static_cast<boost::uint8_t>(obj->st_info & 0xF);
        obj->m_symbol_binding = static_cast<boost::uint8_t>(obj->st_info >> 4);
        m_file.read(&(obj->st_other));
        m_file.read(&(obj->st_shndx));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Symbol (64-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Symbol (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Relocation_Add (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->r_offset));
        m_file.read(&(obj->r_info));
        m_file.read(&(obj->r_addend));
        obj->m_symbol_table_index = static_cast<boost::uint32_t>(obj->r_info >> 8);
        obj->m_reloc_type = static_cast<boost::uint32_t>(obj->r_info & 0xFF);



#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation_Add (32-bit)" )
					  % obj->to_String() ) );
	
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Relocation_Add (32-bit)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File::read_Elf_Relocation_Add ( elf_types::Elf_Relocation_Add_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Relocation_Add (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->r_offset));
        m_file.read(&(obj->r_info));
        m_file.read(&(obj->r_addend));
        obj->m_symbol_table_index = static_cast<boost::uint64_t>(obj->r_info >> 32);
        obj->m_reloc_type = static_cast<boost::uint64_t>(obj->r_info & 0xFFFFFFFF);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation_Add (64-bit)\n%s" )
					  % obj->to_String() ) );
	
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Relocation_Add (64-bit)" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_File::read_Elf_Relocation ( elf_types::Elf_Relocation_32::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Relocation (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->r_offset));
        m_file.read(&(obj->r_info));
        obj->m_symbol_table_index = static_cast<boost::uint32_t>(obj->r_info >> 8);
        obj->m_reloc_type = static_cast<boost::uint32_t>(obj->r_info & 0xFF);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation (32-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Relocation (32-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Elf_File::read_Elf_Relocation ( elf_types::Elf_Relocation_64::ptr_t& obj)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_File::read_Relocation (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


        m_file.init();

        m_file.read(&(obj->r_offset));
        m_file.read(&(obj->r_info));
        obj->m_symbol_table_index = static_cast<boost::uint64_t>(obj->r_info >> 32);
        obj->m_reloc_type = static_cast<boost::uint64_t>(obj->r_info & 0xFFFFFFFF);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format ( "Elf_File::read_Elf_Relocation (64-bit)\n%s" )
					  % obj->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_File::read_Relocation (64-bit)" );
#endif /* LIBREVERSE_DEBUG */


    }

    boost::uint32_t
    Elf_File::size ( void ) const
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
			     "Inside Elf_File::size" );
#endif /* LIBREVERSE_DEBUG */


      return m_file.size();
    }

} /* namespace elf_module */
} /* namespace libreverse */
