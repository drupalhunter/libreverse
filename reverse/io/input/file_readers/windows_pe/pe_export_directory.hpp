/*  PE_Export_Directory.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_EXPORT_DIRECTORY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_EXPORT_DIRECTORY_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/base_header.hpp>
#include <reverse/io/byte_converter.hpp>
#include <reverse/io/input/file_readers/windows_pe/section_flags.hpp>

#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {


	  class pe_export_directory : public io::input::base_header {
	  public:

	    friend class pe_file;

	    pe_export_directory ();

	    virtual ~pe_export_directory(){}

	    /*!
	     * \brief Return the bit size of this header
	     * \return Bit size of header
	     */
	    virtual boost::uint32_t get_size (void) const;

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string ( boost::uint32_t base_address );

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    void set_dll_name ( std::string name );

	    void add_export_rva ( boost::uint32_t val );

	    void add_name_pointer_rva ( boost::uint32_t val );

	    boost::uint32_t get_address_table_entries ( void ) const;

	    boost::uint32_t get_export_address_table_rva ( void ) const;

	    boost::uint32_t get_number_of_name_pointers ( void ) const;

	    boost::uint32_t get_name_pointer_rva ( void ) const;

	    boost::uint32_t get_ordinal_table_rva ( void ) const;

	    void add_export_entry ( boost::uint32_t export_addr,
				    boost::uint16_t ordinal_value,
				    std::string symbol_name );
	  private:

	    /*
	      MS_PE_COFF: Reserved, must be 0.
	    */
	    boost::uint32_t m_export_flags;

	    /*
	      MS_PE_COFF: The time and date that the export data was
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
	      MS_PE_COFF: The address of the ASCII string that contains
	      the name of the DLL. This address is relative to the image
	      base.
	    */
	    boost::uint32_t m_name_rva;

	    /*
	      MS_PE_COFF: The starting ordinal number for exports in this
	      image. This field specifies the starting ordinal number for
	      the export address table. It is usually set to 1.
	    */
	    boost::uint32_t m_ordinal_base;

	    /*
	      MS_PE_COFF: The number of entries in the export address
	      table.
	    */
	    boost::uint32_t m_address_table_entries;

	    /*
	      MS_PE_COFF: The number of entries in the name pointer table.
	      This is also the number of entries in the ordinal table.
	    */
	    boost::uint32_t m_num_of_name_pointers;

	    /*
	      MS_PE_COFF: The address of the export address table,
	      relative to the image base.
	    */
	    boost::uint32_t m_export_address_table_rva;

	    /*
	      MS_PE_COFF: The address of the export name pointer table,
	      relative to the image base. The table size is given by the
	      Number of Name Pointers field.
	    */
	    boost::uint32_t m_name_pointer_rva;

	    /*
	      MS_PE_COFF: The address of the ordinal table, relative to
	      the image base.
	    */
	    boost::uint32_t m_ordinal_table_rva;

	    std::string m_dll_name;

	    // KEY: hash of string name
	    // VALUE: string name
	    typedef std::map< std::size_t, std::string > name_string_table_t;
	    name_string_table_t m_name_string_table;

	    // KEY: Ordinal value
	    // VALUE: hash of string name
	    typedef std::map< boost::uint32_t, std::size_t> rev_name_table_t;
	    rev_name_table_t m_rev_name_hash_table;

	    // KEY: hash of string name
	    // VALUE: Index into m_ordinal_list
	    typedef std::map< std::size_t, std::size_t> name_table_t;
	    name_table_t m_name_table;

	    // VALUE: Ordinal values
	    typedef std::vector<boost::uint32_t> ordinal_list_t;
	    ordinal_list_t m_ordinal_list;

	    // KEY: Ordinal value
	    // VALUE: Address of function in memory
	    typedef std::map<boost::uint32_t const, boost::uint32_t const> export_table_t;
	    export_table_t m_export_table;
	  };

 	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_EXPORT_DIRECTORY_HPP_INCLUDED
