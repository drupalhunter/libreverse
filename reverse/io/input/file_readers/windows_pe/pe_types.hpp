/*  PE_Types.h

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

#ifndef PE_TYPES_H
#define PE_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <vector>
#include <map>
#include <string>

namespace libreverse {

  namespace wpef_module {

    class AMD_IA_64_Exception_Table_Entry;
    class ARM_POWERPC_SH_Exception_Table_Entry_32;
    class ARM_POWERPC_SH_Exception_Table_Entry_64;
    class COFF_Header;
    class Data_Directory;
    class DOS_Header;
    class DOS_Relocation_Header;
    class Header_32;
    class Header_64;
    class PE_Debug_Directory;
    class PE_File;
    class PE_Exception_Table_Entry;
    class PE_Export_Directory;
    class PE_Header_32;
    class PE_Header_64;
    class PE_Import_Directory;
    class PE_Information_Block;
    class PE_Load_Config_Directory;
    class PE_Optional_Header_32;
    class PE_Optional_Header_64;
    class PE_Optional_Header_Base;
    class PE_Plus_Optional_Header;
    class PE_Resource_Data_Entry;
    class PE_Resource_Directory;
    class PE_Resource_Directory_Entry;
    class PE_Resource_Directory_String;
    class PE_Section_Header;
    class Reader_32;
    class Reader_64;
    class PE_Exception_Table;

  } /* namespace wpef_module */

  namespace wpef_types {

    /*! \brief AMD/IA-64 Exception table entry */
    class AMD_IA_64_Exception_Table_Entry
    {
    public:
      /*! \brief Shared pointer */
      typedef boost::shared_ptr <wpef_module::AMD_IA_64_Exception_Table_Entry> ptr_t;
    };

    /*! \brief AMD/PowerPC/SH (32-bit) Exception table entry */
    class ARM_POWERPC_SH_Exception_Table_Entry_32
    {
    public:
      typedef boost::shared_ptr < wpef_module::ARM_POWERPC_SH_Exception_Table_Entry_32 > ptr_t;
    };

    /*! \brief AMD/PowerPC/SH (64-bit) Exception table entry */
    class ARM_POWERPC_SH_Exception_Table_Entry_64
    {
    public:
      typedef boost::shared_ptr < wpef_module::ARM_POWERPC_SH_Exception_Table_Entry_64 > ptr_t;
    };

    /*! \brief COFF Header */
    class COFF_Header
    {
    public:
      typedef boost::shared_ptr <wpef_module::COFF_Header> ptr_t;
    };

    /*! \brief PE Data directory  */
    class Data_Directory
    {
    public:
      typedef boost::shared_ptr <wpef_module::Data_Directory> ptr_t;
    };

    /*! \brief MS-DOS header (1st header in file) */
    class DOS_Header
    {
    public:
      typedef boost::shared_ptr <wpef_module::DOS_Header> ptr_t;
      typedef boost::shared_ptr <wpef_module::DOS_Header const> const_ptr_t;
    };

    /*! \brief MS-DOS relocation header. This is often not in PE files */
    class DOS_Relocation_Header
    {
    public:
      typedef boost::shared_ptr <wpef_module::DOS_Relocation_Header> ptr_t;
    };

    /*! \brief PE Debug Directory contains the debugging information. */
    class PE_Debug_Directory
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Debug_Directory> ptr_t;
    };

    /*! \brief PE Export Directory contains the export table information. */
    class PE_Export_Directory
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Export_Directory> ptr_t;
    };

    /*! \brief PE Exception Table entry */
    class PE_Exception_Table_Entry
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Exception_Table_Entry > ptr_t;
      typedef boost::shared_ptr < wpef_module::PE_Exception_Table_Entry const> const_ptr_t;
    };

    /*! \brief Libreverse file type for handling reading information from a PE file */
    class PE_File
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_File > ptr_t;
    };

    /*! \brief PE Header (32-bit) */
    class PE_Header_32
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Header_32 > ptr_t;
      typedef boost::shared_ptr < wpef_module::PE_Header_32 const> const_ptr_t;
    };

    /*! \brief PE Header (64-bit) */
    class PE_Header_64
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Header_64 > ptr_t;
      typedef boost::shared_ptr < wpef_module::PE_Header_64 const> const_ptr_t;
    };

    /*! \brief PE Information Block */
    class PE_Information_Block
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Information_Block> ptr_t;
    };

    /*! \brief PE Import Directory contains the import table information. */
    class PE_Import_Directory
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Import_Directory> ptr_t;
      typedef boost::shared_ptr <wpef_module::PE_Import_Directory const> const_ptr_t;
    };

    /*! \brief PE Load Config Directory
     *
     * The data directory entry for a pre­reserved SEH load
     * configuration structure must specify a particular size of the
     * load configuration structure because the operating system
     * loader always expects it to be a certain value. In that regard,
     * the size is really only a version check. For compatibility with
     * Windows XP and earlier versions of Windows, the size must be 64
     * for x86 images. (Ref: PE specification v8)
     */
    class PE_Load_Config_Directory
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Load_Config_Directory> ptr_t;
    };

    /*! \brief PE Optional Header (32-bit) */
    class PE_Optional_Header_32
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Optional_Header_32 > ptr_t;
    };

    /*! \brief PE Optional Header (64-bit) */
    class PE_Optional_Header_64
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Optional_Header_64 > ptr_t;
    };

    /*! \brief PE Section Header */
    class PE_Section_Header
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Section_Header> ptr_t;
      typedef boost::shared_ptr <wpef_module::PE_Section_Header const> const_ptr_t;
    };

    /*! \brief PE Resource Data
     *
     * Raw data of the resource section. The size and location
     * information in the Resource Data Descriptions field delimit the
     * individual regions of resource data. (Ref: PE specification v8)
     */
    class PE_Resource_Data_Entry
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Resource_Data_Entry> ptr_t;
    };

    class PE_Resource_Directory
    {
    public:
      typedef boost::shared_ptr < wpef_module::PE_Resource_Directory > ptr_t;
      typedef std::vector< wpef_types::PE_Resource_Data_Entry::ptr_t > Data_List_t;
    };

    class PE_Resource_Directory_Entry
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Resource_Directory_Entry> ptr_t;
    };

    class PE_Resource_Directory_String
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Resource_Directory_String> ptr_t;
    };

    class PE_Exception_Table
    {
    public:
      typedef boost::shared_ptr <wpef_module::PE_Exception_Table> ptr_t;
    };

    class Header_32
    {
    public:
      typedef boost::shared_ptr < wpef_module::Header_32 > ptr_t;
      typedef std::map< std::string, wpef_types::PE_Section_Header::const_ptr_t > Section_Header_Map_t;
      typedef std::vector< wpef_types::PE_Import_Directory::ptr_t > Import_Directory_List_t;
      typedef std::vector< wpef_types::PE_Exception_Table_Entry::const_ptr_t > Exception_Table_List_t;
    };

    class Header_64
    {
    public:
      typedef boost::shared_ptr < wpef_module::Header_64 > ptr_t;
      typedef std::map< std::string, wpef_types::PE_Section_Header::const_ptr_t > Section_Header_Map_t;
      typedef std::vector< wpef_types::PE_Import_Directory::ptr_t > Import_Directory_List_t;
      typedef std::vector< wpef_types::PE_Exception_Table_Entry::const_ptr_t > Exception_Table_List_t;
    };

    class Reader_32
    {
    public:
      typedef boost::shared_ptr < wpef_module::Reader_32 > ptr_t;
    };

    class Reader_64
    {
    public:
      typedef boost::shared_ptr < wpef_module::Reader_64 > ptr_t;
    };

  } /* namespaces wpef_types */

} /* namespace libreverse */

#endif /* PE_TYPES_H */
