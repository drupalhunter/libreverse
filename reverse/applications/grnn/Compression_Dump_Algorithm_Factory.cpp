/* Compression_Dump_Algorithm_Factory.cpp

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
#include "Compression_Dump_Algorithm_Factory.h"
#include "Windows_Compression_Dump_Algorithm.h"

#include "reverse/errors/Internal_Exception.h"

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace optimizer {

    Compression_Dump_Algorithm_Factory&
    Compression_Dump_Algorithm_Factory::Instance()
    {
      static Compression_Dump_Algorithm_Factory fact_ref;
      return fact_ref;
    }

    optimizer_types::Compression_Dump_Algorithm::ptr_t
    Compression_Dump_Algorithm_Factory::get_Algorithm ( classifier::GRNN_Data_Types::Value_Type type )
    {
      switch ( type )
	{
	case classifier::GRNN_Data_Types::WINDOWS_PE:
	  {
	    optimizer_types::Windows_Compression_Dump_Algorithm::ptr_t obj_ptr ( new Windows_Compression_Dump_Algorithm() );
	    return obj_ptr;
	  }
	default:
	  {

#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				 TraceLevel::ERROR,
				 boost::str ( boost::format ( "GRNN_Data_Types::get_Types - unknown type. %1%" ) % type ) );
	    
	    Trace::write_Trace ( TraceArea::GRNN_OPTIMIZER,
				 TraceLevel::ERROR,
				 boost::str ( boost::format("Exception throw in %s at line %d")
					      % __FILE__
					      % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

	    throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
	  }
	}
    }

  } /* namespace optimizer */
} /* namespace reverse */


