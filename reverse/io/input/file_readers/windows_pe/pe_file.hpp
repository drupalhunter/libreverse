/*  PE_File.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_FILE_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_FILE_HPP_INCLUDED

#include <reverse/io/file.hpp>
#include <reverse/results.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {

  namespace data_containers {
    class memory_map;
  }

  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class amd_ia_64_exception_table_entry;
	  class arm_powerpc_sh_exception_table_entry_32;
	  class arm_powerpc_sh_exception_table_entry_64;
	  class coff_header;
	  class dos_header;
	  class dos_relocation_header;
	  class pe_debug_directory;
	  class pe_export_directory;
	  class pe_header_32;
	  class pe_header_64;
	  class pe_import_directory;
	  class pe_optional_header_32;
	  class pe_optional_header_64;
	  class pe_section_header;
	  class pe_resource_data_entry;
	  class pe_resource_directory;
	  class pe_resource_directory_entry;
	  class pe_resource_directory_string;

	  /*!
	   * \class PE_File
	   *
	   * \brief PE_File contains all the elf specific functionality to
	   * read binary data from a target file.
	   *
	   * \date 2004
	   */
	  class pe_file {
	  public:

	    /*! \brief Narrow? (Copy Constructor?)
	     *  \param f_ref Reference to the File object to copy
	     */
	    pe_file ( boost::shared_ptr < const io::file_id > filename );

	    pe_file ( boost::shared_ptr < data_containers::memory_map > file_img_ptr,
		      boost::shared_ptr < const io::file_id > filename );

	    bool init (void);

	    boost::uint32_t get_file_size (void) const;

	    template <typename offset_type>
	    void seek ( offset_type offset )
	    {
	      m_file.seek ( offset );
	    }

	    results::values address_seek ( boost::uint32_t address );

	    void index_seek ( boost::uint32_t offset );

	    void copy ( boost::shared_ptr < data_containers::memory_map > dest_ptr,
			boost::uint32_t length );

	    boost::shared_ptr < const io::file_id > get_id (void) const;

	    boost::uint32_t get_present_position_value (void) const;

	    template <typename value_type>
	    void read ( value_type* value )
	    {
	      m_file.read ( value );
	    }

	    boost::shared_ptr < const data_containers::memory_map > get_memory_map (void) const;

	    /* Read DOS header from file */
	    void read_dos_header ( boost::shared_ptr < windows_pe::dos_header > obj );

	    /* Read PE header from file */
	    void read_pe_header ( boost::shared_ptr < windows_pe::pe_header_32 > obj );

	    void read_pe_header ( boost::shared_ptr < windows_pe::pe_header_64 > obj );

	    /* Read PE File header from file */
	    void read_coff_header ( boost::shared_ptr < windows_pe::coff_header > obj );

	    /* Read PE Optional header from file */
	    void read_pe_optional_header ( boost::shared_ptr < windows_pe::pe_optional_header_32 > obj );

	    void read_pe_optional_header ( boost::shared_ptr < windows_pe::pe_optional_header_64 > obj );

	    /* Read PE Section header from file */
	    void read_pe_section_header ( boost::shared_ptr < windows_pe::pe_section_header > obj );

	    void read_dos_relocation_header ( boost::shared_ptr < windows_pe::dos_relocation_header > obj );

	    void read_pe_resource_directory ( boost::shared_ptr < windows_pe::pe_resource_directory > obj );

	    void read_pe_resource_directory_entry ( boost::shared_ptr < windows_pe::pe_resource_directory_entry > obj );

	    results::values read_pe_resource_data_entry ( boost::shared_ptr < windows_pe::pe_resource_data_entry > obj,
							  boost::uint32_t base_address );

	    void read_pe_export_directory ( boost::shared_ptr < windows_pe::pe_export_directory > obj );

	    void read_pe_resource_directory_string ( boost::shared_ptr < windows_pe::pe_resource_directory_string > obj );

	    void read_pe_import_directory ( boost::shared_ptr < windows_pe::pe_import_directory > obj );

	    void read_null_terminated_string ( std::string& obj );

	    void read_pe_debug_directory ( boost::shared_ptr < windows_pe::pe_debug_directory > obj );

	    void read_amd_ia_64_exception ( boost::shared_ptr < windows_pe::amd_ia_64_exception_table_entry > obj );

	    void read_arm_powerpc_sh_exception ( boost::shared_ptr < windows_pe::arm_powerpc_sh_exception_table_entry_64 > obj );

	    void read_arm_powerpc_sh_exception ( boost::shared_ptr < windows_pe::arm_powerpc_sh_exception_table_entry_32 > obj );

	  private:

	    io::file m_file;
        
	  };
	  
	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_WINDOWS_PE_PE_FILE_HPP_INCLUDED
