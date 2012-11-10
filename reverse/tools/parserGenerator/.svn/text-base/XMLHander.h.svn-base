/*  XMLHander.h

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

//
// C++ Interface: XMLHander
//
// Description:
//
//
// Author: Stephen Torri <storri@torri.org>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
// DESIGN: Using chain of command design pattern

#include <qdom.h>
#include <boost/shared_ptr.hpp>

namespace parserGen
{
    class InternalData;

    class XMLHandler
    {
    protected:
        boost::shared_ptr<XMLHandler> m_successor;

    public:
        // Collaborator: main
        void setSuccessor (boost::shared_ptr<XMLHandler> successor);

        // Collaborator: XMLHandler, main
        virtual void handleRequest (boost::shared_ptr<QDomDocument> xmlData,
				    boost::shared_ptr<InternalData> intData) = 0;
    };

}
