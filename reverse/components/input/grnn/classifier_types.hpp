/*  Classifier_Types.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <string>
#include <map>
#include <vector>

namespace reverse {
  namespace classifier  {

    class Classifier_Algorithm;
    template <typename Data_Type> class Configuration;
    class Configuration_Data;
    class GRNN_Data_Entry;
    class GRNN_Data_Map;
    class Formula_List;
    class Java_Classifier_Algorithm;
    class Java_Training_Data;
    template <typename Data_Type> class Training_Data;
    template <typename Data_Type> class Training_Set;
    class Variable_Map;
    class Windows_Classifier_Algorithm;
    class Windows_Training_Data;
    
  } /* namespace classifier */
  
  namespace classifier_types
  {


    class Classifier_Algorithm
    {
    public:
      typedef boost::shared_ptr <classifier::Classifier_Algorithm> ptr_t;
      typedef boost::shared_ptr <classifier::Classifier_Algorithm const> const_ptr_t;
    };

    template <typename Data_Type>
    class Configuration
    {
    public:
      typedef boost::shared_ptr <classifier::Configuration<Data_Type> > ptr_t;
    };

    class GRNN_Data_Entry
    {
    public:
      typedef boost::shared_ptr <classifier::GRNN_Data_Entry> ptr_t;
      typedef boost::shared_ptr <classifier::GRNN_Data_Entry const> const_ptr_t;
    };

    class GRNN_Data_Map
    {
    public:
      typedef boost::shared_ptr <classifier::GRNN_Data_Map> ptr_t;
      typedef boost::shared_ptr <classifier::GRNN_Data_Map const> const_ptr_t;
    };

    class Java_Classifier_Algorithm
    {
    public:
      typedef boost::shared_ptr <classifier::Java_Classifier_Algorithm> ptr_t;
    };

    class Java_Training_Data
    {
    public:
      typedef boost::shared_ptr <classifier::Java_Training_Data> ptr_t;
    };

    template <typename Data_Type>
    class Training_Data
    {
    public:
      typedef boost::shared_ptr< classifier::Training_Data<Data_Type> > ptr_t;
    };

    class Variable_Map {
    public:
      typedef boost::shared_ptr < classifier::Variable_Map > ptr_t;
      typedef std::map <boost::uint32_t, double> map_type;
    };

    template <typename Data_Type>
    class Training_Set
    {
    public:
      typedef boost::shared_ptr < classifier::Training_Set<Data_Type> > ptr_t;
      typedef std::vector< typename Training_Data<Data_Type>::ptr_t > Data_List_t;
    };

    class Windows_Classifier_Algorithm
    {
    public:
      typedef boost::shared_ptr <classifier::Windows_Classifier_Algorithm> ptr_t;
    };

    class Windows_Training_Data
    {
    public:
      typedef boost::shared_ptr <classifier::Windows_Training_Data> ptr_t;
    };

  } // namespace classifier_types
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_TYPES_HPP_INCLUDED
