/*  Dysymtab_Command.h

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

#ifndef DYSYMTAB_COMMAND_H
#define DYSYMTAB_COMMAND_H

#include "Load_Command.h"

namespace reverse
{
    namespace mach_module
    {

        class Dysymtab_Command : public Load_Command
        {
            public:

                friend class Mach_File;

                /*!
                 * \brief Default Constructor
                 *
                 * \param cmd  cmd Unsigned integer (LC_DYSYMTAB)
                 * \param cmdsize Size of this command
                 */
                Dysymtab_Command ( boost::uint32_t cmd, boost::uint32_t cmdsize );

                /*! \brief Default Constructor */
                virtual ~Dysymtab_Command() {}

                /*!
                 * \brief Convert the byte order of the command values
                 *
                 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
                 */
                virtual void convert ( bool need_convert );

                /*!
                 * \brief Return a formatted string representation of the Dysymtab_Command
                 *
                 * \return Formatted output string of Dysymtab_Command object
                 */
                virtual std::string to_String ( void );

            private:

                /*! \brief Common to all load command structures. For this structure, set to LC_DYSYMTAB. */
                boost::uint32_t m_cmd;

                /*! \brief Common to all load command structures. For this structure, set to sizeof(dysymtab_command). */
                boost::uint32_t m_cmdsize;

                /*! \brief An integer indicating the index of the first symbol in the group of local symbols. */
                boost::uint32_t m_ilocalsym;

                /*! \brief An integer indicating the total number of symbols in the group of local symbols. */
                boost::uint32_t m_nlocalsym;

                /*! \brief An integer indicating the index of the first symbol in the group of defined external symbols. */
                boost::uint32_t m_iextdefsym;

                /*! \brief An integer indicating the total number of symbols in the group of defined external symbols. */
                boost::uint32_t m_nextdefsym;

                /*! \brief An integer indicating the index of the first symbol in the group of undefined external symbols. */
                boost::uint32_t m_iundefsym;

                /*! \brief An integer indicating the total number of symbols in the group of undefined external symbols. */
                boost::uint32_t m_nundefsym;

                /*! \brief An integer indicating the byte offset from the start of the file to the table of contents data. */
                boost::uint32_t m_tocoff;

                /*! \brief An integer indicating the number of entries in the table of contents. */
                boost::uint32_t m_ntoc;

                /*! \brief An integer indicating the byte offset from the start of the file to the module table data. */
                boost::uint32_t m_modtaboff;

                /*! \brief An integer indicating the number of entries in the module table. */
                boost::uint32_t m_nmodtab;

                /*! \brief An integer indicating the byte offset from the start of the file to the external reference table
                 *         data.
                 */
                boost::uint32_t m_extrefsymoff;

                /*! \brief An integer indicating the number of entries in the external reference table. */
                boost::uint32_t m_nextrefsyms;

                /*! \brief An integer indicating the byte offset from the start of the file to the indirect symbol table data. */
                boost::uint32_t m_indirectsymoff;

                /*! \brief An integer indicating the number of entries in the indirect symbol table. */
                boost::uint32_t m_nindirectsyms;

                /*! \brief An integer indicating the byte offset from the start of the file to the external relocation table
                 * data.
                 */
                boost::uint32_t m_extreloff;

                /*! \brief An integer indicating the number of entries in the external relocation table. */
                boost::uint32_t m_nextrel;

                /*! \brief An integer indicating the byte offset from the start of the file to the local relocation table data. */
                boost::uint32_t m_localref;

                /*! \brief An integer indicating the number of entries in the local relocation table. */
                boost::uint32_t m_nlocrel;

        };

    } /* namespace mach_module */
} /* namespace reverse */


#endif /* DYSYMTAB_COMMAND_H */
