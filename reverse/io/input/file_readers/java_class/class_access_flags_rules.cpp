/*  Class_Access_Flags_Rules.cpp

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

#include "Class_Access_Flags_Rules.h"
#include "Class_Access_Flags.h"

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    bool
    Class_Access_Flags_Rules::validate_Flags ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::validate_Flags" );
#endif /* LIBREVERSE_DEBUG */


        bool result = true;

	/*
        // Is this class file an interface?
        if ( ! ( is_Interface ( value ) &&
                 is_Abstract ( value ) &&
                 ! is_Super ( value ) &&
                 ! is_Final ( value ) &&
                 are_Non_Assigned_Bits_Clear ( value ) ) )
            {
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "FAILED: Checked if class was an interface" );

	      result = false;
            }
        else if (! ( is_Super ( value ) &&
                     ! is_Interface ( value ) &&
                     are_Non_Assigned_Bits_Clear ( value ) ) )
            {
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "FAILED: Checked if class was not an interface" );
	      
	      result = false;
            }
	*/

	// Rule 1: Check to see if the flags are for an interface
	//         ACC_INTERFACE
	//   Rule 1a: ACC_ABSTRACT & !ACC_FINAL & !ACC_SUPER & !ACC_ENUM
	//   Rule 1b: Check to see if the ACC_ANNOTATION is set
	// Rule 2: Check to see if the flags are not for an interface
	//         !ACC_ANNOTATION

	// Rule 3: Check both ACC_FINAL and ACC_ABSTRACT are not both set

	if ( is_Interface ( value ) )
	  {
	    if ( is_Abstract ( value ) &&
		 ( ! is_Final ( value ) ) &&
		 ( ! is_Super ( value ) ) &&
		 ( ! is_Enum ( value ) ) )
	      {
		// VALID
		result = true;
	      }
	    else
	      {
		// INVALID
		result = false;
	      }

	    if ( is_Annotation ( value ) &&
		 result )
	      {
		// VALID
		result = true;
	      }
	  }
	else
	  {
	    if ( ( ! is_Final ( value ) ) &&
		 ( ! is_Abstract ( value ) ) )
	      {
		// VALID
		result = true;
	      }
	    else
	      {
		// INVALID
		result = false;
	      }
	  }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::validate_Flags" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Interface ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Interface" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( value & Class_Access_Flags::ACC_INTERFACE )
            {
                result = true;

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     "is_Interface: TRUE" );
#endif /* LIBREVERSE_DEBUG */

	  }

#ifdef LIBREVERSE_DEBUG
	else
	  {
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "is_Interface: FALSE" );
	  }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Interface" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Abstract ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Abstract" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( value & Class_Access_Flags::ACC_ABSTRACT )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Abstract" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Public ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Public" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( value & Class_Access_Flags::ACC_PUBLIC )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Public" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Final ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Final" );
#endif /* LIBREVERSE_DEBUG */

        bool result = false;

        if ( value & Class_Access_Flags::ACC_FINAL )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Final" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Super ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Super" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( value & Class_Access_Flags::ACC_SUPER )
	  {
	    result = true;


#ifdef LIBREVERSE_DEBUG
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "is_Super: TRUE" );
#endif /* LIBREVERSE_DEBUG */

	  }

#ifdef LIBREVERSE_DEBUG
	else
	  {
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "is_Super: FALSE" );
	  }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Super" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    bool
    Class_Access_Flags_Rules::are_Non_Assigned_Bits_Clear ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::are_Non_Assigned_Bits_Clear" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

	boost::uint16_t reserved = ~ ( Class_Access_Flags::ACC_PUBLIC &
				       Class_Access_Flags::ACC_FINAL &
				       Class_Access_Flags::ACC_SUPER &
				       Class_Access_Flags::ACC_INTERFACE &
				       Class_Access_Flags::ACC_ABSTRACT &
				       Class_Access_Flags::ACC_SYNTHETIC &
				       Class_Access_Flags::ACC_ANNOTATION &
				       Class_Access_Flags::ACC_ENUM );

        if ( ( value & reserved ) == 0 )
            {
                result = true;

#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     "Non Assigned Bits are clear: TRUE" );
#endif /* LIBREVERSE_DEBUG */

	  }

#ifdef LIBREVERSE_DEBUG
	else
	  {
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "Non Assigned Bits are clear: FALSE" );
	  }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::are_Non_Assigned_Bits_Clear" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Annotation ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Annotation" );
#endif /* LIBREVERSE_DEBUG */

        bool result = false;

        if ( value & Class_Access_Flags::ACC_ANNOTATION )
            {
                result = true;


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     "is_Annotation: TRUE" );
#endif /* LIBREVERSE_DEBUG */

	  }

#ifdef LIBREVERSE_DEBUG
	else
	  {
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "is_Annotation: FALSE" );
	  }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Annotation" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    bool
    Class_Access_Flags_Rules::is_Enum ( boost::uint16_t value )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Access_Flags_Rules::is_Enum" );
#endif /* LIBREVERSE_DEBUG */


        bool result = false;

        if ( value & Class_Access_Flags::ACC_ENUM )
            {
                result = true;


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
				     TraceLevel::DATA,
				     "is_Enum: TRUE" );
#endif /* LIBREVERSE_DEBUG */

	  }

#ifdef LIBREVERSE_DEBUG
	else
	  {
	    Trace::write_Trace ( TraceArea::IO,
				 TraceLevel::DATA,
				 "is_Enum: FALSE" );
	  }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Access_Flags_Rules::is_Enum" );
#endif /* LIBREVERSE_DEBUG */

        return result;
    }
} /* namespace java_module */
} /* namespace reverse */
