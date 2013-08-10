/*  Reader_64.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_WINDOWS_PE_WPEF_READER_64_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_LINUX_WINDOWS_PE_WPEF_READER_64_HPP_INCLUDED

#include <reverse/io/input/file_readers/file_reader.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_file.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

namespace reverse
{

    namespace data_containers
    {
        class memory_map;
    }

    namespace io
    {

        class file_id;

        namespace input
        {
            namespace file_readers
            {
                namespace windows_pe
                {

		    class header_64;
                    class pe_exception_table_entry;
                    class pe_file;
                    class pe_import_directory;
		    
                    /*!
                     * \class Reader_64
                     * \date 2003
                     * \author Stephen Torri
                     */
		    class reader_64 : public io::file_reader
                    {
                        public:

                            /*!
                             * \brief Default Constructor
                             * \param target_file The file to be used for decompiling
                             */
                            reader_64 ( boost::shared_ptr < const io::file_id > target_file );

                            /*!
                             * \brief Default Destructor
                             */
                            virtual ~reader_64 ();

                            /*! \brief Header reference for this reader
                             */
                            boost::shared_ptr< header_64 > get_header ( void );

			    boost::shared_ptr < pe_file > get_file ( void ) const;

                            bool support_file_type ( void );

                            virtual void read_headers ( void );

                            virtual void preload_image ( void );

                            virtual boost::shared_ptr < data_containers::memory_map > get_memory_map ( void );

                            /*!
                             * \brief Print out the entire file contents
                             */
                            virtual std::string to_string ( void );

                            virtual std::vector < std::string > get_text_strings ( void );

                            virtual std::vector < std::string > get_utf16_strings ( void );

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

                        private:

                            std::string get_entry_point ( void );

                            std::string get_base_address ( void );

                            boost::shared_ptr < pe_exception_table_entry >
                            create_exception_table_entry ( boost::uint16_t type );

                            /*---------------
                             *   Variables
                             *---------------*/
                            /*! \brief WPEF File handle */
                            boost::shared_ptr < pe_file > m_file;

                            /*! \brief Need to convert header data byte order */
                            bool m_convert;

                            boost::shared_ptr < header_64 > m_data;

                            boost::shared_ptr < pe_file > m_loaded_file;

                        public:

                            /*---------------
                             *   Functions
                             *---------------*/

                            /*!
                             * \brief Get the WPEF DOS Header from the file
                             */
                            void read_dos_header ( void );

                            /*!
                             * \brief Get the WPEF PE Header from the file
                             */
                            void read_pe_header ( void );

                            /*!
                             * \brief Get the WPEF PE Section Header from the file
                             */
                            void read_section_headers ( void );

                            virtual std::string get_section_string ( std::string name ) const;

                            void read_export_table ();

                            void read_import_table ();

                            void read_import_lookup_table ( boost::shared_ptr < pe_import_directory > import_dir_ptr );

                            /*!
                             * \brief Get the WPEF PE Resource Tables from the image
                             */
                            void read_resource_table ();

                            void
                            handle_resource_directory_entries ( boost::shared_ptr < pe_resource_directory > parent_ptr,
                                                                boost::shared_ptr < pe_resource_directory_entry > parent_entry_ptr,
                                                                boost::uint32_t base_address );

                            void read_debug_table ();

                            void read_load_config_table ();

                            void read_exception_table ();

                    };

                } /* namespace windows_pe */
            } // namespace file_readers
        } // namespace input
    } // namespace io
} // namespace reverse


#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_LINUX_WINDOWS_PE_WPEF_READER_64_HPP_INCLUDED
