#include "USRView.h"
#include <QPainter>
#include <QTimer>
#include <assert.h>

USRView::USRView()
{
	setFixedSize(480,280);
	
	model.push_back(USRTriangle(
		USRVector3(0,0,0),
		USRVector3(1,0,0),
		USRVector3(0,1,0)
		));

	
	model.push_back(USRTriangle(
		USRVector3(1,0,0),
		USRVector3(1,1,0),
		USRVector3(0,1,0)
		));
	

	model.push_back(USRTriangle(
		USRVector3(0,0,0),
		USRVector3(1,0,0),
		USRVector3(0,0,1)
		));

	transformed_vertices.resize(model.size());

	WindowMatrix = USRMatrix::CreateWindowMatrix(480,280);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Timeout()));
	timer->start(120);
}

void USRView::paintEvent( QPaintEvent * evt )
{
	QPainter painter(this);

	painter.fillRect(0,0,width(),height(),Qt::black);
	painter.setPen(Qt::white);
	painter.setBrush(Qt::red);

	for (unsigned int i=0; i<transformed_vertices.size(); i++)
	{
		USRTriangle t = transformed_vertices[i];

		QPolygonF tri;
		tri << QPointF(t.A.X,t.A.Y);
		tri << QPointF(t.B.X,t.B.Y);
		tri << QPointF(t.C.X,t.C.Y);

		painter.drawPolygon(tri);
	}
}

float t=0;

void USRView::Timeout()
{	
	t += 0.01f;

	//////////////////////////////////////////////////////////////////////////
	USRMatrix tr1 = USRMatrix::CreateTranslationMatrix(USRVector3(0,0,0));
	USRMatrix rx1 = USRMatrix::CreateXRotationMatrix(3.1415f/6); //30�
	USRMatrix ry1 = USRMatrix::CreateYRotationMatrix(t*4); //30�

	USRMatrix Hworld = tr1*rx1*ry1;
	USRMatrix Hview = USRMatrix::CreateLookAtMatrix(
		USRVector3(0,0,5),
		USRVector3(0,0,0),
		USRVector3(0,1,0)
		);

	USRMatrix Hproj = USRMatrix::CreateOrthoProjectionMatrix(-4,4,-4,4,0.1f,10);

	Pipeline = Hproj * Hview * Hworld;
	//////////////////////////////////////////////////////////////////////////

	for (unsigned int i=0; i<model.size(); i++)
	{
		USRTriangle t = model[i];

		USRTriangle tt;
		tt.A = Transform(t.A);
		tt.B = Transform(t.B);
		tt.C = Transform(t.C);

		transformed_vertices[i] = tt;
	}

	update();
}

USRVector3 USRView::Transform( USRVector3 & v )
{
	USRVector3 transformed_point =  Pipeline * v;
	transformed_point = transformed_point / transformed_point.I;
	transformed_point.I = 1;
	transformed_point = WindowMatrix * transformed_point;

	/*
	assert(!(
		transformed_point.X>480 || transformed_point.X<0 ||
		transformed_point.Y>280 || transformed_point.Y<0)
		);
	*/

	return transformed_point;
}
