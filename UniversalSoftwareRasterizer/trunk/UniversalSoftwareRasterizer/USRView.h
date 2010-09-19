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
	vector<USRVector3> model;
	USRMatrix Pipeline;
	USRMatrix WindowMatrix;

private slots:
	void Timeout();
};

#endif // USRView_h__