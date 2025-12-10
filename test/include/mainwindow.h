#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// project headers
#include "Shape.h"
#include "ShapeType.h"
#include "ShapeFactory.h"
#include "CheckShapeType.h"
#include "CommandFactory.h"
#include "Command.h"


// system/standart library
#include <memory>
#include <optional>
#include <vector>

// third-pary
#include <QVBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QMap>
#include <QGraphicsItem>
#include <QStringList>
#include <QColor>
#include <QTime>
#include <QRegularExpression>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeySequence>
#include <QStringList>

class Shape;
class CreateShapeCommand;

class MainWindow : public QMainWindow {
	friend class CreateShapeCommand;
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void onCommandEntered();
	void onNewCanvas();
    void onOpenFile();
    void onSaveFile();
    void onExit();
private:
	QGraphicsScene* scene = nullptr;     // canvas vortex avelacvuma grafikakan dzevery -> QGraphicsItem
	QGraphicsView* view = nullptr;       // widget vory cucatalis scene
	QGraphicsTextItem* canvasLabel = nullptr; // figuri anuny canvasi vra nshelu hamar
	QLineEdit* commandInput = nullptr;   // ogtvoxy gruma commandy aystex
	QTextEdit* logOutput = nullptr;      // aystex grumenq haxordagrutyun pass kam failed

	QMap<QString, QGraphicsItem*> shapes; // pahumenq bolor dzevery 
	QMap<QString, Shape*> m_ownedShapes; // shape objecty pahuma unique_ptr-ov vor memory leak chlini

	void setupScene();
    void setupUI();
	
	void executeCommand(const QStringList& tokens); 	

	void addShapeLabel( QGraphicsItem* item, const QString& name );
												// textain cordinaty("100","200") QPointF-obj
												// ogtagorcvuma draw/move komandneri jamanak
    
	QString extractName(const QStringList& args) const;
	
	std::vector<double> extractCoordinates(const QStringList& args);

	QPointF parseCoord( const QString& coordStr ); // poxakerpume kordinaty QPointF objekti
	
	QString shapeTypeToString(ShapeType type) const;
	
	bool firstShape = true;
public:
	QGraphicsScene* getScene()  { return scene; } 	

		void log(const QString& msg, QColor color = Qt::white); // es funkcian gruma katarvec te chexarkvec figury

	void parseAndExecute( const QString& cmdLine ); // grac commandy haskanuma ev anum scene-um
    
	void handleConnect(const QStringList& args);

	void handleExecuteFile(const QStringList& parts);

};

#endif //MAINWINDOW_H:
