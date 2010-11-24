#include "cviewextender.h"

CViewExtender::CViewExtender( CClassicView* view ){

	m_view = view;

	QVBoxLayout* lay = new QVBoxLayout();

	lay->addWidget( &m_menuBar );
	lay->addWidget( m_view );

	setLayout( lay );

	show();
}
