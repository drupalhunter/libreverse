/*  Dylinker_Command.h

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

#ifndef DYLINKER_COMMAND_H
#define DYLINKER_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace reverse
{
    namespace mach_module
    {

        class Dylinker_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*!
                 * \brief Default Constructor
                 *
                 * \param cmd  cmd Unsigned integer (LC_LOAD_DYLINKER or LC_ID_DYLINKER)
                 * \param cmdsize Size of this command
                 */
                Dylinker_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*!
                 * \brief Default Destructor
                 */
                virtual ~Dylinker_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Dylinker_Command
                 *
                 * \return Formatted output string of Dylinker_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_LOAD_DYLINKER or LC_ID_DYLINKER) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief The name of the dynamic linker */
                mach_types::LC_Str::ptr_t m_name;

        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* DYLINKER_COMMAND_H */
