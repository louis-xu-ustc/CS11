//
// Created by Yunpeng Xu on 1/12/17.
//

#include <cassert>
#include "maze.hh"

// helper functions

// Parameter checker
void Maze::paraChecker(int row, int col) const {
	// Assert viable coordinates
	assert((row >= 0) && (row < getNumRows()));
	assert((col >= 0) && (col < getNumCols()));
}

int Maze::getNumExpCoord() const {
	return (2 * getNumRows() + 1) * (2 * getNumCols() + 1);
}

// Take 2D expanded coordinates and compute the corresponding 1D array index
int Maze::getArrayIndex(const Location &loc) const {
	int arrayIndex = loc.row * getNumCols() + loc.col;
	return arrayIndex;
}

// Returns the expanded coordinates of the specified cell coordinates
Location Maze::getCellArrayCoord(int cellRow, int cellCol) const {
	paraChecker(cellRow, cellCol);
	return Location(cellRow * 2 + 1, cellCol * 2 + 1);
}

// Returns the expanded coordinates of the wall on a specific side of
// a cell given in cell coordinates
Location Maze::getWallArrayCoord(int cellRow, int cellCol,
                                 Direction direction) const {
	paraChecker(cellRow, cellCol);
	Location loc = getCellArrayCoord(cellRow, cellCol);
	int expRow = loc.row;
	int expCol = loc.col;
	switch (direction) {
		case Direction::NORTH:
			expRow -= 1;
			break;
		case Direction::EAST:
			expCol += 1;
			break;
		case Direction::SOUTH:
			expRow += 1;
			break;
		case Direction::WEST:
			expCol -= 1;
			break;
		
	}
	return Location(expRow, expCol);
}


//Initialize a new maze of size rows x cols
Maze::Maze(int rows, int cols) {
	numRows = rows;
	numCols = cols;
	int numExpCoord = getNumExpCoord();
	cells = new MazeCell[numExpCoord];
	for (int i = 0; i < numExpCoord; i++) {
		cells[i] = MazeCell::EMPTY;
	}
	start = Location(0, 0);
	end = Location(0, 0);
}

// Make a copy of an existing maze object
Maze::Maze(const Maze &m) {
	numRows = m.getNumRows();
	numCols = m.getNumCols();
	int numExpCoord = m.getNumExpCoord();
	cells = new MazeCell[numExpCoord];
	for (int i = 0; i < numExpCoord; i++) {
		cells[i] = m.cells[i];
	}
	start = Location(0, 0);
	end = Location(0, 0);
}

// Maze destructor
Maze::~Maze() {
	delete[] cells;
}

// Maze assignment operator
Maze &Maze::operator=(const Maze &m) {
	if (this != &m) {
		delete[] cells;
		numRows = m.getNumRows();
		numCols = m.getNumCols();
		int numExpCells = m.getNumExpCoord();
		cells = new MazeCell[numExpCells];
		for (int i = 0; i < numExpCells; i++) {
			cells[i] = m.cells[i];
		}
		start = m.getStart();
		end = m.getEnd();
	}
	return *this;
}

// Returns the number of rows in the maze
int Maze::getNumRows() const {
	return numRows;
}

// Returns the number of cols in the maze
int Maze::getNumCols() const {
	return numCols;
}

// Returns the starting point in the maze
Location Maze::getStart() const {
	return start;
}

// Sets the starting point in the maze
void Maze::setStart(int row, int col) {
	start = Location(row, col);
}

// Returns the ending point in the maze
Location Maze::getEnd() const {
	return end;
}

// Sets the ending point in the maze
void Maze::setEnd(int row, int col) {
	end = Location(row, col);
}

// Sets all cells and walls to be empty, so that the maze
// is completely cleared
void Maze::clear() {
	int numExpCoord = getNumExpCoord();
	for (int i = 0; i < numExpCoord; i++) {
		cells[i] = MazeCell::EMPTY;
	}
}

// Returns the value of the specified
MazeCell Maze::getCell(int cellRow, int cellCol) const {
	paraChecker(cellRow, cellCol);
	Location loc = Location(cellRow, cellCol);
	int arrayIndex = getArrayIndex(loc);
	return cells[arrayIndex];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val) {
	paraChecker(cellRow, cellCol);
	Location loc = Location(cellRow, cellCol);
	int arrayIndex = getArrayIndex(loc);
	cells[arrayIndex] = val;
}

// Returns the cell-coordinates of the neighboring cell in the specified
// direction.  Trips an assertion if the given cell has no neighbor in the
// specified direction (e.g. the NORTH neighbor of cell (0,5)).
Location Maze::getNeighborCell(int cellRow, int cellCol,
                               Direction direction) const {
	paraChecker(cellRow, cellCol);
	Location loc;
	switch (direction) {
		case Direction::NORTH:
			assert(cellRow > 0);
			loc = Location(cellRow - 1, cellCol);
			break;
		case Direction::EAST:
			assert(cellCol < numCols - 1);
			loc = Location(cellRow, cellCol + 1);
			break;
		case Direction::SOUTH:
			assert(cellRow < numRows - 1);
			loc = Location(cellRow + 1, cellCol);
			break;
		case Direction::WEST:
			assert(cellCol > 0);
			loc = Location(cellRow, cellCol - 1);
			break;
	}
	return loc;
}

// Returns true if there is a wall in the specified direction from the
// given cell, false otherwise
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const {
	Location wallArrayCoord = getWallArrayCoord(cellRow, cellCol, direction);
	
	return cells[getArrayIndex(wallArrayCoord)] == MazeCell::WALL;
}

// Puts a wall on the specified side of the given cell
void Maze::setWall(int cellRow, int cellCol, Direction direction) {
	Location wallArrayCoord = getWallArrayCoord(cellRow, cellCol, direction);
	cells[getArrayIndex(wallArrayCoord)] = MazeCell::WALL;
}

// Removes a wall on the specified side of the given cell
void Maze::clearWall(int cellRow, int cellCol, Direction direction) {
	Location wallArrayCoord = getWallArrayCoord(cellRow, cellCol, direction);
	cells[getArrayIndex(wallArrayCoord)] = MazeCell::EMPTY;
}

// Places a wall at every location that can be a wall in the maze
void Maze::setAllWalls() {
	for (int i = 0; i < getNumRows(); i++) {
		for (int j = 0; j < getNumCols(); j++) {
			for (int k = (int) Direction::NORTH; static_cast<Direction>(k) <= Direction::WEST; k++) {
				Direction wallDir = static_cast<Direction> (k);
				setWall(i, j, wallDir);
			}
		}
	}
}

// Returns true if the specified maze cell has been visited.
bool Maze::isVisited(int cellRow, int cellCol) const {
	Location loc = getCellArrayCoord(cellRow, cellCol);
	return cells[getArrayIndex(loc)] == MazeCell::VISITED;
}

// Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol) {
	Location loc = getCellArrayCoord(cellRow, cellCol);
	cells[getArrayIndex(loc)] = MazeCell::VISITED;
}

// Outputs the maze using simple ASCII-art to the specified output stream.
// The output format is as follows, using the example maze from the
// assignment write-up.  (The text to the right of the maze is purely
// explanatory, and you don't need to output it.)
//
// 3 4                 (# of rows and then # of columns)
// +---+---+---+---+   (each cell is 3 spaces wide, with a + at each corner)
// | S     |       |   (walls indicated by --- or |)
// +---+   +   +   +   (start indicated by S, end indicated by E)
// |   |   |   |   |
// +   +   +   +   +
// |           | E |
// +---+---+---+---+
void Maze::print(std::ostream &os) const {
	os << getNumRows() << getNumCols() << std::endl;
	int numExpRows = getNumRows();
	int numExpCols = getNumCols();
	for (int i = 0; i < numExpRows; i++) {
		for (int j = 0; j < numExpCols; j++) {
			Location curLoc = Location(i, j);
			int curIndex = getArrayIndex(curLoc);
			if ((i & 1) == 0 && (j & 1) == 0) os << "+"; // Neither cell or wall
			else if ((i & 1) == 0 || (j & 1) == 0) { // Wall
				if ((j & 1) == 0) { // Horizontal
					if (cells[curIndex] == MazeCell::WALL) {
						os << "---";
					} else {
						os << "   ";
					}
				} else { // Vertical
					if (cells[curIndex] == MazeCell::WALL) {
						os << "|";
					} else {
						os << " ";
					}
				}
			} else { // cell
				if (curLoc == getStart()) os << "S";
				else if (curLoc == getEnd()) os << "E";
			}
		}
		os << std::endl;
	}
}







