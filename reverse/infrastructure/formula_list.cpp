/*  Formula_List.cpp

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

#include "Formula_List.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace libreverse { namespace infrastructure {

	Formula_List::Formula_List()
		: input (""),
		  analysis (""),
		  output ("")
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::DETAIL,
			       "Entering Formula_List constructor" );
#endif /* LIBREVERSE_DEBUG */

	}

} /* namespace infrastructure */
} /* namespace libreverse */
