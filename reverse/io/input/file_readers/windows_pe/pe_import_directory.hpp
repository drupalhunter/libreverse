/*  PE_Import_Directory.h

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

#ifndef IMPORT_DIRECTORY_H_
#define IMPORT_DIRECTORY_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include <list>
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    class PE_Import_Directory : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        PE_Import_Directory ();

        virtual ~PE_Import_Directory(){}

        /*!
         * \brief Return the bit size of this header
         * \return Bit size of header
         */
        virtual boost::uint32_t get_size (void) const;

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void) const;

        /*!
         * \brief Convert the bit order of the stored data
         */
        virtual void convert ();

        void set_DLL_Name ( std::string name );

        void add_Function_Name ( boost::uint16_t hint, std::string name );

        void add_Ordinal ( boost::uint32_t val );

        boost::uint32_t get_Name_RVA (void) const;

        boost::uint32_t get_Import_Lookup_Table (void) const;

        boost::uint32_t get_Import_Address_Table (void) const;

        boost::uint32_t get_Timestamp (void) const;

        boost::uint32_t get_Forwarder_Chain (void) const;

        bool const is_Null (void) const;

    private:

        /*
          MS_PE_COFF: The RVA of the import lookup table. This table
          contains a name or ordinal for each import. (The name
          "Characteristics" is used in Winnt.h, but no longer
          describes this field.)
        */
        boost::uint32_t m_import_lookup_table;

        /*
          MS_PE_COFF: The stamp that is set to zero until the image is
          bound. After the image is bound, this field is set to the
          time/data stamp of the DLL.
        */
        boost::uint32_t m_timestamp;

        /*
          MS_PE_COFF: The index of the first forwarder reference.
		*/
        boost::uint32_t m_forwarder_chain;

        /*
          MS_PE_COFF: The address of an ASCII string that contains the
          name of the DLL. This address is relative to the image base.
        */
        boost::uint32_t m_name_rva;

        /*
          MS_PE_COFF: The RVA of the import address table. The
          contents of this table are identical to the contents of the
          import lookup table until the image is bound.
        */
        boost::uint32_t m_import_address_table;

        std::string m_name;

        typedef std::list< std::pair<boost::uint16_t,std::string > > DLL_List_t;
        DLL_List_t m_import_dll_list;

        typedef std::list<boost::uint32_t> Ordinal_List_t;
        Ordinal_List_t m_ordinal_list;
    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* IMPORT_DIRECTORY_H_ */
