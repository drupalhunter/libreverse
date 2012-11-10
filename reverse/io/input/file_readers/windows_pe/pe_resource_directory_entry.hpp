/*  PE_Resource_Directory_Entry.h

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

#ifndef PE_RESOURCE_DIRECTORY_ENTRY_H_
#define PE_RESOURCE_DIRECTORY_ENTRY_H_

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

    class PE_Resource_Directory_Entry : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        //-------------------------------
        //     IDENTIFIER TYPES
        //-------------------------------
        static boost::uint8_t const NAME;
        static boost::uint8_t const ID;

        /*!
         * \brief Default Constructor
         */
        PE_Resource_Directory_Entry ( boost::uint8_t type );

        /*!
         * \brief Default Destructor
         */
        virtual ~PE_Resource_Directory_Entry(){}

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

        boost::uint32_t get_Name_Offset (void) const;

        boost::uint32_t get_Offset (void) const;

        boost::uint8_t get_Type (void) const;

        bool is_Directory_Bit_Set (void) const;

    private:

         /* MS_PE_COFF: The address of a string that gives the Type,
            Name, or Language ID entry, depending on level of table.
         */
        boost::uint32_t m_name;

        /* MS_PE_COFF: High bit = 0 => Address of a Resource Data
           entry (a leaf).  High bit = 1 ==> The lower 31 bits are the
           address of another resource directory table (the next level
           down).
        */
        boost::uint32_t m_rva;

        boost::uint8_t m_type;
	};
} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_RESOURCE_DIRECTORY_ENTRY_H_ */
