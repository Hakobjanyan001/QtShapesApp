// project library 
#include "Utility.h"
#include "Constants.h"

//third party library
#include <QGraphicsTextItem>
#include <QPointF>
#include <QPainter>

namespace Utility{
	void helpSetupScene(QGraphicsScene* scene, QGraphicsTextItem*& canvasLabel) {
			if( !scene ) return;
			
			scene->setBackgroundBrush(Constants::sceneBackgroundColor);
			
			canvasLabel = scene->addText(Constants::canvasLabelText);
			canvasLabel->setDefaultTextColor(Constants::canvasTextColor);
			canvasLabel->setFont(Constants::canvasLabelFont);
			
			QRectF rect = canvasLabel->boundingRect();
			QPointF center = scene->sceneRect().center();
	
			canvasLabel->setPos(center.x() - rect.width() / 2,
								center.y() - rect.height() / 2);
	
	}

	void helpSetupUI(QGraphicsView* view, 
				 QLineEdit* commandInput, 
				 QTextEdit* logOutput,
				 QMenuBar* menuBar,
				 QVBoxLayout* layout,
				 QLabel* logTitle,
				 QLabel* consoleTitle) {
		
		if( view ) {
			view->setRenderHint(QPainter::Antialiasing);  // gceri ankyunnery darcnume hart, aveli sirun
			view->setDragMode(QGraphicsView::ScrollHandDrag);  // tuyle talis mknikov sharj el Canvasy
			view->setAlignment(Qt::AlignCenter);  // Scene-y kentronacnum e View-i mej
		}
		
		if( commandInput ) {
			commandInput->setPlaceholderText(Constants::commandInputPlaceholder);
			commandInput->setFixedHeight(Constants::commandInputHeight);  // comand consoly     darcnume aveli bardzr ev gexecik
			commandInput->setStyleSheet("background-color: #f8f9fa; color: black; font-size: 14px; padding: 10px; border: 2px solid #444; border-radius: 4px;");
		}
		
		if( logOutput ) {
			logOutput->setReadOnly(true);  // miayn kardalu rejim
			logOutput->setMaximumHeight(Constants::logOutputMaxHeight);
			logOutput->setStyleSheet("background-color: #f8f9fa; color: black; font-family:'Courier New', monospace; font-size: 13px; border: 1px solid #ccc;");
		}
		
		if( logTitle ) {
			logTitle->setText("Log Output");
			logTitle->setStyleSheet("background-color: black; color: white; font-weight: bold; padding: 4px;"); // console-style panel
		}

		if( consoleTitle ) {
			consoleTitle->setText("Command Console");
			consoleTitle->setStyleSheet("background-color: #333333; color: white; font-weight: bold; padding: 4px;");
		}

		
		layout->setContentsMargins(0,0,0,0); // Canvasi shurjy spitak ezrer ereva
		layout->addWidget(menuBar);	// patuhani vra ktexadri userin ognox bloky 
		layout->addWidget(view); // view zbaxecnuma mec taracq, 1 nshanakuma mecana 1 chapov 



		layout->addWidget(logTitle); // avelacnumen Log Window-un

		layout->addWidget(logOutput); // et window-i mejel dnumen mer outputy




		layout->addWidget(consoleTitle); // avleacnumenq command console  patuhany
		layout->addWidget(commandInput); // dnumenq useri grac commandy




	}
}
