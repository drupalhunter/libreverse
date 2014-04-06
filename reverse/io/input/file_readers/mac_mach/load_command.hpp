/*  Load_Command.h

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

#ifndef LOAD_COMMAND_H
#define LOAD_COMMAND_H

#include <boost/cstdint.hpp>
#include <string>

namespace reverse
{
    namespace mach_module
    {

        class Load_Command
        {
            protected:

                static const boost::uint8_t MAX_NAME_SIZE;

                virtual ~Load_Command() {}

            public:

                virtual void convert ( bool value ) = 0;

                virtual std::string to_String ( void ) = 0;
        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* LOAD_COMMAND_H */
