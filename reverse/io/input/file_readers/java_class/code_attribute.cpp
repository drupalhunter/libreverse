/*  Code_Attribute.cpp

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

#include "Code_Attribute.h"
#include "Attribute_Tags.h"
#include "Exception_Table_Entry.h"
#include "Class_File.h"
#include "Class_Header.h"

#include "io/Byte_Converter.h"
#include "io/Output.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace reverse { namespace java_module {

    Code_Attribute::Code_Attribute( boost::uint16_t index )
        : m_name_index ( index ),
          m_attribute_name ( Attribute_Tags::CODE ),
          m_max_stack ( 0 ),
          m_max_locals ( 0 ),
          m_code_length ( 0 ),
          m_exception_table_length ( 0 ),
          m_attributes_count ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Code_Attribute::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Code_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << boost::format("Tag: %|1$s|(%|2$d|) (0x%|3$X| bytes)")
            % m_attribute_name
            % m_name_index
            % m_attribute_length
               << std::endl;

	output << io::Output::indent ( index )
	       << boost::format ( "Max stack: 0x%|1$X| (%|2$d|)" )
	  % m_max_stack
	  % m_max_stack
               << std::endl;

	output << io::Output::indent ( index )
	       << boost::format ( "Max locals: 0x%|1$X| (%|2$d|)")
	  % m_max_locals
	  % m_max_locals
               << std::endl;

	output << io::Output::indent ( index )
	       << boost::format ( "Code length: 0x%|1$X| (%|2$d|)")
	  % m_code_length
	  % m_code_length
               << std::endl;
	
	output << io::Output::indent ( index );

        size_t code_length = m_code.size();

        for ( std::vector<boost::uint8_t>::const_iterator pos = m_code.begin();
              pos != m_code.end();
              pos++ )
            {

                output << boost::format("%|1$02X|") % static_cast<boost::uint16_t>(*pos);

                if ( code_length > 1 )
                    {
                        output << " ";
                        code_length--;
                    }
            }
        output << std::endl;

	output << io::Output::indent ( index )
	       << boost::format ("Exception table length: 0x%|1$X| (%|2$d|)")
	  % m_exception_table_length
	  % m_exception_table_length
               << std::endl;

        boost::uint16_t new_index = index + 2;

        for ( java_types::Code_Attribute::Exception_Table_t::const_iterator pos =
                  m_exception_table.begin();
              pos != m_exception_table.end();
              pos++ )
            {
                output << (*pos)->to_String ( new_index ) << std::endl;
            }

	output << io::Output::indent ( index )
	       << boost::format ("Attribute count: 0x%|1$X| (%|2$d|)")
	  % m_attributes_count
	  % m_attributes_count
               << std::endl;

	output << io::Output::indent ( index );

        for ( java_types::Code_Attribute::Attribute_Table_t::const_iterator pos = m_attributes.begin();
              pos != m_attributes.end();
              ++pos )
            {
                output << (*pos)->to_String ( new_index ) << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Code_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Code_Attribute::read_Input ( java_types::Class_File::ptr_t file_ptr,
                                 java_types::Class_Header::ptr_t hdr_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Code_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Code_Attribute ( this->shared_from_this(),
                                        hdr_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Code_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Code_Attribute::is_Type ( std::string target ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::is_Type" );
#endif /* LIBREVERSE_DEBUG */

        return ( target == Attribute_Tags::CODE );
    }

    std::string
    Code_Attribute::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Tag" );
#endif /* LIBREVERSE_DEBUG */

        return m_attribute_name;
    }

    boost::uint16_t
    Code_Attribute::get_Name_Index (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Name_Index" );
#endif /* LIBREVERSE_DEBUG */

        return m_name_index;
    }

    std::string
    Code_Attribute::get_Attribute_Name (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Attribute_Name" );
#endif /* LIBREVERSE_DEBUG */


        return m_attribute_name;
    } 
          
    boost::uint32_t
    Code_Attribute::get_Attribute_Length (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Attribute_Length" );
#endif /* LIBREVERSE_DEBUG */


        return m_attribute_length;
    }

    boost::uint16_t
    Code_Attribute::get_Max_Stack (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Max_Stack" );
#endif /* LIBREVERSE_DEBUG */


        return m_max_stack;
    }

    boost::uint16_t
    Code_Attribute::get_Max_Locals (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Max_Locals" );
#endif /* LIBREVERSE_DEBUG */


        return m_max_locals;
    }

    boost::uint32_t
    Code_Attribute::get_Code_Length (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Code_Length" );
#endif /* LIBREVERSE_DEBUG */


        return m_code_length;
    }

    java_types::Code_Attribute::Code_List_t::const_iterator
    Code_Attribute::get_Code_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Code_Begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_code.begin();
    }

    java_types::Code_Attribute::Code_List_t::const_iterator
    Code_Attribute::get_Code_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Code_End" );
#endif /* LIBREVERSE_DEBUG */


        return m_code.end();
    }

    boost::uint16_t
    Code_Attribute::get_Exception_Table_Length (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Exception_Table_Length" );
#endif /* LIBREVERSE_DEBUG */


        return m_exception_table_length;
    }

    java_types::Code_Attribute::Exception_Table_t::const_iterator
    Code_Attribute::get_Exception_Table_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Exception_Table_Begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_exception_table.begin();
    }

    java_types::Code_Attribute::Exception_Table_t::const_iterator
    Code_Attribute::get_Exception_Table_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Exception_Table_End" );
#endif /* LIBREVERSE_DEBUG */


        return m_exception_table.begin();
    }

    boost::uint16_t
    Code_Attribute::get_Attributes_Count (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Attributes_Count" );
#endif /* LIBREVERSE_DEBUG */


        return m_attributes_count;
    }

    java_types::Code_Attribute::Attribute_Table_t::const_iterator
    Code_Attribute::get_Attributes_Begin (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Attributes_Begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_attributes.begin();
    }

    java_types::Code_Attribute::Attribute_Table_t::const_iterator
    Code_Attribute::get_Attributes_End (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Attributes_End" );
#endif /* LIBREVERSE_DEBUG */


        return m_attributes.end();
    }

    boost::uint8_t
    Code_Attribute::get_Code ( boost::uint32_t index ) const
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Code" );
#endif /* LIBREVERSE_DEBUG */

	boost::uint8_t code = m_code.at ( index );

	return code;
    }

    java_types::Code_Attribute::Code_List_t::const_iterator
    Code_Attribute::get_Code_Iterator ( boost::uint32_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Code_Attribute::get_Code_Iterator" );
#endif /* LIBREVERSE_DEBUG */

        return m_code.begin() + index;
    }

} /* namespace java_module */
} /* namespace reverse */
