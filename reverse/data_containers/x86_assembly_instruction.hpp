/*  X86_Assembly_Instruction.h

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

#ifndef X86_ASSEMBLY_INSTRUCTION_H
#define X86_ASSEMBLY_INSTRUCTION_H

#include <string>

namespace reverse { namespace data_container {

  class X86_Assembly_Instruction {
  public:

    virtual X86_Assembly_Instruction_Types get_Type ( void ) const;

    virtual std::string to_String ( void ) const;

    void add_Code ( std::string );

    /*----------------------------*/
    /*         VARIABLES          */
    /*----------------------------*/
    static Instruction_Types TYPE;

    std::string m_code;

  };

}  /* namespace data_container */
} /* namespace reverse */


#endif /* X86_ASSEMBLY_INSTRUCTION_H */
