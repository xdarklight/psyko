#include "psykopreferences.h"

#include "psykoconfiguration.h"

#include <KGenericFactory>

K_PLUGIN_FACTORY(PsykoPreferencesFactory, registerPlugin<PsykoPreferences>();)
K_EXPORT_PLUGIN(PsykoPreferencesFactory("kcm_kopete_psyko"))

PsykoPreferences::PsykoPreferences(QWidget* parent, const QVariantList& args)
	: KCModule (PsykoPreferencesFactory::componentData(), parent, args)
{
	setupUi(this);
	
	addConfig(PsykoConfiguration::self(), this);
	PsykoConfiguration::self()->readConfig();
	load();
}
