/*  Elf_Note.cpp

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

#include "Elf_Note.h"
#include "io/Byte_Converter.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    void Elf_Note::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Entering Elf_Note::convert" );
#endif /* LIBREVERSE_DEBUG */


	io::Byte_Converter::convert (m_namesz);
	io::Byte_Converter::convert (m_descsz);
	io::Byte_Converter::convert (m_type);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DETAIL,
                             "Exiting Elf_Note::convert" );
#endif /* LIBREVERSE_DEBUG */

    }

} /* namespace elf_module */
} /* namespace libreverse */
