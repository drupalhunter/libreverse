/*  Meta_Object.cpp

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

#include "Meta_Object.h"
#include <sstream>
#include "errors/Configuration_Exception.h"
#include <boost/format.hpp>
#include "Trace.h"
#include "Assert.h"

using namespace libreverse::api;
using namespace libreverse::assert;
using namespace libreverse::trace;

namespace libreverse { namespace meta {

    boost::uint8_t const Meta_Object::STRING = 0;
    boost::uint8_t const Meta_Object::HEX = 1;

    Meta_Object::Meta_Object ( void )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object constructor" );
    }

    Meta_Object::Meta_Object ( Meta_Object const& rhs )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object copy constructor" );

        /*
          std::string key = "";
          std::string value = "";
          boost::uint8_t type = 0;

          for ( Data_t::const_iterator cpos = rhs.m_info_map.begin();
          cpos != rhs.m_info_map.end();
          cpos++ )
          {
          key = std::string ( (*cpos).first );
          
          Data_Pair_t pair_ref = (*cpos).second;
          value = std::string ( pair_ref.first );
          type = ( pair_ref.second );
              
          this->add ( key, value, type );
          }
        */
        std::copy ( rhs.m_info_map.begin(),
                    rhs.m_info_map.end(),
                    std::inserter ( m_info_map, m_info_map.begin() ) );

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object copy constructor" );

    }

    void
    Meta_Object::add ( std::string key,
                       std::string value,
                       boost::uint8_t type )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::add" );

        Assert::bool_check ( ! key.empty(), "Key must not be empty" );
        Assert::bool_check ( ! value.empty(), "Input value must not be empty" );
        Assert::bool_check ( this->is_Valid_Type ( type ), "Input type must be an a valid type" );

        Data_Pair_t data = std::make_pair ( value, type );

        std::pair<Meta_Object::iterator,bool> result =
            m_info_map.insert ( std::make_pair ( key, data ) );

        Assert::bool_check ( result.second, "Insertion must be complete without error." );

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::add" );
    }

    void
    Meta_Object::append ( Meta_Object::const_ptr_t meta_ptr )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::append" );

        Assert::null_check ( meta_ptr.get(), "Input meta_ptr must not be NULL" );

        m_info_map.insert ( meta_ptr->begin(),
                            meta_ptr->end() );

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::append" );
    }

    Meta_Object::Data_Pair_t
    Meta_Object::get_Value ( std::string key ) const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::get_Value" );

        Data_t::const_iterator pos = m_info_map.find ( key );

        if ( pos != m_info_map.end() )
            {
                Meta_Object::Data_Pair_t data = pos->second;
                assert ( ! (data.first).empty() );
                assert ( this->is_Valid_Type ( data.second ) );

                return data;
            }
        else
            {
                Trace::write_Trace ( TraceArea::META,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format ( "Meta_Object::get_Value - unknown key: %s" )
                                                  % key ));

                throw errors::Meta_Exception
                    ( errors::Meta_Exception::INVALID_KEY );
            }

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::get_Value" );
    }

    Meta_Object::iterator
    Meta_Object::begin (void)
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object::begin" );

        return m_info_map.begin();
    }

    Meta_Object::const_iterator const
    Meta_Object::begin (void) const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object::begin (const)" );

        return m_info_map.begin();
    }

    Meta_Object::iterator
    Meta_Object::end (void)
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object::end" );

        return m_info_map.end();
    }

    Meta_Object::const_iterator const
    Meta_Object::end (void) const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object::end (const)" );

        return m_info_map.end();
    }

    Meta_Object::size_t
    Meta_Object::size (void) const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Inside Meta_Object::size" );

        return m_info_map.size();
    }


    std::string
    Meta_Object::to_String () const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::to_String" );

        std::stringstream output;

        if ( ! m_info_map.empty() )
            {

                output << "-----------------------" << std::endl
                       << "      Meta_Object" << std::endl
                       << "-----------------------" << std::endl;

                for ( Data_t::const_iterator pos = m_info_map.begin();
                      pos != m_info_map.end();
                      pos++ )
                    {
                        Data_Pair_t data = pos->second;

                        switch ( data.second )
                            {
                            case HEX:
                                {
                                    output << boost::format ( "%1% = %2$X" ) %
                                        pos->first %
                                        this->convert_To_UInt32 ( data.first )
                                           << std::endl;
                                    break;
                                }
                            case STRING:
                            default:
                                {
                                    output << boost::format ( "%1% = %2%" ) %
                                        pos->first %
                                        data.first
                                           << std::endl;
                                }
                            }
                    }
            }

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::to_String" );

        return output.str();
    }

    bool
    Meta_Object::is_Valid_Type ( boost::uint8_t type ) const
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::is_Valid_Type" );

        bool result = false;

        switch ( type )
            {
            case STRING:
            case HEX:
                result = true;
                break;
            default:
                result = false;
            }

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::is_Valid_Type" );

        return result;
    }

    Meta_Object&
    Meta_Object::operator= ( Meta_Object const& rhs )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::operator=" );


        Meta_Object temp ( rhs );
        swap ( temp );

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::operator=" );

        return *this;
    }

    void
    Meta_Object::swap ( Meta_Object& rhs )
    {
        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Entering Meta_Object::swap" );

        m_info_map.swap ( rhs.m_info_map );

        Trace::write_Trace ( TraceArea::META,
                             TraceLevel::DETAIL,
                             "Exiting Meta_Object::swap" );
    }

} /* namespace meta */
} /* namespace libreverse */
