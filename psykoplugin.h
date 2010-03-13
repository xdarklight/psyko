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
	
	private slots:
		void contactSentTypingMessage(const Kopete::Contact* contact, bool isTyping);
		void chatSessionClosing(Kopete::ChatSession* chatSession);
		void chatSessionCreated(Kopete::ChatSession* chatSession);
	
	private:
		void initializePlugin();
		
		static PsykoPlugin* m_instance;
};

#endif
