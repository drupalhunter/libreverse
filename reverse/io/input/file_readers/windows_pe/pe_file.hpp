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

#ifndef PE_FILE_H_
#define PE_FILE_H_

#include "io/IO_Types.h"
#include "io/File.h"
#include <boost/shared_ptr.hpp>
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    /*!
     * \class PE_File
     *
     * \brief PE_File contains all the elf specific functionality to
     * read binary data from a target file.
     *
     * \date 2004
     */
    class PE_File {
    public:

        /*! \brief Narrow? (Copy Constructor?)
         *  \param f_ref Reference to the File object to copy
         */
        PE_File ( io_types::File_ID::const_ptr_t filename );

        PE_File ( data_types::Memory_Map::ptr_t file_img_ptr,
                  io_types::File_ID::const_ptr_t filename );

        bool init (void);

        boost::uint32_t get_File_Size (void) const;

        template <typename Offset_Type>
        void seek ( Offset_Type offset )
        {
            m_file.seek ( offset );
        }

        api::Results::Values address_Seek ( boost::uint32_t address );

        void index_Seek ( boost::uint32_t offset );

        void copy ( data_types::Memory_Map::ptr_t dest_ptr,
                    boost::uint32_t length );

        io_types::File_ID::const_ptr_t get_ID (void) const;

        boost::uint32_t get_Present_Position_Value (void) const;

        template <typename Value_Type>
        void read ( Value_Type* value )
        {
            m_file.read ( value );
        }

	data_types::Memory_Map::ptr_t get_Memory_Map (void) const;

        /* Read DOS header from file */
        void read_DOS_Header ( wpef_types::DOS_Header::ptr_t obj );

        /* Read PE header from file */
        void read_PE_Header ( wpef_types::PE_Header_32::ptr_t obj );

        void read_PE_Header ( wpef_types::PE_Header_64::ptr_t obj );

        /* Read PE File header from file */
        void read_COFF_Header ( wpef_types::COFF_Header::ptr_t obj );

        /* Read PE Optional header from file */
        void read_PE_Optional_Header ( wpef_types::PE_Optional_Header_32::ptr_t obj );

        void read_PE_Optional_Header ( wpef_types::PE_Optional_Header_64::ptr_t obj );

        /* Read PE Section header from file */
        void read_PE_Section_Header ( wpef_types::PE_Section_Header::ptr_t obj );

        void read_DOS_Relocation_Header ( wpef_types::DOS_Relocation_Header::ptr_t obj );

        void read_PE_Resource_Directory ( wpef_types::PE_Resource_Directory::ptr_t obj );

        void read_PE_Resource_Directory_Entry ( wpef_types::PE_Resource_Directory_Entry::ptr_t obj );

        api::Results::Values read_PE_Resource_Data_Entry ( wpef_types::PE_Resource_Data_Entry::ptr_t obj,
							   boost::uint32_t base_address );

        void read_PE_Export_Directory ( wpef_types::PE_Export_Directory::ptr_t obj );

        void read_PE_Resource_Directory_String ( wpef_types::PE_Resource_Directory_String::ptr_t obj );

        void read_PE_Import_Directory ( wpef_types::PE_Import_Directory::ptr_t obj );

        void read_Null_Terminated_String ( std::string& obj );

        void read_PE_Debug_Directory ( wpef_types::PE_Debug_Directory::ptr_t obj );

        void read_AMD_IA_64_Exception ( wpef_types::AMD_IA_64_Exception_Table_Entry::ptr_t obj );

        void read_ARM_POWERPC_SH_Exception ( wpef_types::ARM_POWERPC_SH_Exception_Table_Entry_64::ptr_t obj );

        void read_ARM_POWERPC_SH_Exception ( wpef_types::ARM_POWERPC_SH_Exception_Table_Entry_32::ptr_t obj );

    private:
        io::File m_file;
        
    };
} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_FILE_H_ */
