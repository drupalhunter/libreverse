/*  Routines_Command_64.h

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

#ifndef ROUTINES_COMMAND_64_H
#define ROUTINES_COMMAND_64_H

#include "Load_Command.h"

namespace reverse
{
    namespace mach_module
    {

        class Routines_Command_64 : public Load_Command
        {
            public:

                friend class Mach_File;

                /*!
                 * \brief Default Constructor
                 *
                 * \param cmd  cmd Unsigned integer (LC_ROUTINES_64)
                 * \param cmdsize Size of this command
                 */
                Routines_Command_64 ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Routines_Command_64() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Routines_Command_64
                 *
                 * \return Formatted output string of Routines_Command_64 object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_ROUTINES_64) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief An integer specifying the virtual memory address of the initialization function. */
                boost::uint64_t m_init_address;

                /*! \brief An integer specifying the index into the module table of the module containing the initialization
                 *         function.
                 */
                boost::uint64_t m_init_module;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved1;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved2;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved3;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved4;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved5;

                /*! \brief Reserved for future use. Set this field to 0. */
                boost::uint64_t m_reserved6;
        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* DYLIB_COMMAND_64_H */
