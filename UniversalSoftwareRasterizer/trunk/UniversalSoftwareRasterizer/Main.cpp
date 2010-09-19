#include <QApplication>
#include <QPlastiqueStyle>
#include "USRView.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QPlastiqueStyle());

	USRView usr_view;
	usr_view.show();

	return a.exec();
}
