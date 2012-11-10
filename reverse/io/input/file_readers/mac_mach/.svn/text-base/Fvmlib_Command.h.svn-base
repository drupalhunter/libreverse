/*  Fvmlib_Command.h

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

#ifndef FVMLIB_COMMAND_H
#define FVMLIB_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace libreverse
{
    namespace mach_module
    {

        class Fvmlib_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*! \brief Constructor
                *  \param cmd Command ID ( LC_FVMLIB )
                *  \param cmdsize Command Size in bytes
                */
                Fvmlib_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Fvmlib_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Fvmlib_Command
                 *
                 * \return Formatted output string of Fvmlib_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_FVMFILE) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief Fvmlib object pointer */
                mach_types::Fvmlib::ptr_t m_fvmlib;

        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* FVMFILE_COMMAND_H */
