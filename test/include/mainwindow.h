#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QTextEdit>
#include <QMap>
#include <QGraphicsItem>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void onCommandEntered();
private:
	QGraphicsScene* scene;     // canvas vortex avelacvuma grafikakan dzevery -> QGraphicsItem
	QGraphicsView* view;       // widget vory cucatalis scene
	QGraphicsTextItem* canvasLabel; // figuri anuny canvasi vra nshelu hamar
	QLineEdit* commandInput;   // ogtvoxy gruma commandy aystex
	QTextEdit* logOutput;      // aystex grumenq haxordagrutyun pass kam failed

	QMap<QString, QGraphicsItem*> shapes; // pahumenq bolor dzevery 
										  // orinak "rect1" QGraphicsItem* tuyla talis hesht gtnel texapoxel jnjel

	void log(const QString& msg,const QColor& color = Qt::white); // es funkcian gruma katarvec te chexarkvec figury
	void addShapeWithLabel(QGraphicsItem* item, const QString& name;);
	QPointF parseCoord(const QString& coordStr); // poxakerpume kordinaty QPointF objekti
												// textain cordinaty("100","200") QPointF-obj
												// ogtagorcvuma draw/move komandneri jamanak
	void parseAndExexute(const QString& cmdLine); // grac commandy haskanuma ev anum scene-um
	void connectShapes(const QString& name1, const QString& name2);
	void executeFile(const QString& filePath);
};

#endif //MAINWINDOW_H:
