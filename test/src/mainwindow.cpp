// project library
#include "mainwindow.h"

// third-pary
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QStringList>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	setupScene();
    setupUI();

    log("Canvas ready! Type commands below.", Qt::cyan);
    log("Example: create triangle name T1 -coord_1 (0,0) -coord_2 (100,100) -coord_3 (-50,150)", Qt::gray);
}
MainWindow::~MainWindow(){
}
void MainWindow::setupScene() {
	scene = new QGraphicsScene(-500, -400, 1000, 800, this);
	scene->setBackgroundBrush(Qt::white);
	
	canvasLabel = scene->addText("Canvas");
    canvasLabel->setDefaultTextColor(QColor(180, 180, 220, 100));
	canvasLabel->setFont(QFont("Arial", 70, QFont::Bold));
    QRectF rect = canvasLabel->boundingRect();
    canvasLabel->setPos(scene->sceneRect().center() - QPointF(rect.width()/2, rect.height()/2));
}

void MainWindow::setupUI() {
	QWidget* central = new QWidget(this); // stexcume himnakan widget, vorpes kentronakan hatvac
	QVBoxLayout* layout = new QVBoxLayout(central); // stexcuma vertical dasavorvacutyun, asumenq Qt-in vor Canvasy lini verev, log-y nerqev, Consoly amenanergev

	view = new QGraphicsView(scene, this);
	view->setRenderHint(QPainter::Antialiasing); // gceri ankyunnery darcnume hart,aveli sirun
	view->setDragMode(QGraphicsView::ScrollHandDrag); // tuyle talis mknikov sharjel Canvasy
	view->setAlignment(Qt::AlignCenter); // Scene-y kentronacnum e View-i mej

	commandInput = new QLineEdit(this);
	commandInput->setPlaceholderText("Enter command here..."); // user-y grume hrammanery
	commandInput->setFixedHeight(40); // comand consoly darcnume aveli bardzr ev gexecik
	commandInput->setStyleSheet("front-size: 14px: padding: 8px;"); // ^ ^ ^ ^ ^ 

	logOutput = new QTextEdit(this);
	logOutput->setReadOnly(true); // miayn kardalu rejim
	logOutput->setMaximumHeight(220);
	logOutput->setStyleSheet("background-color: black; color: white; font-family: Courier: front-size: 13px;"); // sev fon, spitak teqst 

#if defined(__GNUC__) || defined(__clang__) // anjatenq warningy 
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif	
	
	QMenuBar* menuBar = this->menuBar();
	menuBar->setStyleSheet("background-color: black; color: white; font-size: 14px;");
	menuBar->setFixedHeight(30); // ^ ^ ^ ^ texti guyn ev chap
	QMenu* fileMenu = menuBar->addMenu(tr("File")); // textery voronq kerevan

	fileMenu->addAction(tr("New"), this, &MainWindow::onNewCanvas, QKeySequence::New); // maqrel canvasy vor nory lini + baci Ctrl + N
    
	fileMenu->addAction(tr("Open"), this, &MainWindow::onOpenFile, QKeySequence::Open); // baci fayly + baci Ctrl + O
					
	fileMenu->addAction(tr("&Save As"), this, &MainWindow::onSaveFile, QKeySequence::Save); // pahpani fayly + pahpani Ctrl + S-ov
    
	fileMenu->addSeparator();
    
	fileMenu->addAction(tr("Exit"), this, &QMainWindow::close, QKeySequence::Quit); // Ctrl + F4  vor dursga

    
	QMenu* helpMenu = menuBar->addMenu(tr("Help")); 

    helpMenu->addAction(tr("About"), this, [this]() { // der patrrast chi uxxaki logov kasi et masin
        QMessageBox::information(this, tr("About"),
            tr("Shape Drawer v1.0\n\n"
               "Simple vector drawing with text commands\n"
               "Created with Qt 5/6 + C++\n\n"
               "Press F1 anytime for help"));
	});

	helpMenu->addAction(tr("Command &Help"), this, [this]() {
        log("Available commands:\n"
            "  create triangle name T1 -coord_1 (0,0) -coord_2 (100,100) -coord_3 (50,200)\n"
            "  create square name S1 -coord_1 (200,200) -coord_2 (300,200)\n"
            "  connect Shape1 Shape2\n"
            "  execute_file myfile.txt", Qt::cyan);
    }, Qt::Key_F1); // F1 stexnov kbaci Help-i      

	layout->setContentsMargins(0,0,0,0); // Canvasi shurjy spitak ezrer ereva
	layout->addWidget(menuBar);	// patuhani vra ktexadri userin ognox bloky 
	layout->addWidget(view); // view zbaxecnuma mec taracq, 1 nshanakuma mecana 1 chapov 

	QLabel* logTitle = new QLabel(" Log"); // stexcumenq pitak(log) anunov
	logTitle->setStyleSheet("background-color: black; color: white; font-weight: bold; padding: 4px;"); // console-style panel
	layout->addWidget(logTitle); // avelacnumen Log Window-un

	layout->addWidget(logOutput); // et window-i mejel dnumen mer outputy

	QLabel* consoleTitle = new QLabel(" Command console"); // stexcumenq pitak(command consol) anunov
	consoleTitle->setStyleSheet("background-color: #333333; color: white; font-weight: bold; padding: 4px;");
	layout->addWidget(consoleTitle); // avleacnumenq command console  patuhany
	layout->addWidget(commandInput); // dnumenq useri grac commandy

	setCentralWidget(central);
	resize(1200, 800); // patuhani chapy
	setWindowTitle("Shapes Designer"); // anuny 

	connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::onCommandEntered); // stexcumen signal-slot kap, ENTER sexmelis kanchumenq onCommandEntered()

	log("ShapDesigner started. Ready for commands.", Qt::green); // grumenq arajin haxordagrutyuny logum 
#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif
}

void MainWindow::onNewCanvas() {

	scene->clear();
    shapes.clear();
    m_ownedShapes.clear();
    setupScene();
    log("New canvas created", Qt::green);

}

void MainWindow::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open commands"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        handleExecuteFile(QStringList() << "execute_file" << fileName);
    }
}

void MainWindow::onSaveFile() {
    log("Save not implemented yet", Qt::gray);
}

void MainWindow::onExit() {
    close();
}

void MainWindow::log( const QString& msg, QColor color ) {
	
	if( !logOutput) return;
	
	QString html = QString("<font color=\"%1\">%2</font><br>")
                   .arg(color.name())
                   .arg(msg.toHtmlEscaped());
	logOutput->append(html); // avelacnum es namaky log-um
	logOutput->ensureCursorVisible();
}

void MainWindow::onCommandEntered() {

	QString cmd = commandInput->text().trimmed();
    if ( cmd.isEmpty() ) return;
    commandInput->clear();
    log(cmd, Qt::gray);

    QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
    std::vector<std::string> tokens;
    for ( const auto& p : parts )
        tokens.push_back(p.toStdString());

    auto command = CommandFactory::createCommand(this, tokens);
    if ( command ) {
        command->execute();
    } else {
        log("Unknown command", Qt::red);
    }

}


void MainWindow::parseAndExecute( const QString& commandLine ) {

	QString clean = commandLine.trimmed();
    if (clean.isEmpty()) return;

    QStringList qTokens = clean.split(' ', Qt::SkipEmptyParts);
    if (qTokens.isEmpty()) return;

    std::vector<std::string> tokens;
    for (const auto& t : qTokens) {
        tokens.push_back(t.toStdString());
    }

    auto command = CommandFactory::createCommand(this, tokens);
    if (command) {
        command->execute();
    } else {
        log("Unknown or invalid command: " + commandLine, Qt::red);
    }	

}


QPointF MainWindow::parseCoord(const QString& s) { // vercnume kordinat{10,20} veradardznun QPointF(10,20), aysinqn string -> coordinate point sarqum
	QRegularExpression re(R"(\{\s*([\-\d.]+)\s*,\s*([\-\-d.]+)s*\})"); // sa regex pattern e stugume teqstn uni {inchvor tiv, inchvor tiv} dzevy amen ir manruqov vor skzbum {-pakagic lini heto tiv, tivy kara .-ov lini kara amboxjakan +-y vor mek kam avel nish lni datark chmna cordinatnery
	QRegularExpressionMatch m = re.match(s); // stugumenq ardyoq patterny hamapatasxanume 
	if( !m.hasMatch() ) throw QString("Invalid coordinate format: " + s); // ete match-y chgtnvec nshanakum e usery sxal dzevachape grel
	return QPointF(m.captured(1).toDouble(), m.captured(2).toDouble()); //ete match-y gtnvel e veradardznum enq QPointF(regex1, regex2);
}

void MainWindow::addShapeLabel(QGraphicsItem* item, const QString& name) { 
	if ( !item ) return;
    auto* label = scene->addText(name);
    label->setDefaultTextColor(Qt::darkBlue);
    label->setFont(QFont("Arial", 12, QFont::Bold));
    QRectF r = item->sceneBoundingRect();
    label->setPos(r.center().x() - label->boundingRect().width()/2, r.bottom() + 8);
}

void MainWindow::executeCommand(const QStringList& tokens) {
    parseAndExecute(tokens.join(' '));
}

void MainWindow::handleConnect(const QStringList& args) {
   
	if( args.size() < 2 ) {
        log("Usage: connect <shape1> <shape2>", Qt::red);
        return;
    }

    QString a = args[0];
    QString b = args[1];

    if( !m_ownedShapes.contains(a) || !m_ownedShapes.contains(b) ) {
        log("One or both shapes not found: " + a + " or " + b, Qt::red);
        return;
    }

    QPointF c1 = m_ownedShapes[a]->center();
    QPointF c2 = m_ownedShapes[b]->center();

    scene->addLine(QLineF(c1, c2), QPen(Qt::red, 3));
    log(a + " connected to " + b, Qt::yellow);

}

QString MainWindow::shapeTypeToString(ShapeType type) const {

    switch(type) {
    
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

void MainWindow::handleExecuteFile(const QStringList& tokens) {
 
    QString filePath = tokens[1];
    QFile file(filePath);
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        log("Cannot open file: " + filePath, Qt::red);
        return;
    }
    QTextStream in(&file);
    int lineNum = 0;
    while ( !in.atEnd() ) {
        QString line = in.readLine().trimmed();
        lineNum++;
        if ( line.isEmpty() || line.startsWith("#" )) continue;
        log(QString(">> %1").arg(line), Qt::darkGray);
        parseAndExecute(line);
    }
    log("File executed: " + filePath, Qt::green);
    file.close();

}

std::vector<double> MainWindow::extractCoordinates(const QStringList& args) {
    std::vector<double> coords;

    for (int i = 0; i < args.size(); ++i) {
        if (!args[i].startsWith("-coord_")) continue;
        if (i + 1 >= args.size()) continue;

        QString token = args[i + 1].trimmed();

        if (token.startsWith('{') && token.endsWith('}')) {
            QString inside = token.mid(1, token.length() - 2);
            QStringList parts = inside.split(',');
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
        if (args[i] == "-name" || args[i] == "name") {
            QString n = args[i + 1];
            if (n.startsWith('{') && n.endsWith('}')) {
                n = n.mid(1, n.length() - 2);
            }
            return n;
        }
    }
    return "";

}
