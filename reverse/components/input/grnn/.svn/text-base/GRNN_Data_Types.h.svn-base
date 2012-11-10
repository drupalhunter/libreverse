/*  GRNN_Data_Types.h

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

#ifndef GRNN_DATA_TYPES_H
#define GRNN_DATA_TYPES_H

#include <string>

namespace libreverse
{

  namespace classifier
  {
    class GRNN_Data_Types {
    public:

      enum Value_Type {
	JAVA_CLASS,
	WINDOWS_PE,
	LINUX_ELF,
	MAC_MACH_O,
	UNKNOWN
      };

      /*!
       * \brief Return the numerical value of the type string
       * \return Unsigned integer representing the type string
       * \pre type string is not empty
       */
      static Value_Type get_Type ( std::string type_string );

    };

  } /* namespace classifier */

} /* namespace libreverse */

#endif /* GRNN_DATA_MAP_H */
