/*  Reverse_Impl.h

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

#ifndef REVERSE_REVERSE_IMPL_HPP_INCLUDED
#define REVERSE_REVERSE_IMPL_HPP_INCLUDED

#include <reverse/infrastructure/component_graph.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace infrastructure {

    class component;

    namespace data_source {
      
      class data_source_base;

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

namespace reverse {

  /*!
   * \class Reverse_Impl
   *
   * \brief This class handles the all the real actions of the interface.
   *
   * \date 2003
   *
   * \author Stephen Torri
   */
  class reverse_impl
  {
	  
  public:

    typedef std::pair < boost::shared_ptr < infrastructure::data_source::data_source_base >,
			boost::shared_ptr < infrastructure::component > >
    return_type_t;

    /*!
     * \brief default constructor
     */
    explicit reverse_impl();

    /*!
     * \brief default destructor
     */
    ~reverse_impl();

    /*!
     * \brief perform the actions for the input section.
     *
     * \param m_graph the component graph associated with the input section.
     * \param init_data_ptr input data source associated with the root node of the component graph. at present this is only a string file name
     * \param init_comp_ptr component that will be the provider for the input to the root node
     * \return return the data source from the last component in the component_graph along with the pointer to the last component
     */
    return_type_t
    execute_input_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
			    boost::shared_ptr < infrastructure::data_source::data_source_base > init_data_ptr,
			    boost::shared_ptr < infrastructure::component > init_comp_ptr );

    return_type_t
    execute_analysis_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
			       return_type_t& input_results );
            
    void execute_output_section ( boost::shared_ptr < infrastructure::component_graph::map_t > m_graph,
				  return_type_t& analysis_results );

  private:

    void print_graph ( infrastructure::component_graph const& graph_ref,
		       std::string name ) const;

    boost::shared_ptr < infrastructure::data_source::data_source_base >
    process_graph ( boost::shared_ptr < const infrastructure::component_graph > graph_ptr,
		    boost::shared_ptr < infrastructure::data_source::data_source_base > val ) const;
  };

} // namespace reverse

#endif // #ifndef REVERSE_REVERSE_IMPL_HPP_INCLUDED

