/*  ARM_POWERPC_SH_Exception_Table_Entry_64.h

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

#ifndef ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_64_H_
#define ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_64_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <boost/shared_ptr.hpp>
#include <string>
#include "PE_Exception_Table_Entry.h"
#include <boost/enable_shared_from_this.hpp>

namespace libreverse { namespace wpef_module {

    class PE_File;

    class ARM_POWERPC_SH_Exception_Table_Entry_64 : public PE_Exception_Table_Entry,
						    public boost::enable_shared_from_this < ARM_POWERPC_SH_Exception_Table_Entry_64 >
    {
    public:

      friend class PE_File;

      /*!
       * \brief Default Constructor
       */
      ARM_POWERPC_SH_Exception_Table_Entry_64();

      /*!
       * \brief Default Destructor
       */
      virtual ~ARM_POWERPC_SH_Exception_Table_Entry_64 (){}

      virtual void read_Entry ( wpef_types::PE_File::ptr_t file_ptr );

      /*!
       * \brief Convert the header data into a string representation
       * \return String representation of header data
       */
      virtual std::string to_String (void);

      /*!
       * \brief Convert the bit order of the stored data if host and data
       * endian types differ
       *
       */
      virtual void convert ();

    private:

      boost::uint32_t m_begin_address;

      boost::uint8_t m_prolog_length;

      boost::uint32_t m_function_length;

      bool m_32bit_flag;

      bool m_exception_flag;
    };
  } /* namespace wpef_module */
} /* namespace libreverse */

#endif /* ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_H_ */
