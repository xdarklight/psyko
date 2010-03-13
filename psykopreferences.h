#ifndef PSYKOPREFERENCES_H
#define PSYKOPREFERENCES_H

#include "ui_psykopreferences.h"

#include <KCModule>

class PsykoPreferences : public KCModule, private Ui::PsykoPreferencesUI
{
	Q_OBJECT
	
	public:
		explicit PsykoPreferences(QWidget* parent = 0, const QVariantList& args = QVariantList());
};

#endif