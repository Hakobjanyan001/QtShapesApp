// project library
#include "mainwindow.h"
#include "Constants.h"
#include "Utility.h"

// third-pary library
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QStringList>
#include <QRegularExpression>
#include <QTextCursor>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

	setupScene();
	setupUI();

    log("Canvas ready! Type commands below.", Constants::logInfoColor);
	log(Constants::exampleCreateTriangle, Constants::logInfoColor); 
}

MainWindow::~MainWindow() {
	for(auto shape : m_ownedShapes) {
		delete shape;
	}
    m_ownedShapes.clear();
}

void MainWindow::setupScene() {

	scene = new QGraphicsScene(Constants::sceneX, 
							   Constants::sceneY,
	                           Constants::sceneWidth, 
							   Constants::sceneHeight, 
							   this);

		Utility::helpSetupScene(scene, canvasLabel);
}


void MainWindow::setupUI() {
	QWidget* central = new QWidget(this);  // stexcume himnakan widget, vorpes kentronakan hatvac
	QVBoxLayout* layout = new QVBoxLayout(central);  // stexcuma vertical dasavorvacutyun, asumenq Qt-in vor Canvasy lini verev, log-y nerqev, Consoly amenanergev

	view = new QGraphicsView(scene, this);

	commandInput = new QLineEdit(this);

	logOutput = new QTextEdit(this);


	menuBar = new QMenuBar(this);

	fileMenu = menuBar->addMenu(tr("File")); 
    
	helpMenu = menuBar->addMenu(tr("Help")); 


	logTitle = new QLabel(" Log"); // stexcumenq pitak(log) anunov

	consoleTitle = new QLabel(" Command console"); // stexcumenq pitak(command consol) anunov

	fileMenu->addAction(tr("New"), this, &MainWindow::onNewCanvas)->setShortcut(QKeySequence::New); // maqrel canvasy vor nory lini + baci Ctrl + N
		
	fileMenu->addAction(tr("Open"), this, &MainWindow::onOpenFile)->setShortcut(QKeySequence::Open); // baci fayly + baci Ctrl + O

	fileMenu->addAction(tr("&Save As"), this, &MainWindow::onSaveFile)->setShortcut(QKeySequence::Save); // pahpani fayly + pahpani Ctrl + S-ov
	fileMenu->addSeparator();

	fileMenu->addAction(tr("Exit"), this, &QMainWindow::close) ->setShortcut(QKeySequence::Quit); // Ctrl + F4  vor dursga


	helpMenu->addAction(tr("About"), this, [this]() { // der patrrast chi uxxaki logov kasi et masin
		QMessageBox::information(this, tr("About"),
			tr( "Shape Drawer v1.0\n\n"
				"Simple vector drawing with text commands\n"
				"Created with Qt 5/6 + C++\n\n"
				"Press F1 anytime for help"));
	});

	helpMenu->addAction(tr("Command &Help"), this, [this]() {
		QMessageBox::information(this, tr("Available commands"),
			tr( "  examples of creating a form\n  create_line -name {line_name} -coord_1 {0,3} -coord_2 {3.5,-1}\n\n"
			"  create_square -name {sqr_name} -coord_1 {0,0} -coord_2 {3,3}\n"
			"  examples of connecting 2 objects\n  connect -object_name_1 {star_name} -object_name_2 {rect_name}\n\n"
			"  example how to connect execute file\n example of run execute file execute_file -file_path {../a/b/c/d/script.txt}"));
	})->setShortcut(Qt::Key_F1); // F1 stexnov kbaci Help-i 

	Utility::helpSetupUI(view,
						 commandInput,
						 logOutput,
						 menuBar,
						 layout,
						 logTitle,
						 consoleTitle);
	
	setCentralWidget(central);
	setMenuBar(menuBar);
	setWindowTitle("Shapes Designer"); // anuny 

	Utility::helpSetupUI(view, 
                     	 commandInput,
                     	 logOutput,
                     	 menuBar,
                     	 layout,
                     	 logTitle,
                     	 consoleTitle);

	connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::onCommandEntered); // stexcumen signal-slot kap, ENTER sexmelis kanchumenq onCommandEntered()

	log("ShapDesigner started. Ready for commands.", Constants::logSuccessColor); 
}

void MainWindow::onNewCanvas() {

	scene->clear();
    shapes.clear();
    m_ownedShapes.clear();
    setupScene();
    log("New canvas created", Constants::logSuccessColor);  

}

void MainWindow::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, 
													tr("Open commands"), 
													"", 
													tr("Text Files (*.txt)"));
    if( fileName.isEmpty() ) return;
	
		QString command = "execute_file \"" + fileName + "\"";
    	parseAndExecute(command);
		log("Opened and executed: " + fileName, Constants::logInfoColor);
}

void MainWindow::onSaveFile() {
    log("Save not implemented yet", Constants::logWarningColor); 
}

void MainWindow::onExit() {
    close();
}

void MainWindow::log( const QString& msg, QColor color ) {
	
	if( !logOutput) return;
	
	QString html = QString("<font color=\"%1\">%2</font><br>")
                   .arg(color.name())
                   .arg(msg.toHtmlEscaped());
	logOutput->append(html); 
	logOutput->ensureCursorVisible();

	QTextEdit* logWidget = logOutput;
	logWidget->setTextColor(color);

	QTextCursor cursor = logWidget->textCursor();
	cursor.movePosition(QTextCursor::End);
	logWidget->setTextCursor(cursor);
	
	logWidget->ensureCursorVisible();

}

void MainWindow::onCommandEntered() {

	QString cmd = commandInput->text().trimmed();
    if( cmd.isEmpty() ) return;
    commandInput->clear();
    log(cmd, Constants::logCommandColor); 

    QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
    std::vector<std::string> tokens;
    for( const auto& p : parts )
        tokens.push_back(p.toStdString());

    auto command = CommandFactory::createCommand(this, tokens);
    if( command ) {
        command->execute();
    } else {
        log("Unknown command", Constants::logErrorColor);
    }

}


void MainWindow::parseAndExecute( const QString& commandLine ) {

	QString clean = commandLine.trimmed();
    if( clean.isEmpty() ) return;

    QStringList qTokens = clean.split(' ', Qt::SkipEmptyParts);
    if( qTokens.isEmpty() ) return;

    std::vector<std::string> tokens;
    for( const auto& t : qTokens ) {
        tokens.push_back(t.toStdString());
    }

    auto command = CommandFactory::createCommand(this, tokens);
    if( command ) {
        command->execute();
    } else {
        log("Unknown or invalid command: " + commandLine, Constants::logErrorColor);
    }	

}

QPointF MainWindow::parseCoord(const QString& s) { // vercnume kordinat{10,20} veradardznun QPointF(10,20), aysinqn string -> coordinate point sarqum
	QRegularExpression re(R"(\{\s*([\-\d.]+)\s*,\s*([\-\d.]+)\s*\})"); // sa regex pattern e stugume teqstn uni {inchvor tiv, inchvor tiv} dzevy amen ir manruqov vor skzbum {-pakagic lini heto tiv, tivy kara .-ov lini kara amboxjakan +-y vor mek kam avel nish lni datark chmna cordinatnery
	QRegularExpressionMatch m = re.match(s); // stugumenq ardyoq patterny hamapatasxanume 
	if( !m.hasMatch() ) throw QString("Invalid coordinate format: " + s); // ete match-y chgtnvec nshanakum e usery sxal dzevachape grel
	return QPointF(m.captured(1).toDouble(), m.captured(2).toDouble()); //ete match-y gtnvel e veradardznum enq QPointF(regex1, regex2);
}

void MainWindow::addShapeLabel(QGraphicsItem* item, const QString& name) {
    QGraphicsTextItem* text = new QGraphicsTextItem(name);
    text->setDefaultTextColor(Constants::shapeLabelTextColor);
    text->setFont(Constants::shapeLabelFont);

    QRectF rect = item->boundingRect();
    QPointF center = rect.center();

    QRectF textRect = text->boundingRect();
    text->setPos(center.x() - textRect.width() / 2, center.y() - textRect.height() / 2);

    scene->addItem(text);
}

void MainWindow::executeCommand(const QStringList& tokens) {
    parseAndExecute(tokens.join(' '));
}

void MainWindow::handleConnect(const QStringList& args) {
    if (args.size() < 2) {
        log("Usage: connect <shape1> <shape2>", Constants::logErrorColor);
        return;
    }

    QString a = args[0];
    QString b = args[1];

    if (!m_ownedShapes.contains(a) || !m_ownedShapes.contains(b)) {
        log("One or both shapes not found: " + a + " or " + b, Constants::logErrorColor);
        return;
    }

    QPointF c1 = m_ownedShapes[a]->center();
    QPointF c2 = m_ownedShapes[b]->center();

    scene->addLine(QLineF(c1, c2), QPen(Constants::connectLineColor, Constants::connectLineWidth));
    log(a + " connected to " + b, Constants::logConnectColor);
}

QString MainWindow::shapeTypeToString(ShapeType type) const {
    switch (type) {
        case ShapeType::TRIANGLE:
            return "Triangle";

        case ShapeType::RECTANGLE:
            return "Rectangle";

        case ShapeType::SQUARE:
            return "Square";

        case ShapeType::LINE:
            return "Line";

        default: return "Unknown";
    }
}

std::vector<double> MainWindow::extractCoordinates(const QStringList& args) {
    std::vector<double> coords;

    for (int i = 0; i < args.size() - 1; ++i) {
        QString lowerToken = args[i].toLower();
        if (lowerToken.startsWith("-coord_")) {
            QString token = args[i + 1].trimmed();
            token = token.remove('(').remove(')').remove('{').remove('}').trimmed();

            QStringList parts = token.split(',');
            if (parts.size() == 2) {
                bool ok1, ok2;
                double x = parts[0].trimmed().toDouble(&ok1);
                double y = parts[1].trimmed().toDouble(&ok2);
                if (ok1 && ok2) {
                    coords.push_back(x);
                    coords.push_back(y);
                }
            }
        }
    }
    return coords;
}

QString MainWindow::extractName(const QStringList& args) const {
    for (int i = 0; i < args.size() - 1; ++i) {
        QString lowerToken = args[i].toLower();
        if (lowerToken == "-name" || lowerToken == "name") {
            QString n = args[i + 1].trimmed();
            n = n.remove('{').remove('}').remove('(').remove(')').trimmed();
            return n;
        }
    }
    return "";
}
