/*  Inner_Class_Reference.cpp

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

#include "Inner_Class_Reference.h"
#include "Attribute_Tags.h"
#include "Class_File.h"
#include "Class_File.h"
#include "Class_Header.h"

#include "errors/IO_Exception.h"
#include "io/Byte_Converter.h"
#include "io/Output.h"
#include "io/Preconditions.h"

#include <sstream>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Inner_Class_Reference::Inner_Class_Reference()
      : m_inner_class_info_index ( 0 ),
        m_outer_class_info_index ( 0 ),
        m_inner_name_index ( 0 ),
        m_inner_name ( "" ),
        m_inner_class_access_flags ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Inner_Class_Reference constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Inner_Class_Reference::to_String ( boost::uint16_t indent )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Inner_Class_Reference::to_String" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output;

	output << io::Output::indent ( indent )
	       << boost::format("Inner class info index: %d")
	  % m_inner_class_info_index
               << std::endl;

	output << io::Output::indent ( indent )
	       << boost::format("Outer class info index: %d")
	  % m_outer_class_info_index
               << std::endl;

	output << io::Output::indent ( indent )
	       << boost::format("Inner name: %s (%d)")
	  % m_inner_name
	  % m_inner_name_index
               << std::endl;

	output << io::Output::indent ( indent )
	       << boost::format("Inner class access flags: %d")
	  % m_inner_class_access_flags
               << std::endl;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Inner_Class_Reference::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    void Inner_Class_Reference::read_Impl ( java_types::Class_File::ptr_t file_ptr,
                                            java_types::Class_Header::ptr_t hdr_ptr )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Inner_Class_Reference::read_Impl" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( file_ptr );
	io::Preconditions::is_set ( hdr_ptr );

        file_ptr->read_Inner_Class_Reference ( this->shared_from_this(), hdr_ptr );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Inner_Class_Reference::read_Impl" );
#endif /* LIBREVERSE_DEBUG */

    }


} /* namespace java_module */
} /* namespace reverse */
