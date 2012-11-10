/*  GRNN_Data_Types.cpp

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

#include "GRNN_Data_Types.h"
#include "io/Preconditions.h"
#include "Trace.h"

#include <boost/format.hpp>

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse
{

  namespace classifier
  {

    GRNN_Data_Types::Value_Type
    GRNN_Data_Types::get_Type ( std::string type_string )
    {
      io::Preconditions::not_empty ( type_string );

      GRNN_Data_Types::Value_Type result = GRNN_Data_Types::UNKNOWN;
      
      if ( type_string.compare ( "java_class" ) == 0 )
	{
	  result = GRNN_Data_Types::JAVA_CLASS;
	}
      else if ( type_string.compare ( "windows_pe" ) == 0 )
	{
	  result = GRNN_Data_Types::WINDOWS_PE;
	}
      else if ( type_string.compare ( "linux_elf" ) == 0 )
	{
	  result = GRNN_Data_Types::LINUX_ELF;
	}
      else if ( type_string.compare ( "mac_mach_o" ) == 0 )
	{
	  result = GRNN_Data_Types::MAC_MACH_O;
	}
      else
	{
	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::ERROR,
			       boost::str ( boost::format ( "GRNN_Data_Types::get_Types - unknown type. %1%" ) % type_string ) );

	  Trace::write_Trace ( TraceArea::INFRASTRUCTURE,
			       TraceLevel::ERROR,
			       boost::str ( boost::format("Exception throw in %s at line %d")
					    % __FILE__
					    % __LINE__ ) );

	  throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
	}

      return result;
    }

  } /* namespace classifier */

} /* namespace libreverse */
