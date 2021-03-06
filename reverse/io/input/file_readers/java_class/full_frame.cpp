/*  Full_Frame.cpp

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

#include "Full_Frame.h"
#include "Verification_Type_Factory.h"
#include "Verification_Type_Info.h"
#include "Class_File.h"

#include <sstream>
#include <boost/format.hpp>

#include "io/Byte_Converter.h"
#include "io/Output.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Full_Frame::Full_Frame ( boost::uint8_t tag )
        : m_tag ( tag ),
          m_offset_delta ( 0 ),
          m_number_of_locals ( 0 ),
          m_number_of_stack_items ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Full_Frame constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Full_Frame::to_String ( boost::uint16_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Full_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( index )
	       << boost::format("frame_type: 0x%1$2X")
	  % m_tag 
	       << std::endl;

	output << io::Output::indent ( index )
	       << boost::format("offset_delta: 0x%1$2X")
            % m_offset_delta
	       << std::endl;

	output << io::Output::indent ( index )
	       << boost::format("number of locals: 0x%1$2X")
	  % m_number_of_locals
	       << std::endl;

        boost::uint16_t new_index = index + 2;

        for ( List_t::const_iterator cpos = m_locals.begin();
              cpos != m_locals.end();
              cpos++ )
            {
                output << (*cpos)->to_String ( new_index );
            }

	output << io::Output::indent ( index )
	       << boost::format("number of stack_items: 0x%1$2X")
            % m_number_of_stack_items
	       << std::endl;

        for ( List_t::const_iterator cpos = m_stack.begin();
              cpos != m_stack.end();
              cpos++ )
            {
                output << (*cpos)->to_String ( new_index );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Full_Frame::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void
    Full_Frame::read_Input ( java_types::Class_File::ptr_t file_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Full_Frame::read_Input" );
#endif /* LIBREVERSE_DEBUG */


        file_ptr->read_Full_Frame ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Full_Frame::read_Input" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint8_t
    Full_Frame::get_Frame_Type ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Full_Frame::get_Frame_Type" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

    boost::uint8_t
    Full_Frame::get_Tag (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Full_Frame::get_Tag" );
#endif /* LIBREVERSE_DEBUG */


        return m_tag;
    }

} /* namespace java_module */
} /* namespace reverse */
