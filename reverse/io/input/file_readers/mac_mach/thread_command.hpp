/*  Thread_Command.h

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

#ifndef THREAD_COMMAND_H
#define THREAD_COMMAND_H

#include "Load_Command.h"
#include <vector>
#include "Mach_Types.h"
#include "Mach_File.h"
#include "CPU_Thread_State.h"
#include <string>

namespace libreverse { namespace mach_module {

  class Thread_Command : public Load_Command {
  public:

    friend class Mach_File;

    Thread_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

    void add_CPU_State ( mach_types::CPU_Thread_State::ptr_t cpu );

    virtual void convert ( bool need_convert );

    virtual std::string to_String (void);

  private:

    boost::uint32_t m_cmd;
    boost::uint32_t m_cmdsize;
    boost::uint32_t m_flavor;
    boost::uint32_t m_count;
    mach_types::CPU_Thread_State::ptr_t m_cpu;

  };

} /* namespace mach_module */
} /* namespace libreverse */


#endif /* DYLIB_COMMAND_H */
