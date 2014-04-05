/*  Mach_File.h

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

#ifndef MACH_FILE_H_
#define MACH_FILE_H_

#include "io/IO_Types.h"
#include "io/File.h"
#include "Reverse.h"
#include "Mach_Types.h"
#include "CPU_X86_32.h"
#include "CPU_X86_64.h"
#include "CPU_PPC_32.h"
#include "CPU_PPC_64.h"
#include "io/Preconditions.h"

namespace libreverse
{
    namespace mach_module
    {

        /*!
         * \class Mach_File
         *
         * \brief Mach_File contains all the elf specific functionality to
         * read binary data from a target file.
         *
         * \date 2004
         */
        class Mach_File
        {
            public:

                /*! \brief Constructor
                 *  \param filename File name associated with this Mach file object
                 */
                Mach_File ( io_types::File_ID::const_ptr_t filename );

                /*! \brief Constructor which creates a Mach_File object from a given memory_map
                 *  \param file_img_ptr Memory Map associated with this Mach file
                 *  \param filename File name associated with this Mach file object
                 */
                Mach_File ( data_types::memory_map::ptr_t file_img_ptr,
                            io_types::File_ID::const_ptr_t filename );

                /*! \brief Initialize Mach_File object
                 *  \return Boolean value to denote success (TRUE) or failure (FALSE)
                 */
                bool init ( void );

                /*! \brief Retrieve the file size
                 *  \return Unsigned integer for file size in bytes
                 */
                boost::uint32_t get_File_Size ( void ) const;

                /*! \brief Move the reader pointer in the file to a new offset
                 *  \param offset New location to start the next read operation
                 */
                template <typename Offset_Type>
                void seek ( Offset_Type offset )
                {
                    m_file.seek ( offset );
                }

                /*! \brief Move the reader pointer in the file to a new address
                 *  \param address New address to start the next read operation
                 *  \return Return api::Results::Types to denote success or failure
                 */
                api::Results::Values address_Seek ( boost::uint32_t address );

                /*! \brief Move the reader pointer in the file to a new offset
                 *  \param offset New location to start the next read operation
                 */
                void index_Seek ( boost::uint32_t offset );

                /*! \brief Copy a section of bytes from the Mach file to a memory_map object from the present location.
                 *  \param dest_ptr Destination memory_map object
                 *  \param length Size of read in bytes
                 *  \pre dest_ptr is not null
                 *  \pre length is not equal to zero
                 */
                void copy ( data_types::memory_map::ptr_t dest_ptr,
                            boost::uint32_t length );

                /*! \brief Return the File_ID object associated with this Mach file
                 *  \return File_ID pointer
                 */
                io_types::File_ID::const_ptr_t get_ID ( void ) const;

                /*! \brief Get the present reader index location
                 *  \return Unsigned integer representing the reader's present index location
                 */
                boost::uint32_t get_Present_Position_Value ( void ) const;

                /*! \brief Read the binary value at the present reader location
                 *  \param value Object to be read from the file
                 *  \pre value is allocated (not null)
                 */
                template <typename Value_Type>
                void read ( Value_Type* value )
                {
                    io::Preconditions::is_set(value);
                    m_file.read ( value );
                }

                /*! \brief Read Mach 32-bit header from file
                 *  \param obj Mach_Header_32 pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Mach_Header ( mach_types::Mach_Header_32::ptr_t obj );

                /*! \brief Read Mach 64-bit header from file
                 *  \param obj Mach_Header_64 pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Mach_Header ( mach_types::Mach_Header_64::ptr_t obj );

                /*! \brief Read Fat_Header from file
                 *  \param obj Fat_Header pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Fat_Header ( mach_types::Fat_Header::ptr_t obj );

                /*! \brief Read Fat_Arch from file
                 *  \param obj Fat_Arch pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Fat_Arch ( mach_types::Fat_Arch::ptr_t obj, bool needs_convert  );

                /*! \brief Read Segment_Command from file
                 *  \param obj Segment_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Segment_Command ( mach_types::Segment_Command::ptr_t obj );

                /*! \brief Read Segment_Command_64 from file
                 *  \param obj Segment_Command_64 pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Segment_Command_64 ( mach_types::Segment_Command_64::ptr_t obj );

                /*! \brief Read Symtab_Command from file
                 *  \param obj Symtab_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Symtab_Command ( mach_types::Symtab_Command::ptr_t obj );

                /*! \brief Read Thread_Command from file
                 *  \param obj Thread_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Thread_Command ( mach_types::Thread_Command::ptr_t obj );

                /*! \brief Read Fvmlib_Command from file
                 *  \param obj Fvmlib_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Fvmlib_Command ( mach_types::Fvmlib_Command::ptr_t obj, bool need_convert );

                /*! \brief Read LC_Str from file
                 *  \param obj LC_Str pointer
                 *  \param present_location Index of the present reader location
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_LC_Str ( mach_types::LC_Str::ptr_t obj,
                                   boost::uint32_t present_location,
                                   bool need_convert );

                /*! \brief Read Ident_Command from file
                 *  \param obj Ident_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Ident_Command ( mach_types::Ident_Command::ptr_t obj );

                /*! \brief Read Fvmfile_Command from file
                 *  \param obj Fvmfile_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Fvmfile_Command ( mach_types::Fvmfile_Command::ptr_t obj, bool need_convert );

                /*! \brief Skip the unimplemented command
                 *  \param obj Skipped_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Skipped_Command ( mach_types::Skipped_Command::ptr_t obj );

                /*! \brief Read Dysymtab_Command from file
                 *  \param obj Dysymtab_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Dysymtab_Command ( mach_types::Dysymtab_Command::ptr_t obj );

                /*! \brief Read Dylib_Command from file
                 *  \param obj Dylib_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Dylib_Command ( mach_types::Dylib_Command::ptr_t obj, bool need_convert );

                /*! \brief Read x86 32-bit CPU state from file
                 *  \param obj CPU_State pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_CPU_State ( mach_types::CPU_State<CPU_X86_32>::ptr_t obj );

                /*! \brief Read x86 64-bit CPU state from file
                 *  \param obj CPU_State pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_CPU_State ( mach_types::CPU_State<CPU_X86_64>::ptr_t obj );

                /*! \brief Read PPC 32-bit CPU state from file
                 *  \param obj CPU_State pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_CPU_State ( mach_types::CPU_State<CPU_PPC_32>::ptr_t obj );

                /*! \brief Read PPC 64-bit CPU state from file
                 *  \param obj CPU_State pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_CPU_State ( mach_types::CPU_State<CPU_PPC_64>::ptr_t obj );

                /*! \brief Read Dylinker_Command from file
                 *  \param obj Dylinker_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Dylinker_Command ( mach_types::Dylinker_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Prebound_Dylib_Command from file
                 *  \param obj Prebound_Dylib_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Prebound_Dylib_Command ( mach_types::Prebound_Dylib_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Routine_Command from file
                 *  \param obj Routine_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Routines_Command ( mach_types::Routines_Command::ptr_t obj );

                /*! \brief Read Routine_Command_64 from file
                 *  \param obj Routine_Command_64 pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Routines_Command_64 ( mach_types::Routines_Command_64::ptr_t obj );

                /*! \brief Read Sub_Framework_Command from file
                 *  \param obj Sub_Framework_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Sub_Framework_Command ( mach_types::Sub_Framework_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Sub_Umbrella_Command from file
                 *  \param obj Sub_Umbrella_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Sub_Umbrella_Command ( mach_types::Sub_Umbrella_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Sub_Client_Command from file
                 *  \param obj Sub_Client_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Sub_Client_Command ( mach_types::Sub_Client_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Sub_Library_Command from file
                 *  \param obj Sub_Library_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 *  \param need_convert Is it necessary to convert this command's fields when reading from the file?
                 */
                void read_Sub_Library_Command ( mach_types::Sub_Library_Command::ptr_t obj, bool need_convert );

                /*! \brief Read Twolevel_Hints_Library_Command from file
                 *  \param obj Twolevel_Hints_Library_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Twolevel_Hints_Command ( mach_types::Twolevel_Hints_Command::ptr_t obj );

                /*! \brief Read UUID_Command from file
                 *  \param obj UUID_Command pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_UUID_Command ( mach_types::UUID_Command::ptr_t obj );

                /*! \brief Read Section from file
                 *  \param obj Section pointer
                 *  \pre 'obj' is allocated (not null)
                 */
                void read_Section ( mach_types::Section::ptr_t obj );

            private:

                io::File m_file;

        };

    } /* namespace mach_module */
} /* namespace libreverse */

#endif /* MACH_FILE_H_ */
