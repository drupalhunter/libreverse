/*  java_assembly_instruction.h

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

#include <reverse/data_containers/java_assembly_instruction.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
  namespace data_containers {
    
    const boost::uint32_t java_assembly_instruction::type = instruction::java_assembly;
    
    java_assembly_instruction::java_assembly_instruction ( boost::uint32_t index, std::string input )
      : m_index ( index ),
	m_code ( input )
    {
      trace::data_containers_detail( "Inside java_assembly_instruction constructor" );
    }

    boost::uint32_t
    java_assembly_instruction::get_type ( void ) const
    {
      trace::data_containers_detail( "Inside java_assembly_instruction::get_Type" );

      return type;
    }
    
        boost::uint32_t java_assembly_instruction::get_index() const
        {
	  return m_index;
        }

    
        const std::string& java_assembly_instruction::get_code() const
        {
	  return m_code;
        }


    std::ostream& operator<< ( std::ostream& os, java_assembly_instruction const& rhs )
    {
      trace::data_containers_detail("Entering java_assembly_instruction::to_String" );

      os << boost::format ( "%1%: %2%" )
	% rhs.get_index()
	% rhs.get_code();

      trace::data_containers_detail( "Exiting java_assembly_instruction::to_String" );

      return os;
    }

  }  /* namespace data_container */
} /* namespace reverse */
