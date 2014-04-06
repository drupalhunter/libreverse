/*  Exception_Table_Entry.cpp

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

#include "Exception_Table_Entry.h"
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

    Exception_Table_Entry::Exception_Table_Entry()
        : m_start_pc ( 0 ),
	  m_end_pc ( 0 ),
	  m_handler_pc ( 0 ),
	  m_catch_type ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Exception_Table_Entry constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Exception_Table_Entry::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Exception_Table_Entry::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << boost::format("Start PC: %|1$d| (%|2$X|)")
	  % m_start_pc
	  % m_start_pc
               << std::endl;

	output << io::Output::indent ( index )
	       << boost::format("End PC: %|1$d| (%|2$X|)")
	  % m_end_pc
	  % m_end_pc
               << std::endl;

	output << io::Output::indent ( index )
	       << boost::format("Handler PC: %|1$d| (%|2$X|)")
	  % m_handler_pc
	  % m_handler_pc
               << std::endl;
	
	output << io::Output::indent ( index )
	       << boost::format("Catch type: %|1$d| (%|2$X|)")
	  % m_catch_type
	  % m_catch_type
               << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Exception_Table_Entry::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

} /* namespace java_module */
} /* namespace reverse */
