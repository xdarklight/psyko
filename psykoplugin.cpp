#include "psykoplugin.h"

#include <kopete/kopetecontact.h>
#include <kopete/kopetemetacontact.h>
#include <kopete/kopetechatsessionmanager.h>

#include <KGenericFactory>

K_PLUGIN_FACTORY(PsykoPluginFactory, registerPlugin<PsykoPlugin>();)
K_EXPORT_PLUGIN(PsykoPluginFactory("kopete_psyko"))

PsykoPlugin* PsykoPlugin::m_instance = 0L;

PsykoPlugin::PsykoPlugin(QObject* parent, const QVariantList& args)
	: Kopete::Plugin(PsykoPluginFactory::componentData(), parent)
{
	Q_UNUSED(args)
	
	// make sure we're not initialized yet
	if (!self())
	{
		m_instance = this;
		
		initializePlugin();
	}
}

PsykoPlugin* PsykoPlugin::self()
{
	return m_instance;
}

void PsykoPlugin::initializePlugin()
{
	QList<Kopete::ChatSession*> chatSessionList = Kopete::ChatSessionManager::self()->sessions();
	
	// connect to the signals for all existing chat session
	foreach (Kopete::ChatSession* chatSession, chatSessionList)
	{
		chatSessionCreated(chatSession);
	}
	
	// then we'll do the same for new chat sessions
	connect(Kopete::ChatSessionManager::self(), SIGNAL(chatSessionCreated(Kopete::ChatSession*)), self(), SLOT(chatSessionCreated(Kopete::ChatSession*)));
}

void PsykoPlugin::contactSentTypingMessage(const Kopete::Contact* contact, bool isTyping)
{
	if (isTyping)
	{
		// start chat (= open chat window)
		contact->metaContact()->startChat();
	}
}

void PsykoPlugin::chatSessionClosing(Kopete::ChatSession* chatSession)
{
	// chat session is gone - thus we need to disconnect from it
	disconnect(chatSession, 0, self(), 0);
}

void PsykoPlugin::chatSessionCreated(Kopete::ChatSession* chatSession)
{
	// connect to the 'typing' and 'session closed' signals
	connect(chatSession, SIGNAL(closing(Kopete::ChatSession*)), self(), SLOT(chatSessionClosing(Kopete::ChatSession*)));
	connect(chatSession, SIGNAL(remoteTyping(const Kopete::Contact*, bool)), self(), SLOT(contactSentTypingMessage(const Kopete::Contact*, bool)));
}
