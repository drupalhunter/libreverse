/*  PE_Load_Config_Directory.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_LOAD_CONFIG_DIRECTORY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_LOAD_CONFIG_DIRECTORY_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>


namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

          class pe_load_config_directory : public io::input::base_header {
	  public:

	    friend class pe_file;

	    pe_load_config_directory ();

	    virtual ~pe_load_config_directory(){}

	    /*!
	     * \brief Return the bit size of this header
	     * \return Bit size of header
	     */
	    virtual boost::uint32_t get_size (void) const;

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void) const;

	    /*!
	     * \brief Convert the bit order of the stored data if host and data
	     * endian types differ
	     *
	     * \param host_endian Endian type of host
	     * \param data_endian Endian type of data
	     */
	    virtual void convert ( bool host_endian,
				   bool data_endian );

	  private:

	    /*
	      MS_PE_COFF: Reserved, must be 0.
	    */
	    boost::uint32_t m_characteristics;

	    /*
	      MS_PE_COFF: The time and date that the debug data was
	      created.
	    */
	    boost::uint32_t m_time_date_stamp;

	    /*
	      MS_PE_COFF: The major version number. The major and minor
	      version numbers can be set by the user.
	    */
	    boost::uint16_t m_major_version;

	    /*
	      MS_PE_COFF: The minor version number.
	    */
	    boost::uint16_t m_minor_version;

	    /*
	      MS_PE_COFF: The format of debugging information. This field
	      enables support of multiple debuggers.
	    */
	    boost::uint32_t m_type;

	    /*
	      MS_PE_COFF: The size of the debug data
	    */
	    boost::uint32_t m_size_of_data;

	    /*
	      MS_PE_COFF: The address of the debug data when loaded,
	      relative to the image base.
	    */
	    boost::uint32_t m_address_of_raw_data;

	    /*
	      MS_PE_COFF: The file pointer to the debug data.
	    */
	    boost::uint32_t m_pointer_to_raw_data;
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_LOAD_CONFIG_DIRECTORY_HPP_INCLUDED
