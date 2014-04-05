/*  Dylib.h

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

#ifndef DYLIB_H
#define DYLIB_H

#include <boost/cstdint.hpp>
#include <string>

#include "Mach_Types.h"

namespace reverse
{
    namespace mach_module
    {

        class Dylib
        {
            public:

                friend class Mach_File;

                /*! \brief Default Constructor */
                Dylib();

                /*! \brief Default Destructor */
                virtual ~Dylib() {}


                /*!
                 * \brief Convert the byte order of the Dylib object values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the CPU state
                 *
                 * \return Formatted output string of CPU state
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Name of the shared library */
                mach_types::LC_Str::ptr_t m_name;

                /*! \brief The date and time when the shared library was built */
                boost::uint32_t m_timestamp;

                /*! \brief The current version of the shared library */
                boost::uint32_t m_current_version;

                /*! \brief The compatibility version of the shared library */
                boost::uint32_t m_compatibility_version;

        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* DYLIB_H */
