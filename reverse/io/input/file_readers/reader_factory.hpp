/*  Reader_Factory.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_READER_FACTORY_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_READER_FACTORY_HPP_INCLUDED

#include <reverse/errors/file_reader_exception.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/file_reader.hpp>

#include <boost/shared_ptr.hpp>

#include <map>

namespace reverse {
  namespace io {

    class file_id;

    namespace input {
      namespace file_readers {

	/*!
	 * \class Reader_Factory
	 * \date 2003
	 * \author Stephen Torri
	 */
	class reader_factory {
	public:

	  /*!
	   * \brief Produce a factory reference for use in creating Elf Readers
	   * \return Return a pointer to the Elf Reader Factory
	   *
	   * This object was designed with the Singleton pattern in mind.
	   */
	  static reader_factory& instance (void);

	  boost::shared_ptr < file_reader> create_file_reader ( std::string filename );

	  /*!
	   * \brief Remove the reader associated with the filename from the list
	   * 	of active readers.
	   */
	  void clear_reader ( std::string filename );

	private:

	  typedef std::pair < boost::shared_ptr < file_reader>, bool > reader_pair_t;

	  /*!
	   * \brief Elf Reader generated to support target file
	   * \param target_file The reference to the file being decompiled
	   * \return Pointer to the appropriate reader for this target file
	   */
	  reader_pair_t create_elf_reader ( boost::shared_ptr < const file_id >& target_file );

	  /*!
	   * \brief WPEF Reader generated to support target file
	   * \param target_file The reference to the file being decompiled
	   * \return Pointer to the appropriate reader for this target file
	   */
	  reader_pair_t create_wpef_reader ( boost::shared_ptr < const file_id >& target_file );

	  /*!
	   * \brief Java class Reader generated to support target file
	   * \param target_file The reference to the file being decompiled
	   * \return Pointer to the appropriate reader for this target file
	   */
	  reader_pair_t create_java_reader ( boost::shared_ptr < const file_id >& target_file );

	  /*!
	   * \brief Mach Reader generated to support target file
	   * \param target_file The reference to the file being decompiled
	   * \return Pointer to the appropriate reader for this target file
	   */
	  reader_pair_t create_mach_reader ( boost::shared_ptr < const file_id >& target_file );

	  /*!
	   * \brief Mach Fat Reader generated to support target file
	   * \param target_file The reference to the file being decompiled
	   * \return Pointer to the appropriate reader for this target file
	   */
	  reader_pair_t create_mach_fat_reader ( boost::shared_ptr < const file_id >& target_file );

	  // TRUE = little endian
	  // FALSE = big endian
	  bool detect_host_endian (void);

	  reader_factory(){}

	  /*!
	   * \fn ~Reader_Factory ()
	   * \brief Default Constructor
	   */
	  virtual ~reader_factory(){}

	  typedef std::map<std::string, boost::shared_ptr < file_reader> > reader_map_t;
	  reader_map_t m_reader_map;
	};

      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_READER_FACTORY_HPP_INCLUDED
