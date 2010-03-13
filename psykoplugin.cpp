#include "psykoplugin.h"
#include "psykoconfiguration.h"

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
		
		// read the settings from the config file
		settingsChanged();
		
		// initialize the plugin
		initializePlugin();
	}
}

PsykoPlugin* PsykoPlugin::self()
{
	return m_instance;
}

void PsykoPlugin::initializePlugin()
{
	connect(this, SIGNAL(settingsChanged()), this, SLOT(settingsChanged()));
	
	QList<Kopete::ChatSession*> chatSessionList = Kopete::ChatSessionManager::self()->sessions();
	
	// connect to the signals for all existing chat session
	foreach (Kopete::ChatSession* chatSession, chatSessionList)
	{
		chatSessionCreated(chatSession);
	}
	
	// then we'll do the same for new chat sessions
	connect(Kopete::ChatSessionManager::self(), SIGNAL(chatSessionCreated(Kopete::ChatSession*)), self(), SLOT(chatSessionCreated(Kopete::ChatSession*)));
}

void PsykoPlugin::settingsChanged()
{
	// read the config file
	PsykoConfiguration* config = PsykoConfiguration::self();
	config->readConfig();
	
	// set the values from the config file to our member variables
	m_showMessageInChatWindow = config->showMessageInChatWindow();
	m_disableWhenNotAvailable = config->disableWhenNotAvailable();
}

bool PsykoPlugin::userIsAvailable(const Kopete::Contact* contact)
{
	bool isAvailable = true;
	
	// only check if the user is unavailable if the setting is activated
	if (m_disableWhenNotAvailable)
	{
		// check if we are NOT online (= we're away, invisible or something else..)
		if (contact->onlineStatus().status() != Kopete::OnlineStatus::Online)
		{
			// then we're not available
			isAvailable = false;
		}
	}
	
	return isAvailable;
}

void PsykoPlugin::contactSentTypingMessage(const Kopete::Contact* contact, bool isTyping)
{
	Kopete::Contact* chatContact = const_cast<Kopete::Contact*>(contact);
	Kopete::ChatSession* chatSession = chatContact->manager();
	
	// check if the user is actually typing and make sure we do not have a
	// chat window (view) yet
	// also we need to check if we are available
	if (isTyping && !chatSession->view(false) && userIsAvailable(chatSession->myself()))
	{
		// start chat (= open chat window)
		chatContact->startChat();
		
		if (m_showMessageInChatWindow)
		{
			// build the chat message
			Kopete::Message message(chatSession->myself(), chatSession->myself());
			message.setDirection(Kopete::Message::Internal);
			message.setPlainBody(i18n("You feel a disturbance in the force..."));
			
			// append the message to the chat window
			chatSession->appendMessage(message);
		}
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
