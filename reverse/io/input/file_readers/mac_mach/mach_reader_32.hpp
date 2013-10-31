/*  Mach_Reader_32.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_MAC_MACH_MACH_READER_32_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_MAC_MACH_MACH_READER_32_HPP_INCLUDED

#include <reverse/io/input/file_readers/file_reader.hpp>
#include <reverse/io/input/file_readers/mac_mach/mach_file.hpp>

namespace reverse {

  namespace data_containers {
    class memory_map;
  }

  namespace io {

    class file_id;

    namespace input {
      namespace file_readers {
	namespace mac_mach {

        /*!
         * \class mach_reader_32
         * \date 2007
         * \author stephen torri
         */
        class mach_reader_32 : public io::file_reader
        {
        public:

            /*!
             * \brief Constructor
             * \param target_file The file to be used for decompiling
             */
            Mach_Reader_32 ( io_types::File_ID::const_ptr_t target_file );

            /*!
             * \brief Constructor
             * \param Memory_Map pointer associated with Mach file
             * \param target_file The file to be used for decompiling
             */
            Mach_Reader_32 ( data_types::Memory_Map::ptr_t mem_ptr,
                             io_types::File_ID::const_ptr_t target_file );

            /*!
             * \brief Default Destructor
             */
            virtual ~Mach_Reader_32();

            /*!
             * \brief Indicate if file type is supported by this reader
             * \return Boolean value indicating support (TRUE = yes, FALSE = no)
             */
            virtual bool support_File_Type ( void );

            /*!
             * \brief Read the file headers from the file
             */
            virtual void read_Headers ( void );

            /*!
             * \brief Return Memory_Map associated with this reader
             * \return Memory_Map pointer
             */
            virtual data_types::Memory_Map::ptr_t get_Memory_Map ( void );

            /*!
             * \brief Print out the entire file contents
             * \return String representation of the file contents
             */
            virtual std::string to_String ( void );

            /*!
             * \brief Get human readable strings
             */
            virtual io_types::Text_Data::data_type get_Text_Strings ( void );

            /*!
             * \brief Read UTF-16 strings from file
             */
            virtual io_types::Text_Data::data_type get_UTF16_Strings ( void );

            /*!
             * \brief ?
             * \param name ?
             * \return section string?
             */
            virtual std::string get_Section_String ( std::string name ) const;

            /*!
             * \brief Get the Mach_Header object
             * \return Mach_Header pointer
             */
            mach_types::Mach_Header_32::ptr_t get_Header ( void );

            /*!
             * \brief Return the File Type of the target file
             */
            std::string get_File_Type ( void );

            /*!
             * \brief Return the Architecture Type of the target file
             */
            std::string get_Arch_Type ( void ) const;

        private:

            /*! \brief Read Mach header from file */
            void read_Mach_Header ( void );

            /*! \brief Read Load Commands from file */
            void read_Load_Commands ( void );

            /*---------------
             *   Variables
             *---------------*/
            /*! \brief Mach reader implementation */
            mach_types::Mach_Header_32::ptr_t m_header;

            typedef std::vector<mach_types::Load_Command::ptr_t> Command_List_t;
            Command_List_t m_commands;

            /*! \brief Mach file handle */
            Mach_File m_file;

            /*! \brief Conversion of data read is required */
            bool m_convert;
        };

    } /* namespace mach_module */
} /* namespace libreverse */

#endif /* MACH_READER_32_H_ */
