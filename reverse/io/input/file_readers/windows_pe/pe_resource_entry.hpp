/*  PE_Resource_Entry.h

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

#ifndef PE_RESOURCE_ENTRY_H_
#define PE_RESOURCE_ENTRY_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.hpp"

namespace libreverse { namespace wpef_module {

    template <boost::uint32_t size> class PE_File;

    class PE_Resource_Entry : public libreverse::header::Base_Header {
    public:

        friend class PE_File<32>;
        friend class PE_File<64>;

        typedef boost::shared_ptr <PE_Resource_Entry> ptr_t;

        /*!
         * \brief Default Constructor
         */
        PE_Resource_Entry();

        /*!
         * \brief Default Destructor
         */
        virtual ~PE_Resource_Entry(){}

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

         /* MS_PE_COFF: Characteristics Resource flags. This field is
            reserved for future use. It is currently set to zero. */
        boost::uint32_t m_name;

        /* MS_PE_COFF: Time/Date Stamp - The time that the resource data
           was created by the resource compiler. */
        boost::uint32_t m_offset_to_data;
	};
} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_RESOURCE_ENTRY_H_ */
