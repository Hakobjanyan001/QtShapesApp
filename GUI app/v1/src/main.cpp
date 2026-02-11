// project library
#include "mainwindow.h"
#include "Constants.h"

// third-pary library
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.resize(Constants::windowWidth, Constants::windowHeight);
	w.show();
	return a.exec();
}
