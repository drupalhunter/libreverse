/*  Component_Factory.cpp

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

#include "Component_Factory.h"
#include "Null_Component.h"

#include "components/input/Compiler_Classifier.h"
#include "components/input/File_Type_Detector.h"
#include "components/input/Arch_Type_Detector.h"
#include "components/input/Unpacker.h"
#include "components/input/Code_Section_Detector.h"
#include "components/input/Data_Section_Detector.h"
#include "components/input/Entry_Point_Detector.h"
#include "components/input/Memory_Map_Producer.h"
#include "components/input/File_Header_Printer.h"
#include "components/input/Tevis_Zero_Filled_Checker.h"
#include "components/input/Tevis_Unknown_Region_Checker.h"
#include "components/output/Meta_Writer.h"
#include "Create.h"

#include "errors/Internal_Exception.h"

#include <boost/format.hpp>

using namespace libreverse::alloc;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace infrastructure {

    infrastructure_types::Component::ptr_t
    Component_Factory::get_File_Type_Detector ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_File_Type_Detector" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::File_Type_Detector> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Arch_Type_Detector ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Arch_Type_Detector" );
#endif /* LIBREVERSE_DEBUG */
                
      return Create::shared_pointer<component::Arch_Type_Detector> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Unpacker ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Unpacker" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Unpacker> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Meta_Writer ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Meta_Writer" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Meta_Writer> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Code_Section ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Code_Section" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Code_Section_Detector> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Data_Section ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Data_Section" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Data_Section_Detector> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Entry_Point ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Entry_Point" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Entry_Point_Detector> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Null_Component ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Null_Component" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Null_Component> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Memory_Map_Producer ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Memory_Map_Producer" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Memory_Map_Producer> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_File_Header_Printer ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_File_Header_Printer" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::File_Header_Printer> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Tevis_Zero_Filled_Checker ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Tevis_Zero_Filled_Checker" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Tevis_Zero_Filled_Checker> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Tevis_Unknown_Region_Checker ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Tevis_Unknown_Region_Checker" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Tevis_Unknown_Region_Checker> ( state_ptr );
    }

    infrastructure_types::Component::ptr_t
    Component_Factory::get_Compiler_Classifier ( infrastructure_types::Component_State::ptr_t state_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::COMPONENTS,
			   TraceLevel::DETAIL,
			   "Inside Component_Factory::get_Compiler_Classifier" );
#endif /* LIBREVERSE_DEBUG */

      return Create::shared_pointer<component::Compiler_Classifier> ( state_ptr );
    }


} /* namespace infrastructure */
} /* namespace libreverse */
