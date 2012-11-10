/*  Load_Command_Constants.h

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

#ifndef LOAD_COMMAND_CONSTANTS_H
#define LOAD_COMMAND_CONSTANTS_H

namespace libreverse
{
    namespace mach_module
    {
        class Load_Command_Constants
        {
        public:
            enum Values {
                LC_REQ_DYLD = 0x80000000,
                LC_SEGMENT = 0x1,              /*! \brief File segment to be mapped into memory */
                LC_SYMTAB = 0x2,               /*! \brief Link-edit stab symbol table info (Obsolete) */
                LC_SYMSEG = 0x3,               /*! \brief Link-edit gdb symbol table info */
                LC_THREAD = 0x4,               /*! \brief Thread */
                LC_UNIXTHREAD = 0x5,           /*! \brief UNIX thread (includes a stack) */
                LC_LOADFVMLIB = 0x6,           /*! \brief Load a fixed VM shared library */
                LC_IDFVMLIB = 0x7,             /*! \brief Fixed VM shared library ID */
                LC_IDENT = 0x8,                /*! \brief Object identification information (Obsolete) */
                LC_FVMFILE = 0x9,              /*! \brief Fixed VM file inclusion (a.k.a LC_LOADFVMFILE ) */
                LC_PREPAGE = 0xA,
                LC_DYSYMTAB = 0xB,             /*! \brief Additional symbol table information used by the dynamic linker */
                LC_LOAD_DYLIB = 0xC,           /*! \brief Name of a dynamic shared library that the file links against */
                LC_ID_DYLIB = 0xD,             /*! \brief Specifies the install name of a dynamic shared library */
                LC_LOAD_DYLINKER = 0xE,        /*! \brief Specifies the dynamic linker that the kernel executes to load this file */
                LC_ID_DYLINKER = 0xF,          /*! \brief Identifies this file as a dynamic linker */
                LC_PREBOUND_DYLIB = 0x10,      /*! \brief Specifies the modules in the linked prebound shared library that are used */
                LC_ROUTINES = 0x11,            /*! \brief Contains the address of the shared library initialization routine */
                LC_SUB_FRAMEWORK = 0x12,       /*! \brief Identifies this file as the implementation of a subframework of an umbrella framework */
                LC_SUB_UMBRELLA = 0x13,        /*! \brief Specifies a file that is a subumbrella of this umbrella framework */
                LC_SUB_CLIENT = 0x14,          /*! \brief A subframework can explicitly allow another framework or bundle to link against it by
                                                  including an LC_SUB_CLIENT load command containing the name of the framework or a
                                                  client name for a bundle */
                LC_SUB_LIBRARY = 0x15,         /*! \brief Identifies this file as the implementation of a sublibrary of an umbrella framework */
                LC_TWOLEVEL_HINTS = 0x16,      /*! \brief Contains the two-level namespace lookup hint table */
                LC_PREBIND_CKSUM = 0x17,
                LC_LOAD_WEAK_DYLIB = ( 0x18 | LC_REQ_DYLD ),
                LC_SEGMENT_64 = 0x19,          /*! \brief Defines a 64-bit segment of this file to be mapped into the address space of the process
                                                  that loads this file */
                LC_ROUTINES_64 = 0x1A,         /*! \brief Contains the address of the shared library 64-bit initialization routine */
                LC_UUID = 0x1B                 /*! \brief Specifies the 128-bit UUID for an image or its corresponding dSYM file */
            };
        };

    } /*! \brief namespace mach_module */
} /*! \brief namespace libreverse */


#endif /*! \brief LOAD_COMMAND_CONSTANTS_H */
