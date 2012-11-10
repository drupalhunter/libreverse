/*  Dylib_Table_Of_Contents.h

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

#ifndef DYLIB_TABLE_OF_CONTENTS_H
#define DYLIB_TABLE_OF_CONTENTS_H

#include <boost/cstdint.hpp>

namespace libreverse
{
    namespace mach_module
    {

        class Dylib_Table_Of_Contents
        {
            public:

                /*! \brief Default Constructor */
                Dylib_Table_Of_Contents();

            private:

                /*! \brief An index into the symbol table indicating the defined external symbol to which this entry
                 *         refers.
                 */
                boost::uint32_t m_symbol_index;

                /*! \brief An index into the module table indicating the module in which this defined external symbol
                 *         is defined.
                 */
                boost::uint32_t m_module_index;

        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* DYLIB_TABLE_OF_CONTENTS_H */
