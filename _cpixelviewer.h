#ifndef CPIXELVIEWER_H
#define CPIXELVIEWER_H

#include <QtGui>
#include <QtOpenGL>
#include "cpixelvector.h"

class CPixelViewer : public QGLWidget
{
    Q_OBJECT

public:
	CPixelViewer(QWidget *parent = 0);
	~CPixelViewer();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

public slots:

        void setPixelList( QList<CPixelVector>* list );
	void loadFile();
        void saveFile();
	void radiusChanged(QString);

	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:

	QPushButton				m_loadFileButton;
	QLineEdit				m_radiusEdit;
	QList<CPixelVector>		m_pixelList;

	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:

	int xRot;
	int yRot;
	int zRot;
	float distance;
	float m_radius;

        CVector m_center;

	QPoint	lastPos;
};

#endif // CPIXELVIEWER_H
