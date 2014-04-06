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

#include <reverse/trace.hpp>
#include <reverse/infrastructure/formula_list.hpp>

namespace reverse {
  namespace infrastructure {

	formula_list::formula_list()
		: input (""),
		  analysis (""),
		  output ("")
	{
	  trace::infrastructure_detail( "Entering Formula_List constructor" );
	}
  
  } /* namespace infrastructure */
} /* namespace reverse */
