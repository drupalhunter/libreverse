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

#include <reverse/components/input/grnn/grnn_data_types.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	grnn_data_types::value_type
	grnn_data_types::get_type ( std::string const& type_string )
	{
	  preconditions::not_empty ( type_string );

	  grnn_data_types::value_type result = grnn_data_types::unknown;
      
	  if ( type_string.compare ( "java_class" ) == 0 )
	    {
	      result = grnn_data_types::java_class;
	    }
	  else if ( type_string.compare ( "windows_pe" ) == 0 )
	    {
	      result = grnn_data_types::windows_pe;
	    }
	  else if ( type_string.compare ( "linux_elf" ) == 0 )
	    {
	      result = grnn_data_types::linux_elf;
	    }
	  else if ( type_string.compare ( "mac_mach_o" ) == 0 )
	    {
	      result = grnn_data_types::mac_mach_o;
	    }
	  else
	    {
	      trace::write_trace ( trace_area::infrastructure,
				   trace_level::error,
				   boost::str ( boost::format ( "GRNN_Data_Types::get_Types - unknown type. %1%" ) % type_string ) );

	      trace::write_trace ( trace_area::infrastructure,
				   trace_level::error,
				   boost::str ( boost::format("Exception throw in %s at line %d")
						% __FILE__
						% __LINE__ ) );

	      throw errors::internal_exception ( errors::internal_exception::invalid_value );
	    }

	  return result;
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

