/*  Prebound_Dylib_Command.h

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

#ifndef PREBOUND_DYLIB_COMMAND_H
#define PREBOUND_DYLIB_COMMAND_H

#include "Load_Command.h"
#include "Mach_Types.h"

namespace libreverse
{
    namespace mach_module
    {

        class Prebound_Dylib_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*!
                 * \brief Default Constructor
                 *
                 * \param cmd  cmd Unsigned integer (LC_LOAD_DYLINKER or LC_ID_DYLINKER)
                 * \param cmdsize Size of this command
                 */
                Prebound_Dylib_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Destructor */
                virtual ~Prebound_Dylib_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Prebound_Dylib_Command
                 *
                 * \return Formatted output string of Prebound_Dylib_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Command id (LC_PREBOUND_DYLIB) */
                boost::uint32_t m_cmd;

                /*! \brief Size of this command */
                boost::uint32_t m_cmdsize;

                /*! \brief The name of the prebound shared library */
                mach_types::LC_Str::ptr_t m_name;

                /*! \brief An integer. Specifies the number of modules the prebound shared library contains. The size
                 *         of the linked_modules string is (nmodules / 8) + (nmodules % 8).
                 */
                boost::uint32_t m_nmodules;

                /*! \brief A data structure of type lc_str (page 31). Usually, this data structure defines the offset of a
                 *         C string; in this usage, it is a variable-length bitset, containing one bit for each module. Each
                 *         bit represents whether the corresponding module is linked to a module in the current file, 1
                 *         for yes, 0 for no. The bit for the first module is the low bit of the first byte.
                 */
                mach_types::LC_Str::ptr_t m_linked_modules;

        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* PREBOUND_DYLIB_COMMAND_H */
