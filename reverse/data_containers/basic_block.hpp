/*  Basic_Block.h

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

#ifndef REVERSE_DATA_CONTAINERS_BASIC_BLOCK_HPP_INCLUDED
#define REVERSE_DATA_CONTAINERS_BASIC_BLOCK_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

namespace reverse {
  namespace data_containers {

    class instruction;

    class basic_block {
    public:

      basic_block ( boost::uint32_t id,
		    boost::uint32_t type );

      boost::uint32_t get_id () const;

      void add_line ( boost::shared_ptr<instruction> input_line );

      void add_comment ( std::string const& comment );

      std::vector< boost::shared_ptr < instruction > >::iterator begin();

      std::vector< boost::shared_ptr < instruction > >::iterator end();

      std::vector< boost::shared_ptr < instruction > >::const_iterator begin() const;

      std::vector< boost::shared_ptr < instruction > >::const_iterator end() const;
      
      std::vector< std::string >::const_iterator comments_begin () const;
      
      std::vector< std::string >::const_iterator comments_end () const;

    private:

      boost::uint32_t m_id;

      boost::uint32_t m_type;

      std::vector< boost::shared_ptr < instruction > > m_instructions;
    
      std::vector<std::string> m_comments;
    };
    
    std::ostream& operator<< ( std::ostream& os, basic_block const& rhs );

  }  // namespace data_containers
} // namespace reverse


#endif // #ifndef REVERSE_DATA_CONTAINERS_BASIC_BLOCK_HPP_INCLUDED
