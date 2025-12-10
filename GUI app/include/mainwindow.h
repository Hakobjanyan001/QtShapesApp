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

/*
    MainWindow – The central widget of ShapeDesigner
    Features:
      Interactive graphics canvas (QGraphicsScene + QGraphicsView)
      Command-line interface at the bottom
      Real-time colored log output
      File → Open support for executing command scripts
      Full command system: create_*, delete, execute_file, connect
*/

class Shape;
class CreateShapeCommand;

class MainWindow : public QMainWindow {
	friend class CreateShapeCommand;
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void onCommandEntered();  // Appends colored message to log
	void onNewCanvas();		  // Parses and runs a single command
    void onOpenFile();		  // Triggered when Enter is pressed in input
    void onSaveFile();		  // File → Open menu action
    void onExit();
private:
	QGraphicsScene* scene = nullptr;     		// Main drawing area
	QGraphicsView* view = nullptr;       		// Viewport for the scene
	QGraphicsTextItem* canvasLabel = nullptr; 	
	QLineEdit* commandInput = nullptr;   		// Command input field
	QTextEdit* logOutput = nullptr;             // Colored log/console

	QMap<QString, QGraphicsItem*> shapes;  // name → graphics item (for rendering)
	QMap<QString, Shape*> m_ownedShapes;   // name → actual Shape object (for ownership & deletion)

	void setupScene();  // Creates layout, widgets, menus
    void setupUI();		// Initializes the drawing canvas
	
	void executeCommand(const QStringList& tokens); 	

	void addShapeLabel( QGraphicsItem* item, const QString& name );
    
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

};

#endif //MAINWINDOW_H:
