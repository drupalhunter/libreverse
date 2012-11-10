/*  Constant_Double_Info.h

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

#ifndef JAVA_CONSTANT_DOUBLE_INFO_H_
#define JAVA_CONSTANT_DOUBLE_INFO_H_

#include "Constant_Pool_Info.h"
#include <boost/enable_shared_from_this.hpp>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace libreverse { namespace java_module {

    /*!
     * \class Constant_Double_Info
     * \date 2007
     * \author Stephen Torri
     */
    class Constant_Double_Info
        : public Constant_Pool_Info,
          public boost::enable_shared_from_this<Constant_Double_Info>
    {
    public:

        friend class Class_File;

        /*!
         * \brief Default Constructor
         */
        Constant_Double_Info();

        /*!
         * \brief Default Destructor
         */
        virtual ~Constant_Double_Info(){}

        virtual std::string to_String (void) const;

        virtual boost::uint8_t get_Tag (void) const;

        virtual void read_Input ( java_types::Class_File::ptr_t file_ptr );

        virtual bool is_Type ( boost::uint8_t id ) const;

	double get_Value() const;

    private:

        boost::uint8_t m_tag;

        /*
         * !\brief The unsigned high_bytes and low_bytes items of the
         * CONSTANT_Double_Info structure together represent the value
         * of the double constant ((double) high_bytes << 32)+low_bytes,
         * where the bytes of each of high_bytes and low_bytes are
         * stored in big_endian (high byte first) order.
         */
        double m_value;

  };

} /* namespace java_module */
} /* namespace libreverse */

#endif /* JAVA_CONSTANT_DOUBLE_INFO_H_ */
