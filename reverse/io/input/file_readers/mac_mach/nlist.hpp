/*  Nlist.h

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

#ifndef NLIST_H
#define NLIST_H

#include <boost/cstdint.hpp>

namespace libreverse
{
    namespace mach_module
    {

        class Nlist
        {
            public:

                /*! \brief Default constructor */
                Nlist();

            private:

                /*! \brief index into the string table */
                boost::uint32_t m_strx;

                /*! \brief A byte value consisting of data accessed using four bit masks

                - N_STAB (0xe0)—If any of these 3 bits are set, the symbol is a symbolic debugging table
                (stab) entry. In that case, the entire n_type field is interpreted as a stab value. See
                /usr/include/mach-o/stab.h for valid stab values.
                - N_PEXT (0x10)—If this bit is on, this symbol is marked as having limited global scope.
                When the file is fed to the static linker, it clears the N_EXT bit for each symbol with the
                N_PEXT bit set. (The ld option -keep_private_externs turns off this behavior.) With Mac
                OS X GCC, you can use the __private_extern__ function attribute to set this bit.
                - N_TYPE (0x0e)—These bits define the type of the symbol.
                - N_EXT (0x01)—If this bit is on, this symbol is an external symbol, a symbol that is either
                defined outside this file or that is defined in this file but can be referenced by other files.

                Values for the N_TYPE field include:
                - N_UNDF (0x0)—The symbol is undefined. Undefined symbols are symbols referenced in
                this module but defined in a different module. The n_sect field is set to NO_SECT.
                - N_ABS (0x2)—The symbol is absolute. The linker does not change the value of an absolute
                symbol. The n_sect field is set to NO_SECT.
                - N_SECT (0xe)—The symbol is defined in the section number given in n_sect.
                - N_PBUD (0xc)—The symbol is undefined and the image is using a prebound value for the
                symbol. The n_sect field is set to NO_SECT.
                - N_INDR ( 0xa)—The symbol is defined to be the same as another symbol. The n_value field
                is an index into the string table specifying the name of the other symbol. When that symbol
                is linked, both this and the other symbol have the same defined type and value.
                */
                boost::uint8_t m_type;

                /*! \brief An integer specifying the number of the section that this symbol can be found in, or NO_SECT
                *         if the symbol is not to be found in any section of this image. The sections are contiguously
                *         numbered across segments, starting from 1, according to the order they appear in the
                *         LC_SEGMENT load commands.
                */
                boost::uint8_t m_sect;

                /*! \brief A 16-bit value providing additional information about the nature of this symbol for non-stab
                symbols. The reference flags can be accessed using the REFERENCE_TYPE mask (0xF) and are
                defined as follows:
                - REFERENCE_FLAG_UNDEFINED_NON_LAZY (0x0)—This symbol is a reference to an external
                 non-lazy (data) symbol.
                - REFERENCE_FLAG_UNDEFINED_LAZY (0x1)—This symbol is a reference to an external lazy
                 symbol—that is, to a function call.
                - REFERENCE_FLAG_DEFINED (0x2)—This symbol is defined in this module.
                - REFERENCE_FLAG_PRIVATE_DEFINED (0x3)—This symbol is defined in this module and is
                 visible only to modules within this shared library.
                - REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY (0x4)—This symbol is defined in another
                 module in this file, is a non-lazy (data) symbol, and is visible only to modules within this
                 shared library.
                - REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY (0x5)—This symbol is defined in another
                 module in this file, is a lazy (function) symbol, and is visible only to modules within this
                 shared library.

                Additionally, the following bits might also be set:
                - REFERENCED_DYNAMICALLY (0x10)—Must be set for any defined symbol that is referenced
                 by dynamic-loader APIs (such as dlsym and NSLookupSymbolInImage) and not ordinary
                 undefined symbol references. The strip tool uses this bit to avoid removing symbols that
                 must exist: If the symbol has this bit set, strip does not strip it.
                - N_DESC_DISCARDED (0x20)—Sometimes used by the dynamic linker at runtime in a fully
                 linked image. Do not set this bit in a fully linked image.
                - N_NO_DEAD_STRIP(0x20)—When set in a relocatable object file (file type MH_OBJECT) on a
                 defined symbol, indicates to the static linker to never dead-strip the symbol. (Note that
                 the same bit (0x20) is used for two nonoverlapping purposes.)
                - N_WEAK_REF (0x40)—Indicates that this undefined symbol is a weak reference. If the dynamic
                 linker cannot find a definition for this symbol, it sets the address of this symbol to 0. The
                 static linker sets this symbol given the appropriate weak-linking flags.
                - N_WEAK_DEF (0x80)—Indicates that this symbol is a weak definition. If the static linker or
                 the dynamic linker finds another (non-weak) definition for this symbol, the weak definition
                 is ignored. Only symbols in a coalesced section (page 23) can be marked as a weak
                 definition.
                */
                boost::uint16_t m_desc;

                /*! \brief An integer that contains the value of the symbol. The format of this value is different for each
                *         type of symbol table entry (as specified by the n_type field). For the N_SECT symbol type,
                *         n_value is the address of the symbol. See the description of the n_type field for information
                *         on other possible values.
                */
                boost::uint32_t m_value;
        };

    } /* namespace mach_module */
} /* namespace libreverse */


#endif /* DYLIB_COMMAND_H */
