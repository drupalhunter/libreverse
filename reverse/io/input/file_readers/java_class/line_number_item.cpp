/*  Line_Number_Item.cpp

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

#include "Line_Number_Item.h"
#include "Attribute_Tags.h"
#include "Class_File.h"

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

    Line_Number_Item::Line_Number_Item()
        : m_start_pc ( 0 ),
          m_line_number ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Line_Number_Item constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Line_Number_Item::to_String ( boost::uint16_t indent )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Line_Number_Item::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( indent )
	       << boost::format("Start pc: %d")
	  % m_start_pc
               << std::endl;

	output << io::Output::indent ( indent )
	       << boost::format("Line number: %d")
	  % m_line_number
               << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Line_Number_Item::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

} /* namespace java_module */
} /* namespace reverse */
