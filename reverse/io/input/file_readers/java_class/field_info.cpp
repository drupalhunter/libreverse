/*  Field_Info.cpp

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

#include "Field_Info.h"
#include "Attribute_Info.h"

#include "io/Output.h"
#include "errors/IO_Exception.h"

#include <sstream>
#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace java_module {

    Field_Info::Field_Info()
      : m_access_flags ( 0 ),
	m_name_index ( 0 ),
	m_name_string ( "" ),
	m_descriptor_index ( 0 ),
	m_descriptor_string ( "" ),
	m_attributes_count ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Field_Info constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Field_Info::to_String ( boost::uint16_t indent_count )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Field_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( indent_count )
	       << "Field_Info:" << std::endl;

	output << io::Output::indent ( indent_count )
	       << boost::format ("  Access_Flags:       %|1$X|" )
	  % m_access_flags
	       << std::endl;

	output << io::Output::indent ( indent_count )
	       << boost::format ("  Name (%1$s) Index:         %|2$d| (%|3$X|)" )
	  % m_name_string
	  % m_name_index
	  % m_name_index
	       << std::endl;

	output << io::Output::indent ( indent_count )
	       << boost::format ("  Descriptor (%1$s) Index:   %|2$d| (%|3$X|)" )
	  % m_descriptor_string
	  % m_descriptor_index
	  % m_descriptor_index
	       << std::endl;

	output << io::Output::indent ( indent_count )
	       << boost::format ("  Attribute Count:    %|1$d| (%|2$X|)" )
	  % m_attributes_count
	  % m_attributes_count
	       << std::endl;

	output << io::Output::indent ( indent_count )
	       << "  Attributes: " << std::endl;

        for ( java_types::Class_Header::Attribute_Info_Map_t::const_iterator pos = m_attributes.begin();
              pos != m_attributes.end();
              ++pos )
            {
                output << (*pos).second->to_String ( indent_count + 2 );
            }
        output << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Field_Info::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

} /* namespace java_module */
} /* namespace libreverse */
