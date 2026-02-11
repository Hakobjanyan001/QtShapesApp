#ifndef UTILITY_H
#define UTILITY_H

//third-party library
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QLabel>

namespace Utility{

	void helpSetupScene(QGraphicsScene* scene, QGraphicsTextItem*& canvasLabel);

	void helpSetupUI(QGraphicsView* view, 
				 	 QLineEdit* commandInput, 
				 	 QTextEdit* logOutput,
				 	 QMenuBar* menuBar,
				 	 QVBoxLayout* layout,
					 QLabel* logTitle,
					 QLabel* consoleTitle);

}

#endif //UTILITY_H
