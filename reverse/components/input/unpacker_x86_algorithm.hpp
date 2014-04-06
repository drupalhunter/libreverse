/*  Unpacker_X86_Algorithm.h

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

#ifndef UNPACKER_X86_ALGORITHM_H
#define UNPACKER_X86_ALGORITHM_H

#include "Unpacker_Algorithm.h"
#include "meta/meta_object.h"

namespace reverse { namespace component {

    /*!
     * \brief Implements the Unpacking algorithm for x86 binaries
     */
    class Unpacker_X86_Algorithm : public Unpacker_Algorithm {
    public:

      /*!
       * \brief Default Constructor
       */
      Unpacker_X86_Algorithm();

      /*!
       * \brief Unpacks the original image by executing the code instructions.
       *
       * \todo Idea (Dr Homer Carlisle): there cannot be that many
       * compression algorithms out there in the wild. Hand reverse
       * engineer them and then just unpack the origianl
       * image. Research would be required to 1) Find the algorithms.
       * 2) Determine mechanism that can classify a binary image as
       * being compressed with which algorithm. It would be important
       * to be able to do this by reading the file header and with
       * only the binary stream. 3) Select appropriate algorithm. 4)
       * Unpack image.
       *
       * \param meta_ptr Input meta information (contains entry point)
       * \param file_map_ptr Compression binary image
       *
       * \return Uncompressed binary image
       */
      virtual data_types::memory_map::const_ptr_t run ( meta::meta_object::const_ptr_t meta_ptr,
							data_types::memory_map::const_ptr_t file_map_ptr );

      /*!
       * \brief Print input image to standard out
       *
       * \todo It would be nice to save this to a file, create a
       * image, or produce an object that could be displayed in a GUI.
       */
      virtual void print_Color_Map (void);

      /*!
       * \brief Return the output meta information
       *
       * \return Meta object that contains information from the input
       * Meta object and any new information added by this component.
       */
      infrastructure_types::Component::Meta_List_t get_Meta_Input_List_Impl (void);

    private:

      /*!
       * \brief Create the color map from the binary image
       */
      void create_Color_Map (void);

      //------------------------------
      //         CONSTANTS
      //------------------------------
      enum COLOR_VALUE {
	WHITE = 0,
	RED,
	GREEN
      };

      /*! \brief Text string for red color */
      static const std::string RED_STRING;

      /*! \brief Text string for green color */
      static const std::string GREEN_STRING;

      /*! \brief Text string for white color */
      static const std::string WHITE_STRING;

      //------------------------------
      //         TYPES
      //------------------------------
      /*! \brief key is the index to the memory map for the correct
       *  value. Data is the color used when printing
       */
      typedef std::map<boost::uint32_t, COLOR_VALUE> Color_Map_t;

      //------------------------------
      //         VARIABLES
      //------------------------------
      /*! \brief Color map for the binary image. Since we are marking
       * each byte the size of the color map equals the size of the
       * binary image
       */ 
      Color_Map_t m_color_map;

      /*! \brief Pointer to the input binary image */
        data_types::memory_map::const_ptr_t m_file_map;

      /*! \brief Index where the code starts */
      boost::uint32_t m_code_offset;

      /*! \brief Length of code section */
      boost::uint32_t m_code_length;

      /*! \brief Index where the data section starts */
      boost::uint32_t m_data_offset;

      /*! \brief Length of data section */
      boost::uint32_t m_data_length;

      /*! \brief Entry point into the program. */
      boost::uint32_t m_entry_point;

      /*! \brief Base address of the image */
      boost::uint32_t m_base_address;
    };

} /* namespace component */
} /* namespace reverse */

#endif /* UNPACKAGE_X86_ALGORITHM_H */
