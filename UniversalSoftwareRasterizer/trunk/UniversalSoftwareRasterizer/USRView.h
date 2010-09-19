#ifndef USRView_h__
#define USRView_h__

#include <QWidget>
#include "USRMatrix.h"
#include <vector>
using namespace std;

class USRView : public QWidget
{
	Q_OBJECT

public:
	USRView();

protected:
	virtual void paintEvent(QPaintEvent * evt);

private:
	struct USRTriangle
	{
		struct  
		{
			USRVector3 A;
			USRVector3 B;
			USRVector3 C;
		};

		USRTriangle()
		{
		}

		USRTriangle(USRVector3 a, USRVector3 b, USRVector3 c)
			: A(a), B(b), C(c)
		{
		}
	};

	vector<USRTriangle> model;
	vector<USRTriangle> transformed_vertices;
	USRMatrix Pipeline;
	USRMatrix WindowMatrix;

	USRVector3 Transform(USRVector3 & v);

private slots:
	void Timeout();
};

#endif // USRView_h__