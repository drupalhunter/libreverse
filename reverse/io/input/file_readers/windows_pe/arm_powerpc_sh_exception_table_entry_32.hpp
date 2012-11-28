/*  ARM_POWERPC_SH_Exception_Table_Entry_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_32_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/windows_pe/pe_exception_table_entry.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_file;

	  class arm_powerpc_sh_exception_table_entry_32 : public pe_exception_table_entry,
							  public boost::enable_shared_from_this < arm_powerpc_sh_exception_table_entry_32 > {
	  public:
	    
	    friend class pe_file;

	    /*!
	     * \brief Default Constructor
	     */
	    arm_powerpc_sh_exception_table_entry_32 ();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~arm_powerpc_sh_exception_table_entry_32 (){}

	    virtual void read_entry ( boost::shared_ptr < pe_file > file_ptr );

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void);

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

	    boost::uint8_t m_prolog_length;

	    boost::uint32_t m_function_length;

	    bool m_32bit_flag;

	    bool m_exception_flag;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_ARM_POWERPC_SH_EXCEPTION_TABLE_ENTRY_32_HPP_INCLUDED
