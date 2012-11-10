/*  Java_Assembly_Instruction.h

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

#include <reverse/data_container/Java_Assembly_Instruction.h>

#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Trace.h>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace data_container {
    
    const boost::uint32_t Java_Assembly_Instruction::TYPE = Instruction::JAVA_ASSEMBLY;
    
    Java_Assembly_Instruction::Java_Assembly_Instruction ( boost::uint32_t index, std::string input )
      : m_index ( index ),
	m_code ( input )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DETAIL,
			   "Inside Java_Assembly_Instruction constructor" );
#endif /* LIBREVERSE_DEBUG */
    }

    boost::uint32_t
    Java_Assembly_Instruction::get_Type ( void ) const
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DETAIL,
			   "Inside Java_Assembly_Instruction::get_Type" );
#endif /* LIBREVERSE_DEBUG */

      return TYPE;
    }

    std::string
    Java_Assembly_Instruction::to_String ( void ) const
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DETAIL,
			   "Entering Java_Assembly_Instruction::to_String" );
#endif /* LIBREVERSE_DEBUG */

      std::string result = boost::str ( boost::format ( "%1%: %2%" ) % m_index % m_code );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::DATA_CONTAINERS,
			   TraceLevel::DETAIL,
			   "Exiting Java_Assembly_Instruction::to_String" );
#endif /* LIBREVERSE_DEBUG */

      return result;
    }

  }  /* namespace data_container */
} /* namespace reverse */
