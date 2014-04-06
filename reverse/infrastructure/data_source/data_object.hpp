/*  data_object.h

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

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_OBJECT_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_OBJECT_HPP_INCLUDED

#include <reverse/data_containers/filename.hpp>
#include <reverse/data_containers/control_flow_graph_sequence.hpp>
#include <reverse/data_containers/memory_map.hpp>
#include <reverse/meta/meta_object.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

    class data_object
    {
    public:

      explicit data_object ();

      explicit data_object ( boost::shared_ptr < const data_containers::filename>& data );

      explicit data_object ( boost::shared_ptr < const data_containers::control_flow_graph_sequence>& data );

      explicit data_object ( boost::shared_ptr < const data_containers::memory_map>& data );

      explicit data_object ( data_object const& rhs );

      ~data_object(){}
            
      meta::meta_object::const_ptr_t get_meta() const;

      void set_data ( boost::shared_ptr < const data_containers::filename >& data );

      void set_data ( boost::shared_ptr < const data_containers::control_flow_graph_sequence>& data );

      void set_data ( boost::shared_ptr < const data_containers::memory_map>& data );

      void put_meta ( boost::shared_ptr < const meta::meta_object>& meta_ptr );

      boost::shared_ptr < const data_containers::filename> get_filename ( void ) const;

      boost::shared_ptr < const data_containers::control_flow_graph_sequence> get_control_flow_graph_sequence (void) const;

      boost::shared_ptr < const data_containers::memory_map> get_memory_map () const;

      data_object& operator= ( data_object const& rhs );
            
      void swap ( data_object& rhs );
            
    private:

      boost::shared_ptr < const meta::meta_object> m_meta;
      boost::shared_ptr < const data_containers::filename> m_filename;
      boost::shared_ptr < const data_containers::control_flow_graph_sequence> m_graph;
      boost::shared_ptr < const data_containers::memory_map> m_map;
    };
    
    std::ostream& operator<< ( std::ostream& os, data_object const& rhs );

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_OBJECT_HPP_INCLUDED
