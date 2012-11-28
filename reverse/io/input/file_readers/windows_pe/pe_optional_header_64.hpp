/*  PE_Optional_Header_64.h

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

#ifndef PE_OPTIONAL_HEADER_64_H_
#define PE_OPTIONAL_HEADER_64_H_

#include <reverse/io/input/file_readers/base_header.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class pe_optional_header_64 : public io::input::base_header {
	  public:

	    friend class pe_file;

	    static boost::uint16_t const rom_image;
	    static boost::uint16_t const pe_executable;
	    static boost::uint16_t const pe_plus_executable;

	    /*!
	     * \brief Default Constructor
	     */
	    pe_optional_header_64 ();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~pe_optional_header_64 (){}

	    /*!
	     * \brief Convert the header data into a string representation
	     * \return String representation of header data
	     */
	    virtual std::string to_string (void) const;

	    /*!
	     * \brief Convert the bit order of the stored data
	     */
	    virtual void convert ();

	    bool is_pe_file (void);

	    boost::uint16_t get_magic_value (void) const;

	    boost::uint8_t get_major_linker_version (void) const;

	    boost::uint8_t get_minor_linker_version (void) const;

	    boost::uint32_t get_size_of_code (void) const;

	    boost::uint32_t get_size_of_image (void) const;

	    boost::uint32_t get_base_of_code (void) const;

	    boost::uint32_t get_image_base (void) const;

	    boost::uint32_t get_size_of_init_data (void) const;

	    boost::uint32_t get_entry_point (void) const;

	    boost::uint32_t get_section_alignment (void) const;

	    boost::uint32_t get_file_alignment (void) const;

	    boost::uint32_t get_size_of_uninitialized_data (void) const;

	    boost::uint16_t get_major_operating_system_version (void) const;

	    boost::uint16_t get_minor_operating_system_version (void) const;

	    boost::uint16_t get_major_image_version (void) const;

	    boost::uint16_t get_minor_image_version (void) const;

	    boost::uint16_t get_major_subsystem_version (void) const;

	    boost::uint16_t get_minor_subsystem_version (void) const;

	    boost::uint32_t get_win32_version_value (void) const;

	    boost::uint32_t get_size_of_headers (void) const;

	    boost::uint32_t get_checksum (void) const;

	    boost::uint16_t get_subsystem (void) const;

	    boost::uint16_t get_dll_characteristics (void) const;

	    boost::uint32_t get_size_of_stack_reserve (void) const;

	    boost::uint32_t get_size_of_stack_commit (void) const;

	    boost::uint32_t get_size_of_heap_reserve (void) const;

	    boost::uint32_t get_size_of_heap_commit (void) const;

	    boost::uint32_t get_loader_flags (void) const;

	    boost::uint32_t get_number_of_rva_and_sizes (void) const;

	    boost::uint32_t get_export_table_address (void) const;

	    boost::uint32_t get_export_table_size (void) const;

	    boost::uint32_t get_import_table_address (void) const;

	    boost::uint32_t get_import_table_size (void) const;

	    boost::uint32_t get_resource_table_address (void) const;

	    boost::uint32_t get_resource_table_size (void) const;

	    boost::uint32_t get_exception_table_address (void) const;

	    boost::uint32_t get_exception_table_size (void) const;

	    boost::uint32_t get_certificate_table_address (void) const;

	    boost::uint32_t get_certificate_table_size (void) const;

	    boost::uint32_t get_base_relocation_table_address (void) const;

	    boost::uint32_t get_base_relocation_table_size (void) const;

	    boost::uint32_t get_debug_table_address (void) const;

	    boost::uint32_t get_debug_table_size (void) const;

	    boost::uint32_t get_architecture_address (void) const;

	    boost::uint32_t get_architecture_size (void) const;

	    boost::uint32_t get_global_ptr_address (void) const;

	    boost::uint32_t get_global_ptr_size (void) const;

	    boost::uint32_t get_thread_local_storage_table_address (void) const;

	    boost::uint32_t get_thread_local_storage_table_size (void) const;

	    boost::uint32_t get_load_config_table_address (void) const;

	    boost::uint32_t get_load_config_table_size (void) const;

	    boost::uint32_t get_bound_import_address (void) const;

	    boost::uint32_t get_bound_import_size (void) const;

	    boost::uint32_t get_import_address_table_address (void) const;

	    boost::uint32_t get_import_address_table_size (void) const;

	    boost::uint32_t get_delay_import_descriptor_address (void) const;

	    boost::uint32_t get_delay_import_descriptor_size (void) const;

	    boost::uint32_t get_clr_runtime_header_address (void) const;

	    boost::uint32_t get_clr_runtime_header_size (void) const;

	    boost::uint32_t get_reserved_address (void) const;

	    boost::uint32_t get_reserved_size (void) const;

	  protected:

	    /* MS_PE_COFF: The unsigned integer that identifies the state
	       of the image file.

	       0x107 identifies it as a ROM image.
	       0x10B identifies it as a normal executable (PE) file.
	       0x20B identifies it as a PE32+ executable.
	    */
	    boost::uint16_t m_magic;

	    // MS_PE_COFF: The linker major version number
	    boost::uint8_t m_major_linker_version;

	    // MS_PE_COFF: The linker minor version number.
	    boost::uint8_t m_minor_linker_version;

	    /* MS_PE_COFF: The size of the code (text) section, or the sum
	       of all code sections if there are multiple sections.
	    */
	    boost::uint32_t m_size_of_code;

	    /* MS_PE_COFF: The size of the initialized data section, or
	       the sum of all such sections if there are multiple data
	       sections.
	    */
	    boost::uint32_t m_size_of_init_data;

	    /* MS_PE_COFF: The size of the uninitialized data section
	       (BSS), or the sum of all such sections if there are
	       multiple BSS sections.
	    */
	    boost::uint32_t m_size_of_uninit_data;

	    /* MS_PE_COFF: The address of the entry point relative to the
	       image base when the executable file is loaded into
	       memory. For program images, this is the starting
	       address. For device drivers, this is the address of the
	       initialization function. An entry point is optional for
	       DLLs. When no entry point is present, this field must be
	       zero.
	    */
	    boost::uint32_t m_addr_of_entry_point;

	    /* MS_PE_COFF: The address that is relative to the image base
	       of the beginning-of-code section when it is loaded into
	       memory.
	    */
	    boost::uint32_t m_base_of_code;

	    /* MS_PE_COFF: The preferred address of the first byte of
	       image when loaded into memory; must be a multiple of 64 K.

	       The default for DLLs is 0x10000000.

	       The default for Windows CE EXEs is 0x00010000.

	       The default for Windows NT, Windows 2000, Windows XP,
	       Windows 95, Windows 98, and Windows Me is 0x00400000.
	    */
	    boost::uint64_t m_image_base;
        
	    /*
	      MS_PE_COFF:

	      The alignment (in bytes) of sections when they are loaded
	      into memory. It must be greater than or equal to
	      FileAlignment.  The default is the page size for the
	      architecture.
	    */
	    boost::uint32_t m_section_alignment;

	    /*
	      MS_PE_COFF:

	      The alignment factor (in bytes) that is used to align the
	      raw data of sections in the image file. The value should be
	      a power of 2 between 512 and 64 K, inclusive.

	      The default is 512.

	      If the SectionAlignment is less than the architecture's page
	      size, then FileAlignment must match SectionAlignment.

	    */
	    boost::uint32_t m_file_alignment;

	    // Major version number of the required operating system.
	    boost::uint16_t m_major_operating_system_version;

	    // Minor version number of the required operating system.
	    boost::uint16_t m_minor_operating_system_version;

	    // Major version number of the image.
	    boost::uint16_t m_major_image_version;

	    // Minor version number of the image.
	    boost::uint16_t m_minor_image_version;

	    // Major version number of the subsystem.
	    boost::uint16_t m_major_subsystem_version;

	    // Minor version number of the subsystem.
	    boost::uint16_t m_minor_subsystem_version;

	    // MS_PE_COFF: Reserved, must be zero.
	    boost::uint32_t m_win32_version_value;

	    /*
	      MS_PE_COFF:

	      The size (in bytes) of the image, including all headers, as
	      the image is loaded in memory. It must be a multiple of
	      SectionAlignment.
	    */
	    boost::uint32_t m_size_of_image;

	    /*
	      MS_PE_COFF:

	      The combined size of an MS-DOS stub, PE header, and section
	      headers rounded up to a multiple of FileAlignment.

	    */
	    boost::uint32_t m_size_of_headers;

	    /*
	      MS_PE_COFF:

	      The image file checksum. The algorithm for computing the
	      checksum is incorporated into IMAGHELP.DLL. The following
	      are checked for validation at load time: all drivers, any
	      DLL loaded at boot time, and any DLL that is loaded into a
	      critical Windows process.
	    */
	    boost::uint32_t m_checksum;

	    /*
	      MS_PE_COFF:

	      The subsystem that is required to run this image.
	    */
	    boost::uint16_t m_subsystem;

	    // DLL characteristics of the image.
	    boost::uint16_t m_dll_characteristics;

	    /*
	      MS_PE_COFF:

	      The size of the stack to reserve.  Only SizeOfStackCommit is
	      committed; the rest is made available one page at a time
	      until the reserve size is reached.

	    */
	    boost::uint64_t m_size_of_stack_reserve;

	    // MS_PE_COFF: The size of the stack to commit.
	    boost::uint64_t m_size_of_stack_commit;

	    /*
	      MS_PE_COFF:

	      The size of the local heap space to reserve. Only
	      SizeOfHeapCommit is committed; the rest is made available
	      one page at a time until the reserve size is reached.

	    */
	    boost::uint64_t m_size_of_heap_reserve;

	    // MS_PE_COFF: The size of the local heap to commit.
	    boost::uint64_t m_size_of_heap_commit;

	    // MS_PE_COFF: Reserved, must be zero
	    boost::uint32_t m_loader_flags;

	    /* MS_PE_COFF: The number of data-directory entries in the
	       remainder of the optional header. Each describes a location
	       and size.
	    */
	    boost::uint32_t m_number_of_rva_and_sizes;

	    /* MS_PE_COFF: The export table (.edata) address and size. */
	    boost::uint32_t m_export_table_address;
	    boost::uint32_t m_export_table_size;

	    /* MS_PE_COFF: The import table (.idata) address and size. */
	    boost::uint32_t m_import_table_address;
	    boost::uint32_t m_import_table_size;

	    /* MS_PE_COFF: The resource table (.rsrc) address and size. */
	    boost::uint32_t m_resource_table_address;
	    boost::uint32_t m_resource_table_size;

	    /* MS_PE_COFF: The exception table (.pdata) address and size. */
	    boost::uint32_t m_exception_table_address;
	    boost::uint32_t m_exception_table_size;

	    /* MS_PE_COFF: The certificate table address and size. */
	    boost::uint32_t m_certificate_table_address;
	    boost::uint32_t m_certificate_table_size;

	    /* MS_PE_COFF: The base relocation table (.reloc) address and size. */
	    boost::uint32_t m_base_relocation_table_address;
	    boost::uint32_t m_base_relocation_table_size;

	    /* MS_PE_COFF: The debug table (.debug) address and size. */
	    boost::uint32_t m_debug_table_address;
	    boost::uint32_t m_debug_table_size;

	    /* MS_PE_COFF: Reserved, must be 0. */
	    boost::uint32_t m_architecture_address;
	    boost::uint32_t m_architecture_size;

	    /* MS_PE_COFF: The RVA of the value to be stored in the global
	       pointer register. The size member of this structure must be
	       set to zero.
	    */
	    boost::uint32_t m_global_ptr_address;
	    boost::uint32_t m_global_ptr_size;

	    /* MS_PE_COFF: The tls table (.tls) address and size. */
	    boost::uint32_t m_thread_local_storage_table_address;
	    boost::uint32_t m_thread_local_storage_table_size;

	    /* MS_PE_COFF: The load config table address and size. */
	    boost::uint32_t m_load_config_table_address;
	    boost::uint32_t m_load_config_table_size;

	    /* MS_PE_COFF: The bound import table address and size. */
	    boost::uint32_t m_bound_import_address;
	    boost::uint32_t m_bound_import_size;

	    /* MS_PE_COFF: The import address table address and size. */
	    boost::uint32_t m_import_address_table_address;
	    boost::uint32_t m_import_address_table_size;

	    /* MS_PE_COFF: The delay import table address and size. */
	    boost::uint32_t m_delay_import_descriptor_address;
	    boost::uint32_t m_delay_import_descriptor_size;

	    /* MS_PE_COFF: The CLR table (.cormeta) address and size. */
	    boost::uint32_t m_clr_runtime_header_address;
	    boost::uint32_t m_clr_runtime_header_size;

	    /* MS_PE_COFF: Reserved, must be 0 */
	    boost::uint32_t m_reserved_address;
	    boost::uint32_t m_reserved_size;

	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse


#endif /* PE_OPTIONAL_HEADER_64_H_ */
