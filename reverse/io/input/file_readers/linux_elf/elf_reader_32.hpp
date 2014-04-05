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
#include <reverse/io/input/file_readers/linux_elf/elf_file_32.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_types.hpp>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace reverse {

  namespace data_containers {
    class memory_map;
  }

  namespace io {

    class file_id;

    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  class elf_file_header_32;
	  class elf_header_32;
	  class elf_section_header_32;
	  class elf_symbol_32;

	  /*!
	   * \class Elf_Reader_32
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class elf_reader_32 : public io::file_reader {
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

	    virtual bool support_file_type ( void );

	    virtual void read_headers ( void );

	    virtual boost::shared_ptr < data_containers::memory_map > get_memory_map ( void );

	    virtual std::string to_string ( void );

	    virtual std::vector < std::string > get_text_strings ( void );

	    virtual std::vector < std::string > get_utf16_strings ( void );

	    /*---------------
	     *   Functions
	     *---------------*/

	    /*!
	     * \brief Return the File Type of the target file
	     */
	    virtual std::string get_file_type ( void );

	    virtual std::string get_section_string ( std::string name ) const;

	    virtual std::string get_string_name ( boost::uint32_t index ) const;
	    void set_symbol_name ( boost::shared_ptr < elf_symbol_32 > symbol_ptr );

	    const elf_file_32& get_file ( void ) const;

	  private:

	    /*---------------
	     *   Variables
	     *---------------*/

	    /*! \brief elf file handle */
	    struct elf_file_32 m_elf_file;

	    /*! \brief Support the Elf 32-bit file format. */
	    bool m_supported;

	    /*! \brief filename of target. */
	    boost::shared_ptr < const io::file_id > m_filename;
	    
	    boost::shared_ptr < data_containers::memory_map > m_string_table_ptr;
	  };

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_ELF_ELF_READER_32_HPP_INCLUDED
