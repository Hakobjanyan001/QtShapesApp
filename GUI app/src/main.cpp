// project library
#include "mainwindow.h"

// third-pary library
#include <QApplication>

/*
    ShapeDesigner – Interactive vector graphics editor with command-line interface
    Author: [Karen Hakobjanyan]
    Features:
     Real-time shape creation (line, triangle, rectangle, square)
     Script execution via execute_file
     Shape deletion
     Colored console/log output
     Qt6 + clean C++17 code
*/

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.resize(1200, 800);
	w.show();
	return a.exec();
}
