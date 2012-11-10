/*  Elf_Header_64.cpp

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

#include "Elf_Header_64.h"
#include "Elf_Symbol_64.h"

#include "errors/File_Reader_Exception.h"

#include <iomanip>
#include <sstream>
#include <boost/format.hpp>


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace elf_module {

    Elf_Header_64::Elf_Header_64()
        : m_base_address_set ( false ),
          m_base_address ( 0 ),
          m_dyn_hdr ( new Elf_Dynamic_Header_64() )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Elf_Header_64::~Elf_Header_64()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void Elf_Header_64::init ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header::init" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Header_64::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


        m_file_hdr->convert ();

        for ( elf_types::Elf_Header_64::Program_Header_List_t::iterator pos_ptr = m_prg_hdrs.begin();
              pos_ptr != m_prg_hdrs.end();
              ++pos_ptr )
            {
	      elf_types::Elf_Program_Header_64::ptr_t obj =
		boost::const_pointer_cast<elf_module::Elf_Program_Header_64>( (*pos_ptr) );
	      obj->convert();
            }

        for ( elf_types::Elf_Header_64::Section_Header_Map_t::iterator pos_ptr = m_sec_hdrs.begin();
              pos_ptr != m_sec_hdrs.end();
              ++pos_ptr )
            {
                elf_types::Elf_Section_Header_64::ptr_t sec_ptr =
		  boost::const_pointer_cast<elf_module::Elf_Section_Header_64>( (*pos_ptr).second );
                sec_ptr->convert ();
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


    }

    std::string
    Elf_Header_64::to_String ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        output_str << m_file_hdr->to_String() << std::endl;

        output_str << "------------------------------------------------"
                   << std::endl
                   << "             PROGRAM HEADERS"
                   << std::endl
                   << "------------------------------------------------"
                   << std::endl;

        output_str << boost::format ("  %|-15| %|-10| %|-12| %|-12| %|-8| %|-10| %|-4| %|-5|")
            % "Header"
            % "Offset"
            % "VAddr"
            % "PAddr"
            % "Filesz"
            % "Memsz"
            % "Flg"
            % "Align" << std::endl;

        for ( elf_types::Elf_Header_64::Program_Header_List_t::iterator pos_ptr = m_prg_hdrs.begin();
              pos_ptr != m_prg_hdrs.end();
              ++pos_ptr )
            {
                output_str << (*pos_ptr)->to_String() << std::endl;
            }

        output_str << std::endl;

        output_str << "------------------------------------------------"
                   << std::endl
                   << "             SECTION HEADERS"
                   << std::endl
                   << "------------------------------------------------"
                   << std::endl;

        output_str << boost::format(" %|-17| %|-8| %|-8| %|-8| %|-8| %|-3|")
	    % "Name"
            % "Addr"
            % "Offset"
            % "Size"
            % "Info"
            % "Addralign" << std::endl;

        for ( elf_types::Elf_Header_64::Section_Header_Map_t::iterator pos_ptr
                  = m_sec_hdrs.begin();
              pos_ptr != m_sec_hdrs.end();
              ++pos_ptr )
            {
                elf_types::Elf_Section_Header_64::const_ptr_t sec_ptr = (*pos_ptr).second;
                output_str << sec_ptr->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

    void
    Elf_Header_64::get_Text_String ( io_types::Text_Data::data_type* output ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


        m_file_hdr->get_Text_String ( output );
        
        for ( elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator pos_ptr = m_sec_hdrs.begin();
              pos_ptr != m_sec_hdrs.end();
              ++pos_ptr )
            {
                elf_types::Elf_Section_Header_64::const_ptr_t sec_ptr = (*pos_ptr).second;
                sec_ptr->get_Text_String ( output );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */

    }

    elf_types::Elf_File_Header_64::const_ptr_t
    Elf_Header_64::get_File_Header (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_File_Header" );
#endif /* LIBREVERSE_DEBUG */


        return m_file_hdr;
    }

    bool
    Elf_Header_64::is_File_Header_Set (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::is_File_Header_Set" );
#endif /* LIBREVERSE_DEBUG */


        bool result = true;

        if ( m_file_hdr.get() == 0 )
            {
                result = false;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::is_File_Header_Set" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    void Elf_Header_64::set_File_Header ( elf_types::Elf_File_Header_64::ptr_t hdr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::set_File_Header" );
#endif /* LIBREVERSE_DEBUG */


        m_file_hdr = hdr;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::set_File_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    elf_types::Elf_Section_Header_64::const_ptr_t
    Elf_Header_64::get_Section_Header ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Section_Header (uint16)" );
#endif /* LIBREVERSE_DEBUG */


        if ( index <= m_sec_hdrs.size() )
            {
                std::string name = m_sec_hdr_index[index];
                return this->get_Section_Header ( name );
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( " Index: %1%" ) % index ) );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( " Number of Section Headers: %1%" ) % m_sec_hdrs.size() ) );
#endif /* LIBREVERSE_DEBUG */


	      throw errors::File_Reader_Exception ( errors::File_Reader_Exception::OUT_OF_BOUNDS );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Section_Header (uint16)" );
#endif /* LIBREVERSE_DEBUG */

    }

    elf_types::Elf_Section_Header_64::const_ptr_t
    Elf_Header_64::get_Section_Header ( std::string name ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Section_Header (string)" );
#endif /* LIBREVERSE_DEBUG */


        elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator pos = m_sec_hdrs.find ( name );

        elf_types::Elf_Section_Header_64::const_ptr_t sec_ptr = (*pos).second;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Section_Header (string)" );
#endif /* LIBREVERSE_DEBUG */


        return sec_ptr;
    }

    elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator
    Elf_Header_64::get_Section_Header_Begin (void) const
    {
        return m_sec_hdrs.begin();
    }

    elf_types::Elf_Header_64::Section_Header_Map_t::const_iterator
    Elf_Header_64::get_Section_Header_End (void) const
    {
        return m_sec_hdrs.end();
    }

    void
    Elf_Header_64::push_Back_Section_Header ( elf_types::Elf_Section_Header_64::const_ptr_t sec_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::push_Back_Section_Header" );
#endif /* LIBREVERSE_DEBUG */


        std::string section_name = sec_ptr->get_Section_String_Name();

        m_sec_hdrs.insert ( std::make_pair( section_name, sec_ptr ) );

        m_sec_hdr_index.push_back ( section_name );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::push_Back_Section_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Header_64::push_Back_Program_Header ( elf_types::Elf_Program_Header_64::const_ptr_t prg )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::push_Back_Program_Header" );
#endif /* LIBREVERSE_DEBUG */


        if ( ! m_base_address_set )
            {
                m_base_address_set = true;
                m_base_address = prg->get_Virtual_Address();
            }
        else if ( ( prg->get_Virtual_Address() < m_base_address ) && ( prg->get_Virtual_Address() != 0 ) )
            {
                m_base_address = prg->get_Virtual_Address();
            }
        else
            {
                // Do nothing
            }

        m_prg_hdrs.push_back ( prg );

        if (prg->get_Type() == Elf_Common::PT_LOAD)
            {
                m_instruction_prg_hdrs.push_back(prg);
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::push_Back_Program_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Header_64::push_Back_Relocation_Header ( elf_types::Elf_Relocation_64::const_ptr_t rel )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::push_Back_Relocation_Header" );
#endif /* LIBREVERSE_DEBUG */


        m_relocs.push_back(rel);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::push_Back_Relocation_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Header_64::push_Back_Relocation_Add_Header ( elf_types::Elf_Relocation_Add_64::const_ptr_t rel )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::push_Back_Relocation_Add_Header" );
#endif /* LIBREVERSE_DEBUG */


        m_relocs_add.push_back(rel);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::push_Back_Relocation_Add_Header" );
#endif /* LIBREVERSE_DEBUG */


    }

    bool
    Elf_Header_64::has_Section_Headers (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header::has_Section_Headers" );
#endif /* LIBREVERSE_DEBUG */


        return ( ! m_sec_hdrs.empty() );
    }

    bool
    Elf_Header_64::has_Program_Headers (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header::has_Program_Headers" );
#endif /* LIBREVERSE_DEBUG */


        return ( !m_prg_hdrs.empty() );
    }

    bool
    Elf_Header_64::has_Symbols (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header::has_Symbols" );
#endif /* LIBREVERSE_DEBUG */


        return (!m_symbol_table.empty());
    }

    std::string
    Elf_Header_64::get_Program_Header_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Program_Header_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
        for ( elf_types::Elf_Header_64::Program_Header_List_t::const_iterator pos = m_prg_hdrs.begin();
              pos != m_prg_hdrs.end();
              ++pos )
            {
                output << (*pos)->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Program_Header_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    /* NOTE: Possibly we can remove this function */
    std::string
    Elf_Header_64::get_Symbol_Token_String ( char const* string_table ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Symbol_Token_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
        uint32_t counter = 0;

        for ( elf_types::Elf_Header_64::Symbol_List_t::const_iterator pos =  m_symbol_table.begin();
              pos != m_symbol_table.end();
              ++pos )
            {
                if ( m_file_hdr->get_String_Token_Index () != Elf_Common::SHN_UNDEF )
                    {
                        const char* name = string_table + (*pos)->get_String_Token_Index();

			elf_types::Elf_Symbol_64::ptr_t obj =
			  boost::const_pointer_cast<elf_module::Elf_Symbol_64>( (*pos) );

                        obj->set_Symbol_Name( std::string(name) );
                    }

                output << boost::format("%1%: %2%") %
                    boost::io::group(std::setfill(' '), std::setw(7), counter) %
                    (*pos)->to_String() << std::endl;

                ++counter;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Symbol_Token_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    std::string
    Elf_Header_64::get_Relocation_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Relocation_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
        output << "  Number of symbols: " << m_relocs.size() << std::endl;

        for ( elf_types::Elf_Header_64::Relocation_List_t::const_iterator pos = m_relocs.begin();
              pos != m_relocs.end();
              ++pos )
            {
                output << (*pos)->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Relocation_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    std::string
    Elf_Header_64::get_Relocation_Add_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Relocation_Add_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;
        output << "  Number of symbols: " << m_relocs_add.size() << std::endl;

        for ( elf_types::Elf_Header_64::Relocation_Add_List_t::const_iterator pos = m_relocs_add.begin();
              pos != m_relocs_add.end();
              ++pos )
            {
                output << (*pos)->to_String() << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Relocation_Add_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Elf_Header_64::push_Back_Symbol ( elf_types::Elf_Symbol_64::const_ptr_t sym )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::push_Back_Symbol" );
#endif /* LIBREVERSE_DEBUG */


        m_symbol_table.push_back (sym);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::push_Back_Symbol" );
#endif /* LIBREVERSE_DEBUG */

    }

    elf_types::Elf_Symbol_64::const_ptr_t
    Elf_Header_64::get_Symbol ( boost::uint64_t index )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Symbol" );
#endif /* LIBREVERSE_DEBUG */


        if (index <= m_symbol_table.size())
            {
                return m_symbol_table[index];
            }
        else
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( " Index: %1%" ) % index ) );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::ERROR,
				   boost::str ( boost::format ( " Number of Symbols: %1%" ) % m_symbol_table.size() ) );
#endif /* LIBREVERSE_DEBUG */


	      throw errors::File_Reader_Exception ( errors::File_Reader_Exception::OUT_OF_BOUNDS );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Symbol" );
#endif /* LIBREVERSE_DEBUG */


    }

    elf_types::Elf_Program_Header_64::const_ptr_t
    Elf_Header_64::get_Program_Header ( boost::uint32_t addr ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Header::get_Program_Header" );
#endif /* LIBREVERSE_DEBUG */


        elf_types::Elf_Header_64::Program_Header_List_t::const_iterator pos;

        for ( pos = m_instruction_prg_hdrs.begin();
              pos != m_instruction_prg_hdrs.end();
              ++pos)
            {
                if ((*pos)->in_Range(addr))
                    {
                        break;
                    }
            }
        

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Header::get_Program_Header" );
#endif /* LIBREVERSE_DEBUG */


        return *pos;
    }

    boost::uint64_t
    Elf_Header_64::get_Base_Address (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Elf_Header::get_Base_Address" );
#endif /* LIBREVERSE_DEBUG */


        return m_base_address;
    }
  
} /* namespace elf_module */
} /* namespace libreverse */
