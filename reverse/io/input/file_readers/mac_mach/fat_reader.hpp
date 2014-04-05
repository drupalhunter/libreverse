/*  Fat_Reader.h

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

#ifndef FAT_READER_H_
#define FAT_READER_H_

#include "io/input/File_Readers/File_Reader.h"
#include "io/IO_Types.h"
#include "Mach_Types.h"

namespace reverse
{
    namespace mach_module
    {

        /*!
         * \class Reader
         * \date 2003
         * \author Stephen Torri
         */
        class Fat_Reader : public io::File_Reader
        {
            public:

                /*!
                 * \brief Constructor
                 * \param target_file The file to be used for decompiling
                 */
                Fat_Reader ( io_types::File_ID::ptr_t target_file );

                /*!
                 * \brief Constructor
                 * \param mem_ptr The memory_map from which we will read the Fat file
                 * \param target_file The name associated with memory_map (original filename).
                 */
                Fat_Reader ( data_types::memory_map::ptr_t mem_ptr,
                             io_types::File_ID::ptr_t target_file );

                /*!
                 * \brief Default Destructor
                 */
                virtual ~Fat_Reader();

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
                 * \brief Return memory_map associated with this reader
                 * \return memory_map pointer
                 */
                virtual data_types::memory_map::ptr_t get_memory_map ( void );

                /*!
                 * \brief Print out the entire file contents
                 * \return String representation of the file contents
                 */
                virtual std::string to_String ( void );

                /*!
                 * \brief Get human readable strings
                 * \return List of strings found in the file
                 */
                virtual io_types::Text_Data::data_type get_Text_Strings ( void );

                /*!
                 * \brief Read UTF-16 strings from file
                 * \return List of UTF-16 strings found in the file
                 */
                virtual io_types::Text_Data::data_type get_UTF16_Strings ( void );

                /*!
                 * \brief ?
                 * \param name ?
                 * \return section string?
                 */
                virtual std::string get_Section_String ( std::string name ) const;

                /*!
                 * \brief Get the Fat_Header object
                 * \return Fat_Header pointer
                 */
                mach_types::Fat_Header::ptr_t get_Header ( void );

                /*!
                 * \brief Return the File Type of the target file
                 * \return String representing meta information on file type
                 */
                std::string get_File_Type ( void );

                /*!
                 * \brief Return the Architecture Type of the target file
                 * \return String representing meta information on arch type
                 */
                std::string get_Arch_Type ( void ) const;

            private:


                /*!
                                 * \brief Create Mach files from Fat file
                                 *
                                 * Fat files contain one or more Mach files. We need to get the subset of the image from
                                 * the original file before we begin to parse it.
                                 */
                void create_Mach_Files ( void );

                /*---------------
                 *   Variables
                 *---------------*/
                /*! \brief Mach File handle */
                mach_types::Mach_File::ptr_t m_file;

                /*! \brief TRUE = must convert data byte order, FALSE = byte order of data matches CPU */
                bool m_need_convert;

                /*! \brief Handle to the fat header associated with this file. */
                mach_types::Fat_Header::ptr_t m_header;

                /*! \brief List of 32-bit Mach files */
                std::vector<mach_types::Mach_Reader_32::ptr_t> m_32bit_files;

                /*! \brief List of 64-bit Mach files */
                std::vector<mach_types::Mach_Reader_64::ptr_t> m_64bit_files;

            public:

                /*---------------
                 *   Functions
                 *---------------*/

                /*!
                 * \brief Get the Mach Header from the file
                 */
                void read_Fat_Header ( void );

                /*! \brief Create list of Mach Readers for each of the Mach file images found in Fat file */
                void create_Mach_Readers ( void );

        };

    } /* namespace mach_module */
} /* namespace reverse */

#endif /* MACHREADER_H_ */
