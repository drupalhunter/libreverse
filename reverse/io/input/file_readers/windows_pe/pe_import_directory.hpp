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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_IMPORT_DIRECTORY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_IMPORT_DIRECTORY_HPP_INCLUDED

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>
#include <list>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_import_directory : public io::input::base_header {
	  public:
	    
	    friend class pe_file;
	    
	    pe_import_directory ();

	    virtual ~pe_import_directory(){}

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
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    void set_dll_name ( std::string name );

	    void add_function_name ( boost::uint16_t hint, std::string name );

	    void add_ordinal ( boost::uint32_t val );

	    boost::uint32_t get_name_rva (void) const;

	    boost::uint32_t get_import_lookup_table (void) const;

	    boost::uint32_t get_import_address_table (void) const;

	    boost::uint32_t get_timestamp (void) const;

	    boost::uint32_t get_forwarder_chain (void) const;

	    bool const is_null (void) const;

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

	    typedef std::list< std::pair<boost::uint16_t,std::string > > dll_list_t;
	    dll_list_t m_import_dll_list;

	    typedef std::list<boost::uint32_t> ordinal_list_t;
	    ordinal_list_t m_ordinal_list;
	  };

 	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_IMPORT_DIRECTORY_HPP_INCLUDED
