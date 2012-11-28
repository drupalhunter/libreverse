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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_TYPES_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_TYPES_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class grnn_data_types {
	public:

	  enum value_type {
	    java_class,
	    windows_pe,
	    linux_elf,
	    mac_mach_o,
	    unknown
	  };

	  /*!
	   * \brief Return the numerical value of the type string
	   * \return Unsigned integer representing the type string
	   * \pre type string is not empty
	   */
	  static value_type get_type ( std::string const& type_string );

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_TYPES_HPP_INCLUDED
