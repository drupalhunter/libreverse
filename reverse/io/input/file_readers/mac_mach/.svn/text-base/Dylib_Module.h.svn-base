/*  Dylib_Module.h

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

#ifndef DYLIB_MODULE_H
#define DYLIB_MODULE_H

#include <boost/cstdint.hpp>

namespace libreverse { namespace mach_module {

  class Dylib_Module {
  public:

    Dylib_Module();

  private:

    /*! \brief An index to an entry in the string table indicating the name of the module */
    boost::uint32_t m_module_name;

    /*! \brief The index into the symbol table of the first defined external symbol provided by this module */
    boost::uint32_t m_iextdefsym;

    /*! \brief The number of defined external symbols provided by this module */
    boost::uint32_t m_nextdefsym;

    /*! \brief The index into the external reference table of the first entry provided by this module. */
    boost::uint32_t m_irefsym;

    /*! \brief The number of external reference entries provided by this module. */
    boost::uint32_t m_nrefsym;

    /*! \brief The index into the symbol table of the first local symbol provided by this module. */
    boost::uint32_t m_ilocalsym;

    /*! \brief The number of local symbols provided by this module. */
    boost::uint32_t m_nlocalsym;

    /*! \brief The index into the external relocation table of the first entry provided by this module. */
    boost::uint32_t m_iextrel;

    /*! \brief The number of entries in the external relocation table that are provided by this module. */
    boost::uint32_t m_nextrel;

    /*! \brief Contains both the index into the module initialization section (the low 16 bits) and the index
     *         into the module termination section (the high 16 bits) to the pointers for this module.
     */
    boost::uint32_t m_iinit_iterm;

    /*! \brief Contains both the number of pointers in the module initialization (the low 16 bits) and the
     *         number of pointers in the module termination section (the high 16 bits) for this module.
     */
    boost::uint32_t m_ninit_iterm;

    /*! \brief The statically linked address of the start of the data for this module in the __module_info
     *         section in the __OBJC segment.
     */
    boost::uint32_t m_objc_module_info_addr;

    /*! \brief The number of bytes of data for this module that are used in the __module_info section in the
     *         __OBJC segment.
     */
    boost::uint32_t m_objc_module_info_size;

  };

} /* namespace mach_module */
} /* namespace libreverse */


#endif /* DYLIB_MODULE_H */
