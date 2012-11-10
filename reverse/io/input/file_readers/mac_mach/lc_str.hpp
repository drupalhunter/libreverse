/*  LC_Str.h

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

#ifndef LC_STR_H
#define LC_STR_H

#include <boost/cstdint.hpp>
#include <string>

namespace libreverse { namespace mach_module {

  class LC_Str {
  public:

    friend class Mach_File;

    /*! \brief Default Constructor */
    LC_Str();

    /*! \brief Default Destructor */
    virtual ~LC_Str(){}

    /*!
     * \brief Convert the byte order of the command values
     *
     * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
     */
    virtual void convert ( bool need_convert );

    /*! \brief Return a formatted string representation of the LC_Str
     *
     * \return Formatted output string of LC_Str object
     */
    std::string to_String (void);

  private:

    /*! \brief A byte offset from the start of the load command that contains this string to
     *         the start of the string data.
     */
    boost::uint32_t m_offset;

    /*! \brief String data found at offset */
    std::string m_text;

  };

} /* namespace mach_module */
} /* namespace libreverse */


#endif /* LC_STR_H */
