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

#ifndef GRNN_DATA_ENTRY_H
#define GRNN_DATA_ENTRY_H

#include <string>

namespace libreverse
{

  namespace classifier
  {
    class GRNN_Data_Entry {
    public:

      GRNN_Data_Entry ( double sigma, std::string file );

      /*!
       * \return stored sigma value
       * \pre sigma is not zero
       */
      double get_Sigma ( void ) const;

      /*!
       * \return stored filename
       * \pre filename is not empty
       */
      std::string get_Filename ( void ) const;

    private:

      double m_sigma;

      std::string m_file;
    };

  } /* namespace classifier */

} /* namespace libreverse */

#endif /* GRNN_DATA_ENTRY_H */
