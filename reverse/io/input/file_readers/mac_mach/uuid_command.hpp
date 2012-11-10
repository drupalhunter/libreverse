/*  UUID_Command.h

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

#ifndef UUID_COMMAND_H
#define UUID_COMMAND_H

#include "Load_Command.h"
#include <vector>

namespace libreverse
{
    namespace mach_module
    {

        class UUID_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                UUID_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                virtual ~UUID_Command() {}

                virtual void convert ( bool need_convert );

                virtual std::string to_String ( void );

            private:

                static const boost::uint8_t MAX_SIZE;

                boost::uint32_t m_cmd;
                boost::uint32_t m_cmdsize;
                std::vector<boost::uint8_t> m_uuid;

        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* UUID_COMMAND_H */
