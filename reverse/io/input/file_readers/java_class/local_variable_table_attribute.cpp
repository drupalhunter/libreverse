/*  Local_Variable_Table_Attribute.cpp

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

#include "Local_Variable_Table_Attribute.h"
#include "Local_Variable.h"
#include "Attribute_Tags.h"
#include "Class_File.h"
#include "Class_Header.h"

#include "errors/IO_Exception.h"
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

    Local_Variable_Table_Attribute::Local_Variable_Table_Attribute ( boost::uint16_t index )
        : m_attribute_name_index ( index ),
          m_attribute_name ( Attribute_Tags::LOCAL_VARIABLE_TABLE ),
          m_attribute_length ( 0 ),
          m_local_variable_table_length ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Local_Variable_Table_Attribute constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Local_Variable_Table_Attribute::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Local_Variable_Table_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

        output << io::Output::indent ( index )
               << boost::format("Number of local variables: %1%") % m_local_variable_table_length
               << std::endl
               << io::Output::indent ( index )
               << "Local variables list:" << std::endl;

        boost::uint16_t limit = index + 2;

        for ( Local_Variable_Table_Attribute::List_t::const_iterator cpos = m_local_variable_table.begin();
              cpos != m_local_variable_table.end();
              ++cpos )
            {
                output << io::Output::indent ( index )
                       << (*cpos)->to_String ( limit + 2 ) << std::endl;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Local_Variable_Table_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Local_Variable_Table_Attribute::read_Input ( java_types::Class_File::ptr_t file_ptr,
                                                 java_types::Class_Header::ptr_t hdr_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Local_Variable_Table_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Local_Variable_Table_Attribute ( this->shared_from_this(),
                                                        hdr_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Local_Variable_Table_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Local_Variable_Table_Attribute::is_Type ( std::string target ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Local_Variable_Table_Attribute::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return ( target == Attribute_Tags::LOCAL_VARIABLE_TABLE );
    }

    std::string
    Local_Variable_Table_Attribute::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Local_Variable_Table_Attribute::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_attribute_name;
    }
} /* namespace java_module */
} /* namespace reverse */
