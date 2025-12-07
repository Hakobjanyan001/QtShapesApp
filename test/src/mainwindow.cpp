#include <mainwindow.h>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	scene = new QGraphicsScene(-500, -400, 1000, 800, this);
	scene->setBackgroundBrush(Qt::white);

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
	logOutput->setStyleSheet("background-color: black; color: white; front-family: Courier: front-size: 13px;"); // sev fon, spitak teqst 
	logOutput->setMinimumHeight(160); // log-y chi gravum amboxj patuhany
	logOutput->setMaximumHeight(200);

	canvasLabel = scene->addText("Canvas"); // scene-um avelacnumenq text => "Canvas"
	canvasLabel->setDefaultTextColor(Qt::lightGray); // mec bac moxraguyn "Canvas" bar
	canvasLabel->setFont(QFont("Arial", 30, QFont::Bold)); // ^ ^ ^ ^
	QRectF cr = scene->sceneRect(); // hetaga toxery Canvas grutyuny texadrum e kentron
	canvasLabel->setPos(
		cr.center() - QPointF(
			canvasLabel->boundingRect().width()/2, 
			canvasLabel->boundingRect().height()/2
		)
	);

	QMenuBar* menuBar = new QMenuBar(this); // stexcenq patuhanum ognox tox
	menuBar->setStyleSheet("background-color: black; color: white; font-size: 14px;");
	menuBar->setFixedHeight(30); // ^ ^ ^ ^ texti guyn ev chap
	QMenu* fileMenu = menuBar->addMenu("File"); // textery voronq kerevan
	QMenu* helpMenu = menuBar->addMenu("Help"); // ^ ^ ^ ^ 

	QWidget* centralWidget = new QWidget(this); // stexcume himnakan widget, vorpes kentronakan hatvac
	QWBoxLayout* layout = new QVBoxLayout(centralWidget); // stexcuma vertical dasavorvacutyun, asumenq Qt-in vor Canvasy lini verev, log-y nerqev, Consoly amenanergev
	layout->setContentsMargins(0,0,0,0); // Canvasi shurjy spitak ezrer ereva
	layout->addWidget(menuBar);	// patuhani vra ktexadri userin ognox bloky 
	layout->addWidget(view); // view zbaxecnuma mec taracq, 1 nshanakuma mecana 1 chapov 

	Qlabel* logTitle = new Qlabel(" Log"); // stexcumenq pitak(log) anunov
	logTitle->setStyleSheet("background-color: black; color: white; font-weight: bold; padding: 4px;"); // console-style panel
	layout->addWidget(logTitle); // avelacnumen Log Window-un

	layout->addWidget(logOutput); // et window-i mejel dnumen mer outputy

	QLabel* consoleTitle = new QLabel(" Command console"); // stexcumenq pitak(command consol) anunov
	consoleTitle->setStyleSheet("background-color: #333333; color: white; font-weight: bold; padding: 4px;");
	layout->addWidget(consoleTitle); // avleacnumenq command console  patuhany
	layout->addWidget(commandInput); // dnumenq useri grac commandy

	setCentralWidget(centralWidget); 
	resize(1200, 800); // patuhani chapy
	setWindowTitle("Shapes Designer"); // anuny 

	connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::onCommandEntered); // stexcumen signal-slot kap, ENTER sexmelis kanchumenq onCommandEntered()

	log("ShapDesigner started. Ready for commands.", Qt::green); // grumenq arajin haxordagrutyuny logum 
}

MainWindow::~MainWindow() {}

void MainWindow::log(const QString& msg, QColor color) {
	logOutput->setTextColor(color); // log texti guynne talis
	logOutput->append(msg); // avelacnum es namaky log-um
}


QPointF MainWindow::parseCoord(const QString& s) { // vercnume kordinat{10,20} veradardznun QPointF(10,20), aysinqn string -> coordinate point sarqum
	QRegularExpression re(R"(\{\s*([\-\d.]+)\s*,\s*([\-\-d.]+)s*\})"); // sa regex pattern e stugume teqstn uni {inchvor tiv, inchvor tiv} dzevy amen ir manruqov vor skzbum {-pakagic lini heto tiv, tivy kara .-ov lini kara amboxjakan +-y vor mek kam avel nish lni datark chmna cordinatnery
	QRegularExpressionMatch m = re.match(s); // stugumenq ardyoq patterny hamapatasxanume 
	if(!m.hasMatch()) throw QString("Invalid coordinate format: " + s); // ete match-y chgtnvec nshanakum e usery sxal dzevachape grel
	return QPointF(m.captured(1).toDouble(), m.captured(2).toDouble()); //ete match-y gtnvel e veradardznum enq QPointF(regex1, regex2);
}

void MainWindow::addShapeWithLabel(QGraphicsLineItem* item, const QString& name) { 
	shapes[name] = item; // ays map-y pahume figurnery yst anuni
	if (auto *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) { //stugum shape te che, ete shape e uni color/brush 
		shape->setBrush(QBrush(Qt::blue)); // ete shape e nerkumenq 
	}
	
	QGraphicsTextItem* text = scene->addText(name); // scene-um shape-i vra grumenq ira anuny
	text->setDefaultTextColor(Qt::white);	// shap-i anuny spitak
	text->setFont(QFont("Arial", 14, QFont::Bold)); // taratesak, tarachap, bold-hast

	QPointF center = item->boundingRect().center(); // teqsty dni shape-i kentronum
	text->setPos( // texadri teqsti kentrony shape-i kentroni vra
		item->pos()
	   	+ center
	   	- QPointF(text->boundingRect().width()/2, text->boundingRect().height()/2)
	); 

	if(shapes.size() == 1) canvasLabel->hide(); // ete shape chak "Canvas" gracy ereva, hakarak depqum taqcni

	log(name + " created", Qt::green);	// log-um kanach guynov cucenq tali vor shap-y stexcvec
}

void MainWindow::onCommandEntered() {
	QString comd = commandInput->text().trimmed();
	if(cmd.isEmpty()) return;

	log(comd, Qcolor(255, 85, 85));
	parseAndExecute(comd);
	commandInput->clear();
}

void MainWindow::parseAndExecute(const QString& comdLine) {
	QStringList parts = comdLine.split(" ", Qt::SkipEmptyParts);
	if(parts.isEmpty()) return;

	QString command = parts[0];

	try{
		if(command.startsWith("create_")) {
			QString type = command.mid(7); 
			QString name;
			std::vector<double> coords;

			for(int i = 1; i < parts.size(); ++i) {
				if(parts[i] == "name") {
					name = parts[++i];
				} else if(parts[i].startsWith("-coord_")) {
					QPointF p = parseCoord(parts[++i]);
					cords.push_back(p.x());
					cords.push_back(p.y());
				}
			}
		std::unique_ptr<Shape> shape = ShapeFactory::createShape(type.toStdString(), name.toStdString(), coords);
		    if(!shape) {
		        throw QString("Invalid shape or coordinates");
		    }
		
		    shape->draw(scene);   
		
		    QString qname = QString::fromStdString(shape->getName());
		
		    QGraphicsItem* item = shape->graphicsItem();
		    if(item) {
		        shapes[qname] = item;
		        addShapeWithLabel(item, qname);
		        m_ownedShapes[qname] = std::move(shape);   
		        log(qname + " created", Qt::green);
		    } else {
		        log("Failed to create item", Qt::red);
		    }
		}
}else if(command == "connect"){
			if(parts.size() < 3) throw QString("Usage: connect name1, name 2");
			QString name1 = parts[1];
			QString name2 = parts[2];
			
			if(!shapeMap.contains(name1)) throw QString("Shape not found: " + name1);
			if(!shapeMap.contains(name2)) throw QString("Shape not found: " + name2);
			
			Shape* s1 = shapeMap[name1].get();
			Shape* s2 = shapeMap[name2].get();

			QPointF c1 = s1->center();
			QPointF c2 = s2->center();

			scene->addLine(QLineF(c1, c2), QPen(Qt::red, 2))

			log(QString("Connected ".arg(name1, name2), Qt::green));
		}else if(command == "execute_file") {
			if(parts.size() < 2) throw QString("Usage: execute_file filename") 
			QString filename = parts[1];

			QFile file(filename);
			if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				throw QString("cannot open file" + filename);
			}

			QTextStream in(&file);

			while(!in.atEnd()) {
				QString line = in.readLine().trimmed();
				if(line.isEmpty()) continue;
				parseAndExecute(line);

			}
			log("executed " + filename, Qt::green);
		} else {
			throw QString("Unknow command " + command);
		} 
	} catch(const QString& err) {
		log("Error " + err, Qt::red)
	}
}

void MainWindow::connectShapes(const QString& name1, const QString& name2) {
	if(!shape.contains(name1) || !shape.contains(name2)) {
		log("Shapes not found", Qt::red);
		return;
	}
	QPointF center1 = shapes[name1]->boundingRect().center() + shapes[name1]->pos();
	QPointF center2 = shapes[name2]->boundingRect().center() + shapes[name2]->pos();
	scene->addLine(QLineF(center1, center2), QPen(Qt::black));
	log(name1 + " connected to " + name2, QColor(0, 255, 0));
}
