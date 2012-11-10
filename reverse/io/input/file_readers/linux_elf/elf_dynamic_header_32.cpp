/*  Elf_Dynamic_Header_32.cpp

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

#include "Elf_Dynamic_Header_32.h"
#include "io/Byte_Converter.h"
#include "Elf_Dynamic_Tag_32.h"

#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
    namespace elf_module
    {

        void
	Elf_Dynamic_Header_32::convert ()
        {


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Dynamic_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */


            for ( elf_types::Elf_Dynamic_Header_32::Tag_List_t::iterator pos = m_dyn_tags.begin();
                    pos != m_dyn_tags.end();
                    pos++ )
            {
                ( *pos )->Elf_Dynamic_Tag_32::convert();
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Dynamic_Header_32::convert" );
#endif /* LIBREVERSE_DEBUG */


        }

        std::string
	Elf_Dynamic_Header_32::toString ()
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Elf_Dynamic_Header_32::toString" );
#endif /* LIBREVERSE_DEBUG */


            std::stringstream output_str;

            for ( elf_types::Elf_Dynamic_Header_32::Tag_List_t::iterator pos = m_dyn_tags.begin();
                    pos != m_dyn_tags.end();
                    ++pos )
            {
                output_str << ( *pos )->Elf_Dynamic_Tag_32::to_String();
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Elf_Dynamic_Header_32::toString" );
#endif /* LIBREVERSE_DEBUG */


            return output_str.str();
        }

    } /* namespace elf_module */
} /* namespace libreverse */
