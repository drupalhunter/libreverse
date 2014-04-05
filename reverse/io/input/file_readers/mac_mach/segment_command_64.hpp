/*  Segment_Command_64.h

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

#ifndef SEGMENT_COMMAND_64_H
#define SEGMENT_COMMAND_64_H

#include "Load_Command.h"
#include <vector>

namespace reverse { namespace mach_module {

  class Segment_Command_64 : public Load_Command {
  public:

    friend class Mach_File;

    Segment_Command_64 ( boost::uint32_t cmd, boost::uint32_t cmdsize );

    virtual ~Segment_Command_64(){}

    virtual void convert ( bool need_convert );

    virtual std::string to_String (void);

  private:

    std::vector<boost::uint8_t> m_segname;

    boost::uint32_t m_cmd;
    boost::uint32_t m_cmdsize;
    boost::uint64_t m_vmaddr;
    boost::uint64_t m_vmsize;
    boost::uint64_t m_fileoff;
    boost::uint64_t m_filesize;
    boost::uint32_t m_maxprot;
    boost::uint32_t m_initprot;
    boost::uint32_t m_nsects;
    boost::uint32_t m_flags;
  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* SEGMENT_COMMAND_64_H */
