# ShapeDesigner
A functional vector graphics editor  with command-line interface**, written from scratch in C++11 and Qt6.

# Features
- `create_line`, `create_triangle`, `create_rectangle`, `create_square`
- `execute_file filename.txt` – executes the entire file
- File → Open – opens and automatically executes a .txt file
- Colored log/console
- Does not allow duplicate names
- Automatic scroll in log
- No memory leak

# How to use: 
	Line:
		`create_line -name {line_name} -coord_1 {0,3} -coord_2 {3.5,-1}`
			Creates a line from `coord_1 to coord_2.`

	Triangle:
		`create_triangle -name {triangle_name} -coord_1 {0,0} -coord_2 {3,0} -coord_3 {0,4}
			Creates a triangle with vertices at coord_1, coord_2, and coord_3.`

	Rectangle:
		create_rectangle -name {rect_name} -coord_1 {0,0} -coord_2 {3,4}
			Creates a rectangle with a diagonal from coord_1 to coord_2.

	create_rectangle -name {rect_name} -coord_1 {0,0} -coord_2 {3,0} -coord_3 {0,4} -coord_4 {3,4}

		Creates a rectangle using four specified corner coordinates.
	Square:
		create_square -name {sqr_name} -coord_1 {0,0} -coord_2 {3,3}
			Creates a square with a diagonal from coord_1 to coord_2.

	create_square -name {sqr_name} -coord_1 {0,0} -coord_2 {3,3} -coord_3 {3,0} -coord_4 {0,3}
		Creates a square using four specified vertice coordinates.	

	Connecting Objects:
		connect -object_name_1 {star_name} -object_name_2 {rect_name}
			Connects the centers of two shapes with a straight line.

	Batch Command Execution:
		execute_file -file_path {../a/b/c/d/script.txt}
			Executes multiple commands from a specified file, drawing the corresponding shapes on the canvas.

# How to run
- must Ubuntu / Linux or Qt Creator

# Run
 If you have a Qt Creator application then:
 Open Qt Creator → Open Project → select mini-canvas.pro
 Click Build → Run
 

 if you don't have it installing Qt6 and qmake`
	sudo apt update
sudo apt install qt6-base-dev qt6-declarative-dev qt6-tools-dev-tools qmake6 build-essential -y
 
 2.Go to the project folder
	 cd /path/to/QtShapesApp/GUI app
 
 3. Compiling 
		. qmake6
		. make (make -j8 or make -j12)

# Launching
 ./ShapeCanvas
