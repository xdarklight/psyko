#ifndef KOPETEPSYKOPLUGIN_H
#define KOPETEPSYKOPLUGIN_H

#include <kopete/kopeteplugin.h>

#include <QVariant>

namespace Kopete
{
	class Contact;
	class ChatSession;
}

class PsykoPlugin : public Kopete::Plugin
{
	Q_OBJECT
	
	public:
		PsykoPlugin(QObject* parent, const QVariantList& args);
		
		static PsykoPlugin* self();
		
	protected slots:
		void settingsChanged();
		
	private slots:
		void contactSentTypingMessage(const Kopete::Contact* contact, bool isTyping);
		void chatSessionClosing(Kopete::ChatSession* chatSession);
		void chatSessionCreated(Kopete::ChatSession* chatSession);
	
	private:
		void initializePlugin();
		
		bool userIsAvailable(const Kopete::Contact* contact);
		
		bool m_showMessageInChatWindow;
		bool m_disableWhenNotAvailable;
		
		static PsykoPlugin* m_instance;
};

#endif
