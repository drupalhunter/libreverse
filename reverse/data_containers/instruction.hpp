/*  Instruction.h

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

#ifndef REVERSE_DATA_CONTAINERS_INSTRUCTION_HPP_INCLUDED
#define REVERSE_DATA_CONTAINERS_INSTRUCTION_HPP_INCLUDED

#include <boost/cstdint.hpp>

#include <string>

namespace reverse {
  namespace data_containers {

    class instruction {
    public:

      enum instruction_types {
	x86_assembly,
	java_assembly
      };
    
      virtual ~instruction(){}

      virtual boost::uint32_t get_type ( void ) const = 0;

    };

  }  /* namespace data_containers */
} /* namespace reverse */


#endif // #ifndef REVERSE_DATA_CONTAINERS_INSTRUCTION_HPP_INCLUDED
