/*  Mach_Reader_64.h

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

#ifndef MACH_READER_64_H_
#define MACH_READER_64_H_

#include "io/input/File_Readers/File_Reader.h"
#include "io/IO_Types.h"
#include "Mach_Types.h"
#include "Mach_File.h"

namespace reverse
{
    namespace mach_module
    {

        /*!
         * \class Reader
         * \date 2003
         * \author Stephen Torri
         */
        class Mach_Reader_64 : public io::File_Reader
        {
            public:

                /*!
                 * \brief Default Constructor
                 * \param target_file The file to be used for decompiling
                 */
                Mach_Reader_64 ( io_types::File_ID::const_ptr_t target_file );

                /*!
                 * \brief Constructor
                 * \param memory_map pointer associated with Mach file
                 * \param target_file The file to be used for decompiling
                 */
                Mach_Reader_64 ( data_types::memory_map::ptr_t mem_ptr,
                                 io_types::File_ID::const_ptr_t target_file );

                /*!
                 * \brief Default Destructor
                 */
                virtual ~Mach_Reader_64();

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
                 * \return String representing contents
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
                mach_types::Mach_Header_64::ptr_t get_Header ( void );

                /*!
                 * \brief Return the File Type of the target file
                 */
                std::string get_File_Type ( void );

                /*
                 * !\brief Return the Architecture Type of the target file
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
                mach_types::Mach_Header_64::ptr_t m_header;

                typedef std::vector<mach_types::Load_Command::ptr_t> Command_List_t;
                Command_List_t m_commands;

                /*! \brief Mach file handle */
                Mach_File m_file;

                /*! \brief Conversion of data read is required */
                bool m_convert;
        };

    } /* namespace mach_module */
} /* namespace reverse */

#endif /* Mach_Reader_64_32_H_ */
