/*  PE_Header_64.h

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

#ifndef PE_HEADER_64_H_
#define PE_HEADER_64_H_

#include "PE_Types.h"

#include "io/input/File_Readers/Base_Header.h"
#include "io/IO_Types.h"

#include <string>

namespace libreverse { namespace wpef_module {

    /*!
     * \class PE_Header_64
     * \date 2003
     * \author Stephen Torri

     * Header variables names taken from
     * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/
     *        doc/pefile.html
     * Copyright 1996,1997 Johannes Plachy
     *
     * A major thanks to Johannes Plachy for such an excellent
     * description of the PE format
     */
    class PE_Header_64 : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        /* Functions */

        /*!
         * \brief Default Constructor
         */
        PE_Header_64 ();

        /*!
         * \brief Default Destructor
         */
        virtual ~PE_Header_64 (){}

        /*!
         * \brief Return the bit size of this header
         * \return Bit size of header
         */
        virtual boost::uint32_t get_size (void) const;

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void);

        /*!
         * \brief Convert the bit order of the stored data if host and data
         * endian types differ
         */
        virtual void convert ();

        bool needs_Convert ();

        bool is_PE_File (void) const;

        std::string get_File_Type (void) const;

        std::string get_Arch_Type (void) const;

        wpef_types::COFF_Header::ptr_t get_COFF_Header (void) const;

        void set_COFF_Header ( wpef_types::COFF_Header::ptr_t c_ptr );

        wpef_types::PE_Optional_Header_64::ptr_t get_Optional_Header (void) const;

        void set_Optional_Header ( wpef_types::PE_Optional_Header_64::ptr_t o_ptr );

        bool is_Valid () const;

        boost::uint32_t get_Magic_Number (void) const;

        static boost::uint16_t const PE_MAGIC_SIGNATURE;
        static boost::uint16_t const LE_MAGIC_SIGNATURE;
        static boost::uint16_t const NE_MAGIC_SIGNATURE;

    private:

        /* Data */
        boost::uint32_t p_magic;

        /* PE COFF Header */
        wpef_types::COFF_Header::ptr_t m_coff_hdr_ptr;

        /* PE Optional Header */
        wpef_types::PE_Optional_Header_64::ptr_t m_opt_hdr_ptr;

    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_HEADER_64_H_ */
