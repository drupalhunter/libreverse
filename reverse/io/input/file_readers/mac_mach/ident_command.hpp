/*  Ident_Command.h

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

#ifndef IDENT_COMMAND_H
#define IDENT_COMMAND_H

#include "Load_Command.h"
#include <vector>

namespace libreverse
{
    namespace mach_module
    {

        class Ident_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*! \brief Constructor
                 *  \param cmd Command ID ( LC_IDENT )
                 *  \param cmdsize Command Size in bytes
                 */
                Ident_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Ident_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Ident_Command
                 *
                 * \return Formatted output string of Ident_Command object
                 */
                virtual std::string to_String ( void );

            private:
                boost::uint32_t m_cmd;
                boost::uint32_t m_cmdsize;
        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* IDENT_COMMAND_H */
