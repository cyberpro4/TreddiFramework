#ifndef CVIEWEXTENDER_H
#define CVIEWEXTENDER_H

#include "cclassicview.h"

class CViewExtender : public QWidget {

	Q_OBJECT

protected:

	QMenuBar		m_menuBar;
	CClassicView*	m_view;

public:

	CViewExtender( CClassicView* view );
};

#endif // CVIEWEXTENDER_H
