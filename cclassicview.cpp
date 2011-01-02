#include "cclassicview.h"


CClassicView::CClassicView(QWidget *parent)
	 : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {

        m_center.set( 0, 0, -1 );
        xRot = 0;
        yRot = 0;
        zRot = 0;
        distance = -100;

        initializeGL();
        this->setMouseTracking( true );
        this->setFocusPolicy(Qt::StrongFocus);
 }

CClassicView::~CClassicView(){
}

QSize CClassicView::minimumSizeHint() const{
        return QSize(50, 50);
}

QSize CClassicView::sizeHint() const{
        return QSize(400, 400);
}

static void qNormalizeAngle(int &angle){
        while (angle < 0)
            angle += 360 * 16;
        while (angle > 360 * 16)
            angle -= 360 * 16;
}

void CClassicView::setXRotation(int angle){
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
}

void CClassicView::setYRotation(int angle){
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
}

void CClassicView::setZRotation(int angle){
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
}

void CClassicView::initializeGL(){
        //qglClearColor(qtPurple.dark());

        glEnable(GL_DEPTH_TEST);

        //glEnable(GL_CULL_FACE);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
/*	glEnable(GL_LIGHT0);
        //glEnable(GL_MULTISAMPLE);
        static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
*/
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        static GLfloat lightPosition[4] = { 0.0, 0.0, 1000.0, 1.0 }; //{ -0.5, 5.0, 7.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void CClassicView::addMenuAction(QString path, const QObject *receiver, const char *member){

}

void CClassicView::paintGL(){
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glLoadIdentity();

       //glTranslatef( -m_center.x() , -m_center.y() , -m_center.z() );
       glTranslatef( m_center.x() , m_center.y() , m_center.z() );

       glRotatef( xRot, 1.0, 0.0, 0.0);
       glRotatef( yRot, 0.0, 1.0, 0.0);
       glRotatef( zRot, 0.0, 0.0, 1.0);

       customPaint();
}

void CClassicView::customPaint(){
    /*glColor3f(1.0,1.0,1.0);
    glBegin( GL_QUADS );
        float plateWidth = 5000.0;
        float h = 0.0;
        int nx = 30;
        int ny = 30;
        float xstep = plateWidth/nx;
        float ystep = plateWidth/ny;
        for( float x = -plateWidth/2; x < plateWidth/2; x += xstep ){
            for( float y = -plateWidth/2; y < plateWidth/2; y += ystep ){
                glNormal3f( 0.0f, 1.0f, 0.0f);glVertex3f( x, h, y );glNormal3f( 0.0f, 1.0f, 0.0f);glVertex3f( x+xstep, h, y );glNormal3f( 0.0f, 1.0f, 0.0f);glVertex3f( x+xstep, h, y+ystep );glNormal3f( 0.0f, 1.0f, 0.0f);glVertex3f( x, h, y+ystep );
            }
        }
    glEnd();*/
}

void CClassicView::resizeGL(int width, int height){
    int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport( 0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float m_aspectRatio = (float)width/height;
    m_fov = 45.0;
    gluPerspective( m_fov, m_aspectRatio, 1.0, 500000.0);//60?
    glMatrixMode(GL_MODELVIEW);
}

void CClassicView::mousePressEvent(QMouseEvent *event) {

	lastPos = event->pos();
}

void CClassicView::mouseMoveEvent(QMouseEvent *event){

	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if( event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton ){
                m_center.setZ( m_center.z() + ( dy * ( m_center.z() * 0.04 ) ) );

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

void CClassicView::keyPressEvent ( QKeyEvent * event ){
    int value = 10;

    if( event->modifiers() & Qt::ControlModifier ){
        value = 100;
        if( event->key() == Qt::Key_Up ){
            m_center.setZ( m_center.z() + value );
        }else if( event->key() == Qt::Key_Down ){
            m_center.setZ( m_center.z() - value );
        }
        if( event->key() == Qt::Key_Left ){
            m_center.setX( m_center.x() + value );
        }else if( event->key() == Qt::Key_Right ){
            m_center.setX( m_center.x() - value );
        }
        if( event->key() == Qt::Key_A ){
            m_center.setX( m_center.x() + value );
        }else if( event->key() == Qt::Key_D ){
            m_center.setX( m_center.x() - value );
        }
        if( event->key() == Qt::Key_W ){
            m_center.setY( m_center.y() - value );
        }else if( event->key() == Qt::Key_S ){
            m_center.setY( m_center.y() + value );
        }

    }else{
        if( event->key() == Qt::Key_Up ){
            setXRotation( xRot + value );
        }else if( event->key() == Qt::Key_Down ){
            setXRotation( xRot - value );
        }

        if( event->key() == Qt::Key_Left ){
            setZRotation( zRot + value );
        }else if( event->key() == Qt::Key_Right ){
            setZRotation( zRot - value );
        }

        if( event->key() == Qt::Key_W ){
            setXRotation( xRot + value );
        }else if( event->key() == Qt::Key_S ){
            setXRotation( xRot - value );
        }

        if( event->key() == Qt::Key_A ){
            setYRotation( yRot + value );
        }else if( event->key() == Qt::Key_D ){
            setYRotation( yRot - value );
        }
    }
    repaint();
}
