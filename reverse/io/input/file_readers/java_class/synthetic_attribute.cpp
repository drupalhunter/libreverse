/*  Synthetic_Attribute.cpp

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

#include "Synthetic_Attribute.h"
#include "Class_File.h"
#include "Class_Header.h"
#include "Attribute_Tags.h"

#include "errors/IO_Exception.h"
#include "io/Byte_Converter.h"
#include "io/Output.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace java_module {

    Synthetic_Attribute::Synthetic_Attribute ( boost::uint16_t index )
        : m_name_index ( index ),
          m_attribute_name ( Attribute_Tags::SYNTHETIC ),
          m_attribute_length ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Synthetic_Attribute constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Synthetic_Attribute::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Synthetic_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << boost::format("Tag: %|1$s|(%|2$d|) (0x%|3$X| bytes)")
            % m_attribute_name
            % m_name_index
            % m_attribute_length
               << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Synthetic_Attribute::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Synthetic_Attribute::read_Input ( java_types::Class_File::ptr_t file_ptr,
                                      java_types::Class_Header::ptr_t )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Synthetic_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Synthetic_Attribute ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Synthetic_Attribute::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Synthetic_Attribute::is_Type ( std::string target ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Synthetic_Attribute::is_Type" );
#endif /* LIBREVERSE_DEBUG */


        return ( target == Attribute_Tags::SYNTHETIC );
    }

    std::string
    Synthetic_Attribute::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Synthetic_Attribute::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_attribute_name;
    }

} /* namespace java_module */
} /* namespace libreverse */
