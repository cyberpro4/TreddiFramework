#include "cpixelviewer.h"

CPixelViewer::CPixelViewer(QWidget *parent)
	 : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
	 xRot = 0;
	 yRot = 0;
	 zRot = 0;
         distance = -500;

	 m_loadFileButton.setText( "Load" );
	 connect( &m_loadFileButton , SIGNAL(clicked()) , this , SLOT(loadFile()) );
	 m_loadFileButton.show();

         QPushButton* btn = new QPushButton("save");
         connect( btn , SIGNAL(clicked()) , this , SLOT(saveFile()) );
         btn->show();

         m_radiusEdit.setText( "3" );
	 m_radiusEdit.show();
	 connect( &m_radiusEdit , SIGNAL(textChanged(QString)) , this , SLOT(radiusChanged(QString)) );
         m_radius = 3;
 }

void CPixelViewer::radiusChanged(QString s){
	m_radius = s.toFloat();
	updateGL();
}

 CPixelViewer::~CPixelViewer()
{

}


void CPixelViewer::setPixelList(QList<CPixelVector> *list){
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

    m_center.set( ((max[0] - min[0]) / 2.0), ((max[1] - min[1]) / 2.0) , ((max[2] - min[2]) / 2.0) );

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

 QSize CPixelViewer::minimumSizeHint() const
 {
	 return QSize(50, 50);
 }

 QSize CPixelViewer::sizeHint() const
 {
	 return QSize(400, 400);
 }

 static void qNormalizeAngle(int &angle)
 {
	 while (angle < 0)
		 angle += 360 * 16;
	 while (angle > 360 * 16)
		 angle -= 360 * 16;
 }

 void CPixelViewer::setXRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != xRot) {
		 xRot = angle;
		 emit xRotationChanged(angle);
		 updateGL();
	 }
 }

 void CPixelViewer::setYRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != yRot) {
		 yRot = angle;
		 emit yRotationChanged(angle);
		 updateGL();
	 }
 }

 void CPixelViewer::setZRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != zRot) {
		 zRot = angle;
		 emit zRotationChanged(angle);
		 updateGL();
	 }
 }

 void CPixelViewer::initializeGL()
 {
	 //qglClearColor(qtPurple.dark());

	 glEnable(GL_DEPTH_TEST);

	 glEnable(GL_CULL_FACE);
	 glShadeModel(GL_SMOOTH);
	 glEnable(GL_LIGHTING);
	 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	 glEnable(GL_LIGHT0);
	 //glEnable(GL_MULTISAMPLE);
	 static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	 glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

 }

 void CPixelViewer::paintGL()  {
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
        glTranslatef( 0 , 0 , distance );
        glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
        glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
        glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);


        /*float uv = cos( yRot / 64.0 ) * distance;

        float uv_x = cos( xRot / 64.0) * uv;
        float uv_y = sin( xRot / 64.0) * uv;

        //gluLookAt( 170 + uv_x , 130 + uv_y , sin( yRot / 64.0 ) * distance , 170,130,0,0,1,0);
        gluLookAt( 170 + uv_x , 130 + uv_y , sin( yRot / 64.0 ) * distance , 170,0,130,0,0,1);*/


	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL );

	CPixelVector v;

        glPushMatrix();
        glTranslatef( -m_center.x() , -m_center.y() , 0 );

	foreach( v, m_pixelList ){

		glPushMatrix();
                glTranslatef(v.x() , v.y() , v.z() );

		float vv[4] = { v.color().redF() , v.color().greenF() , v.color().blueF() , 1.0 };
		glMaterialfv( GL_FRONT , GL_DIFFUSE , vv );
		gluSphere( quadric , m_radius , 4 , 4 );

		glPopMatrix();
	}

        glPopMatrix();


 }

 void CPixelViewer::resizeGL(int width, int height)
 {
	 int side = qMin(width, height);
	 glViewport((width - side) / 2, (height - side) / 2, side, side);

	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
 #ifdef QT_OPENGL_ES_1
	 glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
 #else
         gluPerspective( 45 , width / height , 0.1 , 4500 );
 #endif
 
	 glMatrixMode(GL_MODELVIEW);

 }

void CPixelViewer::mousePressEvent(QMouseEvent *event) {

	lastPos = event->pos();
}

void CPixelViewer::mouseMoveEvent(QMouseEvent *event){

	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if( event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton ){
                distance += dy * distance*0.01;

		lastPos = event->pos();
		updateGL();
		return;
	}

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}
	lastPos = event->pos();
}
