/*  Data_Directory.h

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

#ifndef WPEF_DATA_DIRECTORY_H_
#define WPEF_DATA_DIRECTORY_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "io/input/File_Readers/Base_Header.h"
#include <list>
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    class Data_Directory : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        /* Directory listing:

        0 - Export Directory
        1 - Import Directory
        2 - Resource Directory
        3 - Exception Directory
        4 - Security Directory
        5 - Base Relocation Token
        6 - Debug Directory
        7 - Architecture Specific
        8 - Global Pointer
        9 - TLS Directory
        10 - Load Config Directory
        11 - Bound Import Directory
        12 - Import Address Token
        13 - Delay Load IAT
        14 - CLR Header
        */

        Data_Directory ();

        virtual ~Data_Directory(){}

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void);

        /*!
         * \brief Convert the bit order of the stored data
         */
        virtual void convert ();

    private:

        typedef std::list< std::pair <boost::uint32_t, boost::uint32_t> >
        Directory_Type;

        static const char* m_directory_names [];

        Directory_Type m_dirs;


        /*
          MS_PE_COFF: The export table address and size.
        */
        boost::uint64_t m_export_table;

        /*
          MS_PE_COFF: The import table address and size.
        */
        boost::uint64_t m_import_table;

        /*
          MS_PE_COFF: The resource table address and size.
        */
        boost::uint64_t m_resource_table;

        /*
          MS_PE_COFF: The exception table address and size.
        */
        boost::uint64_t m_exception_table;

        /*
          MS_PE_COFF: The certificate table address and size. The
          Certificate Table entry points to a table of attribute
          certificates. These certificates are not loaded into memory as
          part of an image. As such, the first field of this entry,
          which is normally an RVA, is a file pointer instead.
        */
        boost::uint64_t m_certificate_table;

        /*
          MS_PE_COFF: The base relocation table address and size.
        */
        boost::uint64_t m_base_relocation_table;

        /*
          MS_PE_COFF: The debug data starting address and size.
        */
        boost::uint64_t m_debug;

        /*
          MS_PE_COFF: Reserved, must be 0
        */
        boost::uint64_t m_architecture;

        /*
          MS_PE_COFF: The RVA of the value to be stored in the global
          pointer register. The size member of this structure must be
          set to zero.
        */
        boost::uint64_t m_global_ptr;

        /*
          MS_PE_COFF: The thread local storage (TLS) table address and
          size.
        */
        boost::uint64_t m_tls_table;

        /*
          MS_PE_COFF: The load configuration table address and size.
        */
        boost::uint64_t m_load_config_table;

        /*
          MS_PE_COFF: The bound import table address and size.
        */
        boost::uint64_t m_bound_import;

        /*
          MS_PE_COFF: The import address table address and size.
        */
        boost::uint64_t m_import_address;

        /*
          MS_PE_COFF: The delay import descriptor address and size.
        */
        boost::uint64_t m_delay_import_descriptor;

        /*
          MS_PE_COFF: The CLR runtime header address and size.
        */
        boost::uint64_t m_clr_runtime_header;

        /*
          MS_PE_COFF: Reserved, must be 0
        */
        boost::uint64_t m_reserved;


    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* WPEF_DATA_DIRECTORY_H_ */
