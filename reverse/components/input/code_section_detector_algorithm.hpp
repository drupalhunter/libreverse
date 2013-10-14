/*  Code_Section_Detector_Algorithm.h

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

#ifndef REVERSE_COMPONENT_CODE_SECTION_DETECTOR_ALGORITHM_HPP_INCLUDED
#define REVERSE_COMPONENT_CODE_SECTION_DETECTOR_ALGORITHM_HPP_INCLUDED

#include <reverse/meta/meta_object.hpp>

namespace reverse {

  namespace io {
    class file_id;
  } // namespace io

  namespace component {

    class code_section_detector_algorithm {
    public:
      
      typedef boost::shared_ptr<code_section_detector_algorithm> ptr_t;
      
      virtual ~code_section_detector_algorithm(){}
      
      virtual boost::shared_ptr < meta::meta_object > run ( boost::shared_ptr < const io::file_id > file_ptr ) = 0;
    };
    
  } /* namespace component */
} /* namespace reverse */

#endif // ifndef REVERSE_COMPONENT_CODE_SECTION_DETECTOR_ALGORITHM_HPP_INCLUDED
