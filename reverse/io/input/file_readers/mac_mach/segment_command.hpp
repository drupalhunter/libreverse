/*  Segment_Command.h

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

#ifndef SEGMENT_COMMAND_H
#define SEGMENT_COMMAND_H

#include "Load_Command.h"
#include <string>
#include <vector>
#include "Mach_Types.h"

namespace libreverse
{
    namespace mach_module
    {

        class Segment_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                Segment_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                virtual ~Segment_Command() {}

                virtual void convert ( bool need_convert );

                virtual std::string to_String ( void );

                boost::uint32_t get_Command ();
                
                boost::uint32_t get_Command_Size ();
                
                std::string get_Segment_Name ();

                boost::uint32_t get_Virtual_Memory_Address ();

                boost::uint32_t get_Virtual_Memory_Size ();

                boost::uint32_t get_File_Offset ();

                boost::uint32_t get_File_Size ();

                boost::uint32_t get_Max_Protection ();

                boost::uint32_t get_Init_Protection ();

                boost::uint32_t get_Section_Count ();

                boost::uint32_t get_Flags ();

                void push_back ( mach_types::Section::ptr_t );

            private:

                boost::uint32_t m_cmd;
                boost::uint32_t m_cmdsize;
                std::string m_segname;
                boost::uint32_t m_vmaddr;
                boost::uint32_t m_vmsize;
                boost::uint32_t m_fileoff;
                boost::uint32_t m_filesize;
                boost::uint32_t m_maxprot;
                boost::uint32_t m_initprot;
                boost::uint32_t m_nsects;
                boost::uint32_t m_flags;

                // List of Sections contained in this segment
                typedef std::vector<mach_types::Section::ptr_t> Section_List_t;
                Section_List_t m_sections;
        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* SEGMENT_COMMAND_H */
