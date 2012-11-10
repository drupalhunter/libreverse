/*  DOS_Relocation_Header.h

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

#ifndef WPEF_DOS_RELOCATION_HEADER_H_
#define WPEF_DOS_RELOCATION_HEADER_H_

#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include <boost/shared_ptr.hpp>

namespace libreverse { namespace wpef_module {

    /*!
     * \class WPEF_DOS_RELOCATION_Header
     * \date 2003
     * \author Stephen Torri

     * Header variables names taken from
     * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/doc/pefile.html
     * Copyright 1996,1997 Johannes Plachy
     *
     * A major thanks to Johannes Plachy for such an excellent description of the PE format
     */

    class DOS_Relocation_Header : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        typedef boost::shared_ptr< DOS_Relocation_Header > ptr_t;

        /* Functions */

        /*!
         * \brief Default Constructor
         */
        DOS_Relocation_Header();

        /*!
         * \brief Default Destructor
         */
        virtual ~DOS_Relocation_Header(){}

        /*!
         * \brief Return the bit size of this header
         * \return Bit size of header
         */
        virtual boost::uint32_t const get_size (void);

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void);

        /*!
         * \brief Convert the bit order of the stored data
         */
        virtual void convert ();


        /* Data */

        boost::uint16_t m_offset;

        boost::uint16_t m_segment;

    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* WPEF_DOS_RELOCATION_HEADER_H_ */
