/*  DOS_Header.h

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

#ifndef WPEF_DOS_HEADER_H_
#define WPEF_DOS_HEADER_H_

#include <string>
#include <vector>
#include "io/input/File_Readers/Base_Header.h"
#include "io/IO_Types.h"
#include "PE_Types.h"
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

namespace libreverse { namespace wpef_module {

    /*!
     * \class DOS_Header
     * \date 2003
     * \author Stephen Torri

     * Header variables names taken from
     * http://www.csn.ul.ie/~caolan/publink/winresdump/winresdump/doc/pefile.html
     * Copyright 1996,1997 Johannes Plachy
     *
     * A major thanks to Johannes Plachy for such an excellent description of the PE format
     */
    class DOS_Header : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        static boost::uint8_t const RES_SIZE = 4;
        static boost::uint8_t const RES2_SIZE = 26;

        /* Functions */

        /*!
         * \brief Default Constructor
         */
        DOS_Header();

        /*!
         * \brief Default Destructor
         */
        virtual ~DOS_Header(){}

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        std::string to_String (void);

        /*!
         * \brief Convert the bit order of the stored data
         */
        virtual void convert ();

        bool needs_Convert ();

        bool is_DOS_File (void) const;

        bool has_PE_Header (void) const;

        std::string get_File_Type (void) const;

        std::string get_Arch_Type (void) const;

        /* Returns the relocation information
           first value: Number of relocations
           second value: Offset position where relocation entries begin
        */
        std::pair<boost::uint16_t,boost::uint16_t> get_Relocation_Info (void) const;

        void add_Reloc_Hdr ( wpef_types::DOS_Relocation_Header::ptr_t obj );

        boost::uint32_t get_PE_Offset (void) const;

        boost::uint16_t get_Magic_Number (void) const;

        boost::uint16_t get_Size_Of_Last_Page (void) const;

        boost::uint16_t get_Page_Total (void) const;

        boost::uint16_t get_Number_Of_Relocations (void) const;

        boost::uint16_t get_Header_Size (void) const;

        boost::uint16_t get_Minimum_Alloc (void) const;

        boost::uint16_t get_Maximum_Alloc (void) const;

        boost::uint16_t get_Initial_SS (void) const;

        boost::uint16_t get_Initial_SP (void) const;

        boost::uint16_t get_Checksum (void) const;

        boost::uint16_t get_IP_Value (void) const;

        boost::uint16_t get_Initial_CS (void) const;

        boost::uint16_t get_File_Address (void) const;

        boost::uint16_t get_Overlay_Number (void) const;

        boost::uint8_t const* get_Reserved_Word (void) const;

        boost::uint16_t get_Behavior_Bits (void) const;

        boost::uint8_t const* get_Reserved_Word2 (void) const;

        boost::uint32_t get_EXE_Header_Address (void) const;

        static boost::uint16_t const DOS_MAGIC_SIGNATURE;

    private:

        /* Data */

        /*! \brief  WPEF "magic number".
         *
         * The initial bytes mark the file as an object file and provide
         * machine-indepenedent data with which to decode and interpret the
         * file's contents.[WPEF Format]
         */


        /* Typically these values are 'ZM' or 'MZ' */
        boost::uint16_t e_magic;

        // Number of bytes in last 512-byte page of executable
        boost::uint16_t e_cblp;

        // Total number of 512-byte pages in executable (includes and
        // partial last page
        boost::uint16_t e_cp;

        // Number of relocation entries
        boost::uint16_t e_crlc;

        // Header size in paragraphs
        boost::uint16_t e_cparhdr;

        // Minimum paragraphs of memory required to allocate in
        // addition to the executable's size
        boost::uint16_t e_minalloc;

        // Mimum paragraphs of memory required to allocate in addition
        // to the executable's size
        boost::uint16_t e_maxalloc;

        boost::uint16_t e_ss;            // Initial (relative) SS value

        boost::uint16_t e_sp;            // Initial SP value

        boost::uint16_t e_csum;          // Checksum

        boost::uint16_t e_ip;            // Initial IP value

        boost::uint16_t e_cs;            // Initial (relative) CS value

        boost::uint16_t e_lfarlc;        // File address of relocation table

        boost::uint16_t e_ovno;          // Overlay number

        boost::uint8_t e_res[RES_SIZE]; // Reserved words

        boost::uint16_t e_behavior_bits;

        boost::uint8_t e_res2[RES2_SIZE]; // Reserved words

        boost::uint32_t e_lfanew;        // File address of new exe header

        typedef std::vector< wpef_types::DOS_Relocation_Header::ptr_t > List_t;
        List_t m_relocs;
    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* WPEF_DOS_HEADER_H_ */
