#include "cvtraw.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CvtRaw w;
	w.show();
	return a.exec();
}
