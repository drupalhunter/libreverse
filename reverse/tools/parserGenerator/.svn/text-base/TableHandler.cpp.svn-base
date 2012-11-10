/*  TableHandler.cpp

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
// C++ Implementation: TableHandler
//
// Description:
//
//
// Author: Stephen Torri <storri@torri.org>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "TableHandler.h"
#include <iostream>

namespace parserGen
{

void
TableHandler::handleRequest ( boost::shared_ptr<QDomDocument> xmlData,
                              boost::shared_ptr<InternalData> intData )
{
    // Do work here
    std::cout << xmlData->toString() << std::endl;

    // Call next member in the chain
    if ( m_successor.get() != 0 )
    {
        m_successor->handleRequest( xmlData, intData );
    }

}

}
