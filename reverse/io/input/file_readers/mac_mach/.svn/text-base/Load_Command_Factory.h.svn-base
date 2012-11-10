/*  Load_Command_Factory.h

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

#ifndef LOAD_COMMAND_FACTORY_H
#define LOAD_COMMAND_FACTORY_H

#include "Mach_File.h"

namespace libreverse
{
    namespace mach_module
    {
        class Load_Command_Factory
        {
            public:

                /*! \brief Create a Load_Command object.
                 *  \param m_file Mach File from where the Load_Command object will be read.
                 *  \param cputype CPU type associated with this Mach file.
                 *  \param convert Boolean check to see if it is necessary to convert the Load_Command fields
                 *                 when reading it from the file.
                 *  \return The pointer to the appropriate Load_Command object
                 */
                static mach_types::Load_Command::ptr_t create ( Mach_File& m_file,
                        boost::uint32_t cputype,
                        bool convert );

                /*! \brief Create a CPU_Thread_State object
                 *  \param m_file Mach_File from where the CPU_Thread_State will be read.
                 *  \param thread_ptr Thread Command object where the CPU_Thread_State will be saved.
                 *  \param cputype CPU type associated with this Mach file.
                 */
                static void
                create_CPU_Thread_State ( Mach_File& m_file,
                                          mach_types::Thread_Command::ptr_t thread_ptr,
                                          boost::uint32_t cputype );
        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* LOAD_COMMAND_FACTORY_H */
