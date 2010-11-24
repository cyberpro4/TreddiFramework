#include "matchertmp.h"

MatcherTmp::MatcherTmp(){

    QPushButton *but = new QPushButton("Push");

    connect( but , SIGNAL(clicked()) , this , SLOT(callMe()) );

    but->show();
}

void MatcherTmp::callMe(){

    QString im1 = QFileDialog::getOpenFileName( 0 , "" , "" );
    QString im2 = QFileDialog::getOpenFileName( 0 , "" , "" );

    m_match = new Matcher( QImage( im1 ).convertToFormat( QImage::Format_RGB888 ) ,
                           QImage( im2 ).convertToFormat( QImage::Format_RGB888 ) );

    m_match->calculate();
}
