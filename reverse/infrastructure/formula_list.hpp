/*  Formula_List.h

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

#ifndef REVERSE_INFRASTRUCTURE_FORMULA_LIST_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_FORMULA_LIST_HPP_INCLUDED

#include <string>

namespace reverse {
  namespace infrastructure {

    /*! \brief a data container for the files that compose a formula list */
    class formula_list {
    public:
      
      formula_list();

      /*! \brief input formula file name */
      std::string input;

      /*! \brief analysis formula file name */
      std::string analysis;

      /*! \brief output formula file name */
      std::string output;
    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_FORMULA_LIST_HPP_INCLUDED
