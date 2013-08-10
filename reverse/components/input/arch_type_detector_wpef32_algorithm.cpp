/*  Arch_Type_Detector_WPEF32_Algorithm.cpp

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

#include <reverse/components/input/arch_type_detector_wpef32_algorithm.hpp>
#include <reverse/io/input/file_readers/windows_pe/reader_32.hpp>
#include <reverse/trace.hpp>

#include <boost/make_shared.hpp>

namespace reverse
{
    namespace component
    {
        namespace input
        {

            std::string
            arch_type_detector_wpef32_algorithm::run ( boost::shared_ptr < const io::file_id > file_ptr )
            {
                trace::components_detail ( "Entering Arch_Type_Detector_WPEF32_Algorithm::run" );

                boost::shared_ptr < io::input::file_readers::windows_pe::reader_32 > file_reader_ptr =
                    boost::make_shared < io::input::file_readers::windows_pe::reader_32 > ( file_ptr );

                std::string result = file_reader_ptr->get_arch_type ();


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::COMPONENTS,
                                     TraceLevel::DETAIL,
                                     "Exiting Arch_Type_Detector_WPEF32_Algorithm::run" );
#endif /* LIBREVERSE_DEBUG */


                return result;
            }

        } // namespace input
    } /* namespace component */
} /* namespace reverse */

