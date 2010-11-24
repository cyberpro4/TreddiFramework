#ifndef CCLASSICVIEW_H
#define CCLASSICVIEW_H

#include <QtGui>
#include <QtOpenGL>
#include "cvector.h"

class CClassicView : public QGLWidget
{
	Q_OBJECT

public:
	CClassicView(QWidget *parent = 0);
	~CClassicView();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

        void  addMenuAction( QString path , const QObject* receiver , const char* member );

public slots:

	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:

        QMainWindow     m_mainWindow;
        CVector         m_center;

	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	virtual void customPaint(){}

private:

	int xRot;
	int yRot;
	int zRot;
	float distance;

	QPoint	lastPos;
};


#endif // CCLASSICVIEW_H