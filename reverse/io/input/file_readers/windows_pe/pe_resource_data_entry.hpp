/*  PE_Resource_Data_Entry.h

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

#ifndef PE_RESOURCE_DATA_ENTRY_H_
#define PE_RESOURCE_DATA_ENTRY_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    class PE_Resource_Data_Entry : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        /*!
         * \brief Default Constructor
         */
        PE_Resource_Data_Entry ( boost::uint8_t level );

        /*!
         * \brief Default Destructor
         */
        virtual ~PE_Resource_Data_Entry(){}

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        virtual std::string to_String (void);

        /*!
         * \brief Convert the bit order of the stored data
         */
        virtual void convert ();

        virtual boost::uint32_t get_size (void) const;

        std::string data_To_String (void) const;

    private:

        boost::uint32_t m_data_rva;

        boost::uint32_t m_size;

        boost::uint32_t m_codepage;

        boost::uint32_t m_reserved;

        boost::uint8_t m_level;

        std::string m_data_string;
	};
} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_RESOURCE_DATA_ENTRY_H_ */
