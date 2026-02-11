#ifndef CONSTANTS_H
#define CONSTANTS_H

// third-pary library
#include <QColor>
#include <QFont>
#include <QString>

// stexcel tarac vory kogni azatvel hard codingic 
// karoxenq cankacac memberin dimel Constants::"mer uzac membery"


namespace Constants{

	const qreal sceneX = -500.0;
	const qreal sceneY = -400.0;
	const qreal sceneWidth = 1000.0;
	const qreal sceneHeight = 800.0;
	const QColor sceneBackgroundColor = Qt::white;
	const QString canvasLabelText = "Canvas";
	const QColor canvasTextColor = Qt::black;
	const QFont canvasLabelFont{"Arial", 30, QFont::Bold};
	const int windowWidth = 1200;
	const int windowHeight = 800;
	const QString exampleCreateTriangle = "create_triangle -name {MyTriangle} -coord_1 {0,0} -coord_2 {100,0} -coord_3 {50,100}";
	const int commandInputHeight = 40;
	const int commandInputPadding = 8;
	const int commandInputFontSize = 14;
	const QString commandInputPlaceholder = "Enter command here...";
	const int logOutputMaxHeight = 220;
	const int logFontSize = 13;
	const QString logFontFamily = "Courier";
	const int menuBarHeight = 30;
	const int menuBarFontSize = 14;
	const QColor uiBackgroundColor = Qt::black;
	const QColor uiTextColor = Qt::white;
	const QColor shapePenColor = Qt::blue;
	const QColor shapeBrushColor = Qt::blue;
	const int shapePenWidthDefault = 1;
	const int squarePenWidth = 2;
	const QFont shapeLabelFont{"Arial", 10};
	const QColor shapeLabelTextColor = Qt::black;
	const QColor connectLineColor = Qt::red;
	const int connectLineWidth = 3;
	const QColor logInfoColor = Qt::black;
	const QColor logErrorColor = Qt::red;
	const QColor logSuccessColor = Qt::green;
	const QColor logConnectColor = Qt::yellow;
	const QColor  logWarningColor    = QColor("#cccccc");   
	const QColor  logCommandColor    = QColor("#aaaaaa");

};

#endif //CONSTANTS_H
