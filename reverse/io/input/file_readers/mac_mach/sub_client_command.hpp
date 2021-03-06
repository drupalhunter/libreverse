/*  Sub_Client_Command.h

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

#ifndef SUB_CLIENT_COMMAND_H
#define SUB_CLIENT_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace reverse { namespace mach_module {

  class Sub_Client_Command : public Load_Command {
  public:

    friend class Mach_File;

    Sub_Client_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

    virtual ~Sub_Client_Command(){}

    virtual void convert ( bool need_convert );

    virtual std::string to_String (void);

  private:

    boost::uint32_t m_cmd;
    boost::uint32_t m_cmdsize;
    mach_types::LC_Str::ptr_t m_client;

  };

} /* namespace mach_module */
} /* namespace reverse */


#endif /* SUB_CLIENT_COMMAND_H */
