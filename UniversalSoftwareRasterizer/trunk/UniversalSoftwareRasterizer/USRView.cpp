#include "USRView.h"
#include <QPainter>
#include <QTimer>

USRView::USRView()
{
	setFixedSize(480,280);
/*
	model.push_back(USRVector3(0,0,0));
	model.push_back(USRVector3(1,0,0));
	model.push_back(USRVector3(0,1,0));
*/
	
	model.push_back(USRVector3(-1,-1,-1));
	model.push_back(USRVector3(-1,1,-1));
	model.push_back(USRVector3(1,1,-1));
	model.push_back(USRVector3(1,-1,-1));
	
	model.push_back(USRVector3(-1,-1,1));
	model.push_back(USRVector3(-1,1,1));
	model.push_back(USRVector3(1,1,1));
	model.push_back(USRVector3(1,-1,1));
	

	//////////////////////////////////////////////////////////////////////////
	USRMatrix tr1 = USRMatrix::CreateTranslationMatrix(USRVector3(00,00,0));
	USRMatrix rx1 = USRMatrix::CreateXRotationMatrix(3.1415f/6); //30°
	USRMatrix ry1 = USRMatrix::CreateYRotationMatrix(0); //30°

	USRMatrix Hworld = tr1*rx1*ry1;
	USRMatrix Hview = USRMatrix::CreateLookAtMatrix(
		USRVector3(0,0,10),
		USRVector3(0,0,0),
		USRVector3(0,1,0)
		);

	USRMatrix Hproj = USRMatrix::CreateProjectionMatrix(-4,4,-4,4,-1,-100);

	Pipeline = Hproj * Hview * Hworld;
	//////////////////////////////////////////////////////////////////////////

	WindowMatrix = USRMatrix::CreateWindowMatrix(480,280);
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Timeout()));
	timer->start(50);
}

void USRView::paintEvent( QPaintEvent * evt )
{
	QPainter painter(this);

	painter.fillRect(0,0,width(),height(),Qt::black);

	painter.setPen(Qt::white);

	for (unsigned int i=0; i<model.size(); i++)
	{
		USRVector3 transformed_point =  Pipeline * model[i];
		transformed_point = transformed_point / transformed_point.I;
		transformed_point.I = 1;
		transformed_point = WindowMatrix * transformed_point;

		painter.drawLine(
			transformed_point.X,transformed_point.Y,
			transformed_point.X,transformed_point.Y);
	}
}

float t=0;

void USRView::Timeout()
{
	t += 0.01f;

	//////////////////////////////////////////////////////////////////////////
	USRMatrix tr1 = USRMatrix::CreateTranslationMatrix(USRVector3(00,00,0));
	USRMatrix rx1 = USRMatrix::CreateXRotationMatrix(3.1415f/6); //30°
	USRMatrix ry1 = USRMatrix::CreateYRotationMatrix(t); //30°

	USRMatrix Hworld = tr1*rx1*ry1;
	USRMatrix Hview = USRMatrix::CreateLookAtMatrix(
		USRVector3(0,0,10),
		USRVector3(0,0,0),
		USRVector3(0,1,0)
		);

	USRMatrix Hproj = USRMatrix::CreateProjectionMatrix(-4,4,-4,4,-1,-100);

	Pipeline = Hproj * Hview * Hworld;
	//////////////////////////////////////////////////////////////////////////

	update();
}
