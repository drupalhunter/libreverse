/*  Basic_Block.cpp

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

#include "Basic_Block.h"
#include "Instruction.h"

#include <sstream>
#include <boost/format.hpp>

#include "errors/Internal_Exception.h"
#include "io/Preconditions.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace data_container {

    Basic_Block::Basic_Block ( boost::uint32_t id,
			       boost::uint32_t type )
      : m_id ( id ),
	m_type ( type )
    {}

    boost::uint32_t
    Basic_Block::get_ID () const
    {
      return m_id;
    }

    void
    Basic_Block::add_Line ( data_types::Instruction::ptr_t input_line )
    {
      io::Preconditions::is_set ( input_line );
      io::Preconditions::equals ( input_line->get_Type(), m_type );

      m_instructions.push_back ( input_line );
    }

    void
    Basic_Block::add_Comment ( std::string comment )
    {
      io::Preconditions::not_empty ( comment );

      m_comments.push_back ( comment );
    }

    data_types::Basic_Block::DataList_t::iterator
    Basic_Block::begin()
    {
      return m_instructions.begin();
    }


    data_types::Basic_Block::DataList_t::iterator
    Basic_Block::end()
    {
      return m_instructions.end();
    }

    data_types::Basic_Block::DataList_t::const_iterator
    Basic_Block::begin() const
    {
      return m_instructions.begin();
    }


    data_types::Basic_Block::DataList_t::const_iterator
    Basic_Block::end() const
    {
      return m_instructions.end();
    }

    std::string
    Basic_Block::to_String (void) const
    {
      std::stringstream output;

      output << "-----------------" << std::endl
	     << boost::format ( "Basic Block (%1%)" ) % m_id << std::endl
	     << "-----------------" << std::endl << std::endl
	     << "  Comments" << std::endl
	     << "  --------" << std::endl;

      for ( std::vector<std::string>::const_iterator cpos = m_comments.begin();
	    cpos != m_comments.end();
	    ++cpos )
	{
	  output << boost::format ( "  %1%" ) % (*cpos) << std::endl;
	}

      output << "  --------" << std::endl
	     << "    Code" << std::endl
	     << "  --------" << std::endl;

      for ( data_types::Basic_Block::DataList_t::const_iterator cpos = m_instructions.begin();
	    cpos != m_instructions.end();
	    ++cpos )
	{
	  output << boost::format ("  %1%" ) % (*cpos)->to_String() << std::endl;
	}

      return output.str();
    }

  }  /* namespace data_types */
} /* namespace libreverse */

