#include "cclassicview.h"


CClassicView::CClassicView(QWidget *parent)
	 : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
	 xRot = 0;
	 yRot = 0;
	 zRot = 0;
	 distance = -100;

	 initializeGL();

         m_mainWindow.setCentralWidget( this );
         m_mainWindow.show();
 }

 CClassicView::~CClassicView()
{

}

 QSize CClassicView::minimumSizeHint() const
 {
         return QSize(50, 50);
 }

 QSize CClassicView::sizeHint() const
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

 void CClassicView::setXRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != xRot) {
		 xRot = angle;
		 emit xRotationChanged(angle);
		 updateGL();
	 }
 }

 void CClassicView::setYRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != yRot) {
		 yRot = angle;
		 emit yRotationChanged(angle);
		 updateGL();
	 }
 }

 void CClassicView::setZRotation(int angle)
 {
	 qNormalizeAngle(angle);
	 if (angle != zRot) {
		 zRot = angle;
		 emit zRotationChanged(angle);
		 updateGL();
	 }
 }

 void CClassicView::initializeGL()
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

 void CClassicView::addMenuAction(QString path, const QObject *receiver, const char *member){

 }

 void CClassicView::paintGL()  {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	glTranslatef(0.0, 0.0, distance / 10.0 );
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

        glPushMatrix();

        glTranslatef( -m_center.x() , -m_center.y() , -m_center.z() );

        customPaint();

        glPopMatrix();

 }

 void CClassicView::resizeGL(int width, int height)
 {
	 int side = qMin(width, height);
	 glViewport((width - side) / 2, (height - side) / 2, side, side);

	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
 #ifdef QT_OPENGL_ES_1
	 glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
 #else
         gluPerspective( 45 , width / height , 0.1 , 5500 );
 #endif

	 glMatrixMode(GL_MODELVIEW);

 }

void CClassicView::mousePressEvent(QMouseEvent *event) {

	lastPos = event->pos();
}

void CClassicView::mouseMoveEvent(QMouseEvent *event){

	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if( event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton ){
                distance += dy * ( distance * 0.01 );

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
