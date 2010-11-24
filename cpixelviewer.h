#ifndef CPIXELVIEWER_H
#define CPIXELVIEWER_H

#include <QtGui>
#include <QtOpenGL>
#include "cpixelvector.h"
#include "cclassicview.h"
#include "cviewextender.h"

class CPixelViewer : public CClassicView
{
    Q_OBJECT

public:
	CPixelViewer(QWidget *parent = 0);
	~CPixelViewer();

public slots:

	void loadFile();
        void saveFile();
	void radiusChanged(QString);

        void setPixelList(QList<CPixelVector> *);

	void	customPaint();

protected:

        QPushButton			m_loadFileButton;
        QLineEdit			m_radiusEdit;
	QList<CPixelVector>		m_pixelList;

private:

	float m_radius;
};

#endif // CPIXELVIEWER_H
