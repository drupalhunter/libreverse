/*  DTDHandler.h

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
// C++ Interface: DTDHandler
//
// Description: 
//
//
// Author: Stephen Torri <storri@torri.org>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <qdom.h>
#include "XMLHander.h"

namespace parserGen
{
	class DTDHandler : public XMLHandler
	{
	public:
	        // Collaborator: XMLHandler, main
        	virtual void handleRequest (QDomDocument data);

	private:
		/* Data */
		QDomDocument m_data;

		/* Functions */
		// Collaborator: handleRequest
		void parseDTD (void);
	
		// Collaborator: handleRequest
		void validateData (void);

	};

}