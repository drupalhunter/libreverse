/*  PE_Resource_Directory.h

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

#ifndef PE_RESOURCE_DIRECTORY_H_
#define PE_RESOURCE_DIRECTORY_H_

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <vector>
#include "io/input/File_Readers/Base_Header.h"
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

    /*! \brief Windows PE resource directory.
     *
     * All comments and hexidecimal values in this header, marked with
     * MS_PE_COFF, are taken from the Microsoft Portable Executable
     * and // Common Object File Format - Revision 8, May 16, 2006.
     */
    class PE_Resource_Directory : public libreverse::header::Base_Header {
    public:

        friend class PE_File;

        //-------------------------------
        //     LEVEL TYPES
        //-------------------------------
      /*! \brief Constant value tag for the type level */
      static boost::uint8_t const TYPE_LEVEL;

      /*! \brief Constant value tag for the name level */
      static boost::uint8_t const NAME_LEVEL;

      /*! \brief Constant value tag for the language level */
      static boost::uint8_t const LANGUAGE_LEVEL;

      /*!
       * \brief Default Constructor
       */
      PE_Resource_Directory ( boost::uint8_t level = TYPE_LEVEL );

      /*!
       * \brief Default Destructor
       */
      virtual ~PE_Resource_Directory(){}

      /*!
       * \brief Convert the header data into a string representation
       * \return String representation of header data
       */
      virtual std::string to_String (void);

      /*!
       * \brief Convert the bit order of the stored data
       */
      virtual void convert ();

      /*!
       * \brief Return the count of the number of name entries
       *
       * \return Total number of name entries
       */
      boost::uint16_t get_Number_Of_Name_Entries (void) const;

      /*!
       * \brief Return the count of the number of id entries
       *
       * \return Total number of id entries
       */
      boost::uint16_t get_Number_Of_Id_Entries (void) const;

      /*!
       * \brief Add a child PE Resource Directory object to the m_children.
       *
       * \param dir_ptr Child PE Resource Directory object
       *
       * \test Check dir_ptr is not null
       */
      void add_Directory ( wpef_types::PE_Resource_Directory::ptr_t dir_ptr );

      /*!
       * \brief Add a child PE Resource Data Entry object to m_data.
       *
       * \param data_ptr Child PE Resource Data Entry object
       *
       * \test Check data_ptr is not null
       */
      void add_Data ( wpef_types::PE_Resource_Data_Entry::ptr_t data_ptr );

      /*!
       * \brief Set m_name to the value of name
       *
       * \param name Input string name for PE Resource Directory
       *
       * \test name is not empty? Can Resource Directory be nameless?
       */
      void set_Name ( std::string name );

      /*!
       * \brief Set m_id to the value of id
       */
      void set_ID ( boost::uint32_t id );

      /*!
       * \brief Return the present level
       *
       * \param Unsigned integer marking the present level
       */
      boost::uint8_t get_Level (void) const;

      /*!
       * \brief get the start of the m_data
       *
       * \return Constant iterator to the start of m_data
       */
      wpef_types::PE_Resource_Directory::Data_List_t::const_iterator get_Data_Begin (void) const;

      /*!
       * \brief get the end of the m_data
       *
       * \return Constant iterator to the end of m_data
       */
      wpef_types::PE_Resource_Directory::Data_List_t::const_iterator get_Data_End (void) const;

    private:

      /*! \brief MS_PE_COFF: Characteristics Resource flags. This
       *     field is reserved for future use. It is currently set to
       *     zero.
       */
        boost::uint32_t m_characteristics;

      /*! \brief MS_PE_COFF: Time/Date Stamp - The time that the
       *  resource data was created by the resource compiler.
       */
      boost::uint32_t m_time_date_stamp;

        /* MS_PE_COFF: Major Version - The major version number, set
           by the user. */
        boost::uint16_t m_major_version;

        /* MS_PE_COFF: Minor Version - The minor version number, set
           by the user. */
        boost::uint16_t m_minor_version;

        /* MS_PE_COFF: Number of Name Entries - The number of
           directory entries immediately following the table that use
           strings to identify Type, Name, or Language entries
           (depending on the level of the table).
        */
        boost::uint16_t m_num_of_name_entries;

        /* MS_PE_COFF: Number of ID Entries - The number of directory
           entries immediately following the Name entries that use
           numeric IDs for Type, Name, or Language entries.
        */
        boost::uint16_t m_num_of_id_entries;

        /* MS_PE_COFF: This field isn't really part of the
           IMAGE_RESOURCE_DIRECTORY structure. Rather, it's an array of
           IMAGE_RESOURCE_DIRECTORY_ENTRY structures that immediately
           follow the IMAGE_RESOURCE_DIRECTORY strucutre. The number of
           elements in the array is the sum of the NumberOfNamedEntries
           and the NumberOfIdEntries fields. The directory entry
           elements that have name identifiers (rather than integer IDs)
           come first in the array.
        */
        typedef std::vector<wpef_types::PE_Resource_Directory::ptr_t> Children_List_t;
        Children_List_t m_children;

        wpef_types::PE_Resource_Directory::Data_List_t m_data;

        std::string m_name;

        boost::uint32_t m_id;

        boost::uint8_t m_level;
	};

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* PE_RESOURCE_DIRECTORY_H_ */
