/*  Fvmfile_Command.h

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

#ifndef FVMFILE_COMMAND_H
#define FVMFILE_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace reverse
{
    namespace mach_module
    {

        /* This is not documented in the latest Mach-O documentation. The sizes were a guess from
           unofficial information found online. */
        class Fvmfile_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*! \brief Constructor
                 *  \param cmd Command ID ( LC_FVMFILE )
                 *  \param cmdsize Command Size in bytes
                 */
                Fvmfile_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Fvmfile_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Fvmfile_Command
                 *
                 * \return Formatted output string of Fvmfile_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_FVMFILE) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief The name of the file */
                mach_types::LC_Str::ptr_t m_name;

                /*! \brief Header address */
                boost::uint32_t m_header_addr;

        };

    } /* namespace mach_module */
} /* namespace filereverse */


#endif /* FVMFILE_COMMAND_H */
