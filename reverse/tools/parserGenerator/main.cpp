/*  main.cpp

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

#include "XMLParser.h"
#include "InternalData.h"
#include "TableHandler.h"

using namespace parserGen;
using namespace std;

int main (int*, char**)
{
	XMLParser x_ref;
	boost::shared_ptr<QDomDocument> xmlData = x_ref.parse ("x86_rules.xml");
	
	boost::shared_ptr<InternalData> intData (new InternalData());

	TableHandler t_ref;
	t_ref.handleRequest(xmlData,intData);

	return 0;
}
