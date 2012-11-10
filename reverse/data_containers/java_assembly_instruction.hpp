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

#ifndef REVERSE_DATA_CONTAINER_JAVA_ASSEMBLY_INSTRUCTION_HPP_INCLUDED
#define REVERSE_DATA_CONTAINER_JAVA_ASSEMBLY_INSTRUCTION_HPP_INCLUDED

#include <reverse/data_containers/instruction.hpp>

#include <boost/cstdint.hpp>
#include <string>

namespace reverse {
  namespace data_container {

    class java_assembly_instruction : public instruction {
    public:

      java_assembly_instruction ( boost::uint32_t index, std::string );

      virtual ~java_assembly_instruction(){}

      virtual boost::uint32_t get_type ( void ) const;

      virtual std::string to_string ( void ) const;

      /*----------------------------*/
      /*         VARIABLES          */
      /*----------------------------*/
      static const boost::uint32_t type;

      boost::uint32_t m_index;

      std::string m_code;

    };

  }  // namespace data_container
} // namespace reverse


#endif /* REVERSE_DATA_CONTAINER_JAVA_ASSEMBLY_INSTRUCTION_HPP_INCLUDED */
