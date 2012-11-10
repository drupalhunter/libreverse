/*  Section_64.h

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

#ifndef SECTION_COMMAND_64_H
#define SECTION_COMMAND_64_H

#include "Load_Command.h"
#include <string>

namespace libreverse { namespace mach_module {

  class Section_64 : public Load_Command {
  public:

    Section_64 ( boost::uint32_t cmd, boost::uint32_t cmdsize );

    virtual ~Section_64(){}

    virtual void convert ( bool need_convert );

    virtual std::string to_String (void);

  private:

    std::string m_sectname;
    std::string m_segname;

    boost::uint32_t m_cmd;
    boost::uint32_t m_cmdsize;
    boost::uint64_t m_addr;
    boost::uint64_t m_size;
    boost::uint32_t m_offset;
    boost::uint32_t m_align;
    boost::uint32_t m_reloff;
    boost::uint32_t m_nreloc;
    boost::uint32_t m_flags;
    boost::uint32_t m_reserved1;
    boost::uint32_t m_reserved2;
  };

} /* namespace mach_module */
} /* namespace libreverse */


#endif /* SECTION_COMMAND_64_H */
