/**
* Copyright 2010  Martin Blumenstingl <darklight.xdarklight@googlemail.com>
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of 
* the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/


#ifndef KOPETEPSYKOPLUGIN_H
#define KOPETEPSYKOPLUGIN_H

#include <kopete/kopeteplugin.h>

#include <QVariant>

namespace Kopete
{
	class Contact;
	class ChatSession;
}

/**
  * the "Psyko" plugin for kopete
  * it causes conversation windows to appear as other users begin to message you
  */
class PsykoPlugin : public Kopete::Plugin
{
	Q_OBJECT
	
	public:
		/**
		  * constructs a new instance of the "Psyko" plugin
		  *
		  * @param parent the parent object
		  * @param args a list of arguments
		  */
		PsykoPlugin(QObject* parent, const QVariantList& args);
		
		/**
		  * returns a pointer to the "Psyko" plugin's instance
		  */
		static PsykoPlugin* self();
		
	protected slots:
		/**
		  * called when the settings were changed
		  */
		void settingsChanged();
		
	private slots:
		/**
		  * a slot which is called when a contact starts or stops typing
		  *
		  * @param contact the contact which started or stopped typing
		  * @param isTyping determines if the user is typing or not
		  */
		void contactSentTypingMessage(const Kopete::Contact* contact, bool isTyping);
		
		/**
		  * a slot shich is called when a chat session is closed
		  *
		  * @param chatSession the chat session which was just closed
		  */
		void chatSessionClosing(Kopete::ChatSession* chatSession);
		
		/**
		  * a slot shich is called when a chat session is created
		  *
		  * @param chatSession the chat session which was just created
		  */
		void chatSessionCreated(Kopete::ChatSession* chatSession);
	
	private:
		/**
		  * initializes the plugin
		  */
		void initializePlugin();
		
		/**
		  * determines if the given contact is online or not
		  *
		  * @param contact the contact which should be checked
		  *
		  * @returns true the user has the status @see Kopete::OnlineStatus::Online
		  */
		bool userIsAvailable(const Kopete::Contact* contact);
		
		bool m_showMessageInChatWindow;
		bool m_disableWhenNotAvailable;
		QString m_chatWindowMessage;
		
		static PsykoPlugin* m_instance;
};

#endif
