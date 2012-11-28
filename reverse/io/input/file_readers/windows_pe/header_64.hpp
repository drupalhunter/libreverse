/*  Header_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_HEADER_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_HEADER_64_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class dos_header;
	  class pe_debug_directory;
	  class pe_exception_table_entry;
	  class pe_export_directory;
	  class pe_header_64;
	  class pe_import_directory;
	  class pe_load_config_directory;
	  class pe_resource_directory;
	  class pe_section_header;
   
	  /*!
	   * \class Header
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class header_64 : public io::input::base_header {

	  public:

	    typedef std::map < std::string, boost::shared_ptr < const pe_section_header > > section_header_map_t;
	    typedef std::vector < boost::shared_ptr < pe_import_directory > > import_directory_list_t;
	    typedef std::vector < boost::shared_ptr < const pe_exception_table_entry > > exception_table_list_t;


	    /*!
	     * \brief Default Constructor
	     */
	    header_64 ();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~header_64 ();

	    /*!
	     * \brief Change the bit-ordering if required
	     */
	    virtual void convert ();

	    /*!
	     * \brief String representation of WPEF Header
	     * \return String output of header
	     */
	    std::string to_string (void);

	    /*!
	     * \brief Get the human readable strings from the header
	     * \return String output of header
	     */
	    void get_text_string ( std::vector < std::string >& output );

	    /*-----------------------------*/
	    /*        DOS HEADER           */
	    /*-----------------------------*/
	    boost::shared_ptr < dos_header > get_dos_header (void) const;

	    void set_dos_header ( boost::shared_ptr < dos_header > hdr );

	    /*-----------------------------*/
	    /*        PE HEADER            */
	    /*-----------------------------*/

	    boost::shared_ptr < pe_header_64 > get_pe_header (void) const;

	    void set_pe_header ( boost::shared_ptr < pe_header_64 > hdr );

	    /*-----------------------------*/
	    /*       SECTION HEADER        */
	    /*-----------------------------*/

	    /*
	     * Return the iterator pointing to the PE Section Header. If
	     * an incorrect name has been given the iterator will point to
	     * the end of the PE Section Header list.
	     */
	    header_64::section_header_map_t::const_iterator get_pe_section_header ( std::string name ) const;

	    boost::uint32_t get_pe_section_header_count (void) const;

	    void set_pe_section_header ( boost::shared_ptr < pe_section_header > hdr );

	    header_64::section_header_map_t::const_iterator get_pe_section_header_list_begin () const;

	    header_64::section_header_map_t::const_iterator get_pe_section_header_list_end () const;

	    /*-----------------------------*/
	    /*      RESOURCE DIRECTORY     */
	    /*-----------------------------*/

	    void set_resource_directory ( boost::shared_ptr < pe_resource_directory > r_ptr );

	    /*-----------------------------*/
	    /*      EXPORT DIRECTORY       */
	    /*-----------------------------*/
	    void set_export_directory ( boost::shared_ptr < pe_export_directory > exp_ptr );

	    boost::shared_ptr < pe_export_directory > get_export_directory () const;

	    /*-----------------------------*/
	    /*      IMPORT DIRECTORY       */
	    /*-----------------------------*/

	    void add_import_directory ( boost::shared_ptr < pe_import_directory > exp_ptr );

	    boost::uint32_t get_pe_import_directory_count (void) const;

	    header_64::import_directory_list_t::iterator get_pe_import_directory_list_begin ();

	    header_64::import_directory_list_t::iterator get_pe_import_directory_list_end ();

	    header_64::import_directory_list_t::const_iterator get_pe_import_directory_list_begin () const;

	    header_64::import_directory_list_t::const_iterator get_pe_import_directory_list_end () const;

	    /*-----------------------------*/
	    /*       DEBUG DIRECTORY       */
	    /*-----------------------------*/

	    void set_debug_directory ( boost::shared_ptr < pe_debug_directory > r_ptr );

	    boost::shared_ptr < pe_debug_directory > get_debug_directory ( void ) const;

	    /*-----------------------------*/
	    /*    LOAD CONFIG DIRECTORY    */
	    /*-----------------------------*/

	    void set_load_config_directory ( boost::shared_ptr < pe_load_config_directory > r_ptr );

	    boost::shared_ptr < pe_resource_directory > get_pe_resource_directory ( void );

	    /*-----------------------------*/
	    /*    EXCEPTION TABLE LIST     */
	    /*-----------------------------*/
	    void add_exception_table_entry ( boost::shared_ptr < pe_exception_table_entry > exp_ptr );

	    boost::uint32_t get_pe_exception_table_entry_count (void) const;

	    header_64::exception_table_list_t::iterator get_pe_exception_table_list_begin ();

	    header_64::exception_table_list_t::iterator get_pe_exception_table_list_end ();

	    header_64::exception_table_list_t::const_iterator get_pe_exception_table_list_begin () const;

	    header_64::exception_table_list_t::const_iterator get_pe_exception_table_list_end () const;

	  private:

	    /* Variables */

	    /*! \brief WPEF DOS Header */
	    boost::shared_ptr < dos_header > m_dos_hdr;

	    /*! \brief WPEF PE Header */
	    boost::shared_ptr < pe_header_64 > m_pe_hdr;

	    /*! \brief List of PE Section Headers */
	    header_64::section_header_map_t m_sec_hdrs;

	    /*! \brief PE Resource Directories */
	    boost::shared_ptr < pe_resource_directory > m_res_ptr;

	    /*! \brief PE Export Directories */
	    boost::shared_ptr < pe_export_directory > m_export_dir_ptr;

	    /*! \brief PE Import Directories */
	    header_64::import_directory_list_t m_import_dir_list;

	    /*! \brief PE Debug Directories */
	    boost::shared_ptr < pe_debug_directory > m_debug_ptr;

	    /*! \brief PE Load_Config Directories */
	    boost::shared_ptr < pe_load_config_directory > m_load_config_ptr;

	    /*! \brief PE Exception Table entries */
	    header_64::exception_table_list_t m_exception_list;

	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_HEADER_64_HPP_INCLUDED
