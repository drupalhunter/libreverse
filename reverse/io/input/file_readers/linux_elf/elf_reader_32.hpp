/*  Elf_Reader_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_READER_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_READER_32_HPP_INCLUDED

#include <reverse/io/input/file_readers/file_reader.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {

  namespace data_containers {
    class memory_map;
  }

  namespace io {
    
    class file_id;

    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_file;
	  class elf_header_32;
	  class elf_section_header_32;
	  class elf_symbol_32;

	  /*!
	   * \class Elf_Reader_32
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class elf_reader_32 : public io::file_reader
	  {
	  public:

	    /*!
	     * \brief Default Constructor
	     * \param target_file The file to be used for decompiling
	     */
	    elf_reader_32 ( boost::shared_ptr < const io::file_id > target_file );

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~elf_reader_32();

	    /*! \brief Elf_Header reference for this reader */
	    boost::shared_ptr < elf_header_32 > get_header ( void );

	    virtual bool support_File_Type ( void );

	    virtual void read_Headers ( void );

	    virtual boost::shared_ptr < data_containers::memory_map > get_memory_map ( void );

	    virtual std::string to_string ( void );

	    virtual std::string get_text_strings ( void );

	    virtual std::string get_utf16_strings ( void );

	    /*---------------
	     *   Functions
	     *---------------*/

	    /*!
	     * \brief Get the Elf File Header from the file
	     */
	    void read_file_header ( void );

	    /*!
	     * \brief Get the Elf Program Headers from the file
	     */
	    void read_program_headers ( void );

	    /*!
	     * \brief Return the File Type of the target file
	     */
	    virtual std::string get_file_type ( void );

	    /* !\brief Return the Architecture Type of the target file */
	    std::string get_arch_type ( void );

	    /* !\brief Return the offset for a section header */
	    std::string get_section_offset ( std::string name );

	    /* !\brief Return the offset for a section length */
	    std::string get_section_length ( std::string name );

	    /*!
	     * \brief Return the Entry Point of the target file
	     */
	    std::string get_entry_point ( void );

	    /*!
	     * \brief Return the Base Address of the target file
	     */
	    std::string get_base_address ( void );

	    /*!
	     * \brief Get the Section Headers from the file
	     */
	    void read_section_headers ( void );

	    /*!
	     * \brief Get the Dynamic Headers from the file
	     */
	    void read_dynamic_headers ( void );

	    /*!
	     * \brief Get the Symbols from the Symbols Token of the file
	     */
	    void read_symbol_token ( void );

	    /*!
	     * \brief Get the Relocation Headers from the file
	     */
	    void read_relocations ( void );

	    /*!
	     * \brief Get the Relocation headers (SHT_REL)
	     */
	    void read_relocation_headers ( boost::shared_ptr < const elf_section_header_32 > sec_hdr,
					   boost::shared_ptr < const elf_file_header_32> file_hdr );

	    /*!
	     * \brief Get the Relocation Addend headers (SHT_RELA)
	     */
	    void read_relocation_addend_headers ( boost::shared_ptr < const elf_section_header_32 > sec_hdr,
						  boost::shared_ptr < const elf_file_header_32> file_hdr );

	    /*!
	     * \brief Get the Relocation symbols
	     */
	    void read_relocation_symbols ( boost::shared_ptr < const elf_section_header_32 > sec_hdr,
					   boost::shared_ptr < const elf_file_header_32> file_hdr );

	    virtual std::string get_section_string ( std::string name ) const;

	    virtual std::string get_string_name ( boost::uint32_t index ) const;

	    void set_symbol_name ( boost::shared_ptr < elf_symbol_32 > symbol_ptr );

	    boost::shared_ptr < const elf_file > get_file (void) const;

	  private:

	    /*---------------
	     *   Variables
	     *---------------*/

	    /*! \brief elf file handle */
	    boost::shared_ptr < elf_types::elf_file > m_elf_file;

	    /*! \brief Conversion of data read is required */
	    bool m_convert;

	    boost::shared_ptr < elf_header_32 > m_elf_data;

	    boost::shared_ptr < data_containers::memory_map > m_string_table_ptr;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_READER_32_HPP_INCLUDED
