/*  AMD_IA_64_Exception_Table_Entry.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_AMD_IA_64_EXCEPTION_TABLE_ENTRY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_AMD_IA_64_EXCEPTION_TABLE_ENTRY_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/File_Readers/Windows_PE/PE_Exception_Table_Entry.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

    class AMD_IA_64_Exception_Table_Entry : public PE_Exception_Table_Entry,
                                            public boost::enable_shared_from_this < AMD_IA_64_Exception_Table_Entry >
    {
    public:

      friend class PE_File;

      /*!
       * \brief Default Constructor
       */
      AMD_IA_64_Exception_Table_Entry();

      /*!
       * \brief Default Destructor
       */
      virtual ~AMD_IA_64_Exception_Table_Entry(){}

      virtual void read_Entry ( wpef_types::PE_File::ptr_t file_ref );

      /*!
       * \brief Convert the header data into a string representation
       * \return String representation of header data
       */
      virtual std::string to_String (void);

      /*!
       * \brief Convert the bit order of the stored data if host and data
       * endian types differ
       *
       * \param host_endian Endian type of host
       * \param data_endian Endian type of data
       */
      virtual void convert ();

    private:

      boost::uint32_t m_begin_address;

      boost::uint32_t m_end_address;

      boost::uint32_t m_unwind_information;
    };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_AMD_IA_64_EXCEPTION_TABLE_ENTRY_HPP_INCLUDED
