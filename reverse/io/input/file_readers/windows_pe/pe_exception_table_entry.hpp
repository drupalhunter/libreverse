/*  PE_Exception_Table_Entry.h

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

#ifndef PE_EXCEPTION_TABLE_ENTRY_H_
#define PE_EXCEPTION_TABLE_ENTRY_H_

/*
  All comments and hexidecimal values in this header, marked with
  MS_PE_COFF, are taken from the Microsoft Portable Executable and //
  Common Object File Format - Revision 8, May 16, 2006.
*/
#include <reverse/io/input/File_Readers/Base_Header.h>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace windows_pe {

	  class PE_Exception_Table_Entry : public Base_Header
	  {
	  public:

	    friend class PE_File;

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~PE_Exception_Table_Entry(){}

	    virtual void read_Entry ( wpef_types::PE_File::ptr_t file_ptr ) = 0;
	
	  };

	} // namespace windows_pe
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse



#endif /* PE_RESOURCE_ENTRY_H_ */
