/*  basic_block.cpp

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

#include <reverse/data_containers/basic_block.hpp>
#include <reverse/data_containers/instruction.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>

namespace reverse {
    namespace data_containers {

        basic_block::basic_block ( boost::uint32_t id,
                                   boost::uint32_t type )
            : m_id ( id ),
              m_type ( type )
        {}

        boost::uint32_t
        basic_block::get_id () const
        {
            return m_id;
        }

        void
        basic_block::add_line ( boost::shared_ptr<instruction> input_line )
        {
            reverse::preconditions::is_set ( input_line );
            reverse::preconditions::equals ( input_line->get_type(), m_type );

            m_instructions.push_back ( input_line );
        }

        void
        basic_block::add_comment ( std::string const& comment )
        {
            reverse::preconditions::not_empty ( comment );

            m_comments.push_back ( comment );
        }

        std::vector< boost::shared_ptr < instruction > >::iterator
        basic_block::begin()
        {
            return m_instructions.begin();
        }


        std::vector< boost::shared_ptr < instruction > >::iterator
        basic_block::end()
        {
            return m_instructions.end();
        }

        std::vector< boost::shared_ptr < instruction > >::const_iterator
        basic_block::begin() const
        {
            return m_instructions.begin();
        }


        std::vector< boost::shared_ptr < instruction > >::const_iterator
        basic_block::end() const
        {
            return m_instructions.end();
        }
              
        std::vector< std::string >::const_iterator basic_block::comments_begin() const
        {
	    return m_comments.begin();
        }
    
        std::vector< std::string >::const_iterator basic_block::comments_end() const
        {
	    return m_comments.end();
        }

        
        std::ostream& operator<< ( std::ostream& os, basic_block const& rhs )
        {
            os << "-----------------" << std::endl
               << boost::format ( "Basic Block (%1%)" ) % rhs.get_id() << std::endl
               << "-----------------" << std::endl << std::endl
               << "  Comments" << std::endl
               << "  --------" << std::endl;

            for ( std::vector<std::string>::const_iterator cpos = rhs.comments_begin();
                    cpos != rhs.comments_end();
                    ++cpos ) {
                os << boost::format ( "  %1%" ) % ( *cpos ) << std::endl;
            }

            os << "  --------" << std::endl
               << "    Code" << std::endl
               << "  --------" << std::endl;

            for ( std::vector< boost::shared_ptr < instruction > >::const_iterator cpos = rhs.begin();
                    cpos != rhs.end();
                    ++cpos ) {
                os << boost::format ( "  %1%" ) % *cpos << std::endl;
            }

            return os;
        }

    }  /* namespace data_containers */
} /* namespace reverse */

