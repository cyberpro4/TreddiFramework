#include "cpixelviewer.h"

CPixelViewer::CPixelViewer(QWidget *parent)
         : CClassicView( parent )
 {

	 m_loadFileButton.setText( "Load" );
	 connect( &m_loadFileButton , SIGNAL(clicked()) , this , SLOT(loadFile()) );
	 m_loadFileButton.show();

	 m_radiusEdit.show();
	 connect( &m_radiusEdit , SIGNAL(textChanged(QString)) , this , SLOT(radiusChanged(QString)) );
	 m_radius = 0;


 }

void CPixelViewer::setPixelList(QList<CPixelVector> *list){

    m_pixelList.clear();

    m_pixelList.append( *list );

    float max[3] = { LONG_MIN, LONG_MIN, LONG_MIN };
    float min[3] = { LONG_MAX, LONG_MAX, LONG_MAX };

    CPixelVector px;
    foreach( px, m_pixelList ){
        if( px.x() < min[0] )min[0]=px.x();
        if( px.y() < min[1] )min[1]=px.y();
        if( px.z() < min[2] )min[2]=px.z();

        if( px.x() > max[0] )max[0]=px.x();
        if( px.y() > max[1] )max[1]=px.y();
        if( px.z() > max[2] )max[2]=px.z();
    }

    m_center.set( ((max[0] + min[0]) / 2.0), ((max[1] + min[1]) / 2.0) , ((max[2] + min[2]) / 2.0) );

}

void CPixelViewer::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save file"), "" , tr("* Files (*.*)"));

    QFile file(fileName);
    if( !file.open( QFile::WriteOnly ) )
            return;

    CPixelVector vec;
    foreach( vec , m_pixelList ){
            QString str = QString("%1;%2;%3;%4\n").arg(vec.x()).arg(vec.y()).arg(vec.z()).arg(vec.color().value());

            file.write( str.toAscii() );
    }

    file.close();
}

void CPixelViewer::radiusChanged(QString s){
	m_radius = s.toFloat();
	updateGL();
}

 CPixelViewer::~CPixelViewer()
{

}

void CPixelViewer::loadFile(){
	QString fileName = QFileDialog::getOpenFileName(this,
	 tr("Open file"), "" , tr("* Files (*.*)"));

	QFile file(fileName);
	if( !file.open( QFile::ReadOnly ) )
		return;

	while( !file.atEnd() ){
		QString s(file.readLine( 256 ));
		QStringList l = s.split(';');

		m_pixelList.append( CPixelVector( l[0].toFloat() , l[1].toFloat() , l[2].toFloat() , QColor( l[3].toInt() ) ) );
	}

	file.close();
}

 void CPixelViewer::customPaint()  {


	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL );

	CPixelVector v;
	foreach( v, m_pixelList ){

		glPushMatrix();
		glTranslatef( v.x() , v.y() , v.z() );

		float vv[4] = { v.color().redF() , v.color().greenF() , v.color().blueF() , 1.0 };
		glMaterialfv( GL_FRONT , GL_DIFFUSE , vv );
		gluSphere( quadric , m_radius , 4 , 4 );

		glPopMatrix();
	}

 }
