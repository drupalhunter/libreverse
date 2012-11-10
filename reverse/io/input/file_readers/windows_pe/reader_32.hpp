/*  Reader_32.h

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

#ifndef WPEF_READER_32_H
#define WPEF_READER_32_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "io/input/File_Readers/File_Reader.h"
#include "io/IO_Types.h"
#include "Reverse.h"
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    /*!
     * \class Reader_32
     * \date 2003
     * \author Stephen Torri
     */
    class Reader_32 : public io::File_Reader {
    public:

      /*!
       * \brief Default Constructor
       * \param target_file The file to be used for decompiling
       */
      Reader_32 ( io_types::File_ID::const_ptr_t target_file );

      /*!
       * \brief Default Destructor
       */
      virtual ~Reader_32();

      /*! \brief Header reference for this reader
       */
      wpef_types::Header_32::ptr_t get_Header (void);

      wpef_types::PE_File::ptr_t get_File (void) const;

      bool support_File_Type ( void );

      virtual void read_Headers ( void );

      void preload_Image ( void );

      virtual data_types::Memory_Map::ptr_t get_Memory_Map ( void );

      /*!
       * \brief Print out the entire file contents
       */
      virtual std::string to_String (void);

      virtual io_types::Text_Data::data_type get_Text_Strings (void);

      virtual io_types::Text_Data::data_type get_UTF16_Strings (void);

      /*!
       * \brief Return the File Type of the target file
       */
      virtual std::string get_File_Type (void);

      /* !\brief Return the Architecture Type of the target file */
      std::string get_Arch_Type (void);

      /* !\brief Return the offset for a section header */
      std::string get_Section_Offset ( std::string name );

      /* !\brief Return the offset for a section length */
      std::string get_Section_Length ( std::string name );

    private:

      std::string get_Entry_Point ( void );

      std::string get_Base_Address ( void );

      wpef_types::PE_Exception_Table_Entry::ptr_t create_Exception_Table_Entry ( boost::uint16_t type );

      /*---------------
       *   Variables
       *---------------*/
      /*! \brief WPEF File handle */
      wpef_types::PE_File::ptr_t m_file;

      /*! \brief Need to convert header data byte order */
      bool m_convert;

      wpef_types::Header_32::ptr_t m_data;

      wpef_types::PE_File::ptr_t m_loaded_file;

    public:

      /*---------------
       *   Functions
       *---------------*/

      /*!
       * \brief Get the WPEF DOS Header from the file
       */
      void read_DOS_Header (void);

      /*!
       * \brief Get the WPEF PE Header from the file
       */
      void read_PE_Header (void);

      /*!
       * \brief Get the WPEF PE Section Header from the file
       */
      void read_Section_Headers (void);

      virtual std::string get_Section_String ( std::string name ) const;

      api::Results::Values read_Export_Table ();

      void read_Import_Table ();

      void read_Import_Lookup_Table ( wpef_types::PE_Import_Directory::ptr_t& import_dir_ptr );

      /*!
       * \brief Get the WPEF PE Resource Tables from the image
       */
      void read_Resource_Table ();

      void
      handle_Resource_Directory_Entries ( wpef_types::PE_Resource_Directory::ptr_t& parent_ptr,
					  wpef_types::PE_Resource_Directory_Entry::ptr_t& parent_entry_ptr,
					  boost::uint32_t base_address );

      void read_Debug_Table ();

      void read_Load_Config_Table ();

      void read_Exception_Table ();

    };

  } /* namespace wpef_module */
} /* namespace libreverse */

#endif /* WPEF_READER_H_ */
