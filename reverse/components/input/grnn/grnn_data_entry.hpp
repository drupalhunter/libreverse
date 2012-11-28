
/*  GRNN_Data_Entry.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_ENTRY_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_ENTRY_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class grnn_data_entry {
	public:

	  grnn_data_entry ( double sigma, std::string file );

	  /*!
	   * \return stored sigma value
	   * \pre sigma is not zero
	   */
	  double get_sigma ( void ) const;

	  /*!
	   * \return stored filename
	   * \pre filename is not empty
	   */
	  std::string get_filename ( void ) const;

	private:

	  double m_sigma;

	  std::string m_file;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_GRNN_DATA_ENTRY_HPP_INCLUDED
