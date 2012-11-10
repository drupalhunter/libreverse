/*  Dylib_Command.h

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

#ifndef DYLIB_COMMAND_H
#define DYLIB_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace libreverse
{
    namespace mach_module
    {

        class Dylib_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*!
                 * \brief Defaut Constructor
                 *
                 * \param cmd Unsigned integer (LC_LOAD_DYLIB or LC_ID_DYLIB)
                 * \param cmdsize Size of this command
                 */
                Dylib_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Dylib_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Dylib_Command
                 *
                 * \return Formatted output string of Dylib_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_LOAD_DYLIB or LC_ID_DYLIB) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief Specifies attributes of the shared library */
                mach_types::Dylib::ptr_t m_dylib;

        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* DYLIB_COMMAND_H */
