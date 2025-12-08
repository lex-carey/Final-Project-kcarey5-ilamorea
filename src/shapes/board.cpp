#include "board.h"


Board::Board(Shader& shader) {
    boardWidth = 30, boardHeight = 16, boardMines = 99;
    for (int i = 0; i < boardWidth; i++) {
        totalWidth = 0;
        while (totalWidth < 660) {
            totalHeight = 0;
            vector<Tile> tiles;
            while (totalHeight < 352) {
                tiles.push_back(Tile(shader, vec2(71 + totalWidth + 10, 196 + totalHeight + 10), vec2(20, 20), color(154/255.0, 154/255.0, 154/255.0, 1)));
                totalHeight += 22;
            }
            board->push_back(tiles);
            totalWidth += 22;
        }
    }
}

Board::~Board() {
    for (vector<Tile> &tiles : board) {
        for (int i = 0; i < tiles.size(); i++) {
            tiles[i].~Tile();
        }
    }
}

void Board::setUniformsAndDraw() const {
    for (const std::unique_ptr<vector<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            tile->setUniforms();
            tile->draw();
        }
    }
}

int Board::getTotalMines(std::unique_ptr<vector<vector<Tile>>>& board) const {
    int num = 0;
    for (const std::unique_ptr<vector<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            if (tile->getState() > 0) num++;
        }
    }
    return num;
}

int Board::getMaxMinesAllowed(std::unique_ptr<vector<vector<Tile>>>& board) const {
    int num = 0;
    for (const std::unique_ptr<vector<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            if (tile->getState() == 0) num++;
        }
    }
    return num;
}

void Board::placeRandomMines(std::unique_ptr<vector<vector<Tile>>>& board, int& numleft) {
    int num = getMaxMinesAllowed(board);
    if (numleft > num) numleft = num;
    while (numleft > 0) {
        int posx = rand() % boardWidth;
        int posy = rand() % boardHeight;
        while ((*board)[posx][posy].getState() != 0)
        {
            posx = rand() % boardWidth;
            posy = rand() % boardHeight;
        }
        (*board)[posx][posy].setState(1);
        numleft--;
    }
}

void Board::clearPoint(std::unique_ptr<vector<vector<Tile>>>& board, int& posx, int& posy) {
    int num = 0;
    for (int x = posx - 1; x <= posx + 1; x++) {
        if (x >= 0 && x < boardWidth) {
            for (int y = posy - 1; y <= posy + 1; y++) {
                if (y >= 0 && y < boardHeight) {
                    if ((*board)[x][y].getState() > 0) num++;
                    if ((*board)[x][y].getState() <= 1) (*board)[x][y].setState(-1);
                }
            }
        }
    }
    placeRandomMines(board, num);
}

int Board::getNumMinesPoint(std::unique_ptr<vector<vector<Tile>>>& board, int& x, int& y) const {
    int num = 0;
    if (x > 0 && y > 0 && (*board)[x-1][y-1].getState() > 0) num++;
    if (x > 0 && (*board)[x-1][y].getState() > 0) num++;
    if (y < boardHeight - 1 && x > 0 && (*board)[x-1][y+1].getState() > 0) num++;
    if (y > 0 && (*board)[x][y-1].getState() > 0) num++;
    if (y < boardHeight - 1 && (*board)[x][y+1].getState() > 0) num++;
    if (y > 0 && x < boardWidth - 1 && (*board)[x+1][y-1].getState() > 0) num++;
    if (x < boardWidth - 1 && (*board)[x+1][y].getState() > 0) num++;
    if (y < boardHeight - 1 && x < boardWidth - 1 && (*board)[x+1][y+1].getState() > 0) num++;
    return num;
}

void Board::openBoardPosition(vector<vector<int>> &points, std::unique_ptr<vector<vector<Tile>>> &board, std::unique_ptr<vector<vector<Tile>>> &dispBoard, int x, int y) {
    if ((*board)[x][y].getState() < 0) (*dispBoard)[x][y].setState(-1);
    else if ((*board)[x][y].getState() == 1) (*dispBoard)[x][y].setState(1);
    else if ((*board)[x][y].getState() == 2) (*dispBoard)[x][y].setState(2);
    points.push_back(vector<int>{x, y});
    if (getNumMinesPoint(board, x, y) != 0) {
        if (x > 0 && y > 0 && (*board)[x-1][y-1].getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y-1);
        if (x > 0 && (*dispBoard)[x-1][y].getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y);
        if (x > 0 && y < boardHeight - 1 && (*dispBoard)[x-1][y+1].getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y+1);
        if (y > 0 && (*dispBoard)[x][y-1].getState() == 0) openBoardPosition(points, board, dispBoard, x, y-1);
        if (y < boardHeight - 1 && (*dispBoard)[x][y+1].getState() == 0) openBoardPosition(points, board, dispBoard, x, y+1);
        if (y > 0 && x < boardWidth - 1 && (*dispBoard)[x+1][y-1].getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y-1);
        if (x < boardWidth - 1 && (*dispBoard)[x+1][y].getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y);
        if (y < boardHeight - 1 && x < boardWidth - 1 && (*dispBoard)[x+1][y+1].getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y+1);
    }
}

vector<vector<int>> Board::getMinesAtPoint(std::unique_ptr<vector<vector<Tile>>>& board, int x, int y) {
    vector<vector<int>> points;
    if (x > 0 && y > 0 && (*board)[x-1][y-1].getState() > 0) points.push_back(vector<int>{x-1, y-1});
    if (y > 0 && (*board)[x][y-1].getState() > 0) points.push_back(vector<int>{x, y-1});
    if (x < boardWidth - 1 && y > 0 && (*board)[x+1][y-1].getState() > 0) points.push_back(vector<int>{x+1, y-1});
    if (x > 0 && (*board)[x-1][y].getState() > 0) points.push_back(vector<int>{x-1, y});
    if (x < boardWidth - 1 && (*board)[x+1][y].getState() > 0) points.push_back(vector<int>{x+1, y});
    if (x > 0 && y < boardHeight - 1 && (*board)[x-1][y+1].getState() > 0) points.push_back(vector<int>{x-1, y+1});
    if (y < boardHeight - 1 && (*board)[x][y+1].getState() > 0) points.push_back(vector<int>{x, y+1});
    if (x < boardWidth - 1 && y < boardHeight - 1 && (*board)[x+1][y+1].getState() > 0) points.push_back(vector<int>{x+1, y+1});
    return points;
}

vector<vector<int>> Board::getAvailablePoints(std::unique_ptr<vector<vector<Tile>>>& board, int& x, int& y) {
    vector<vector<int>> points;
    if (x > 0 && y > 0 && (*board)[x-1][y-1].getState() == 0) points.push_back(vector<int>{x-1, y-1});
    if (y > 0 && (*board)[x][y-1].getState() == 0) points.push_back(vector<int>{x, y-1});
    if (x < boardWidth - 1 && y > 0 && (*board)[x+1][y-1].getState() == 0) points.push_back(vector<int>{x+1, y-1});
    if (x > 0 && (*board)[x-1][y].getState() == 0) points.push_back(vector<int>{x-1, y});
    if (x < boardWidth - 1 && (*board)[x+1][y].getState() == 0) points.push_back(vector<int>{x+1, y});
    if (x > 0 && y < boardHeight - 1 && (*board)[x-1][y+1].getState() == 0) points.push_back(vector<int>{x-1, y+1});
    if (y < boardHeight - 1 && (*board)[x][y+1].getState() == 0) points.push_back(vector<int>{x, y+1});
    if (x < boardWidth - 1 && y < boardHeight - 1 && (*board)[x+1][y+1].getState() == 0) points.push_back(vector<int>{x+1, y+1});
    return points;
}

void Board::generateBoard(int &startx, int &starty) {
    clearPoint(board, startx, starty);
    placeRandomMines(board, boardMines);
    vector<vector<int>> solver;
    std::unique_ptr<vector<vector<Tile>>> solverBoard;
    int minesLeft = getTotalMines(board);
    int spacesLeft = boardWidth * boardHeight;
    openBoardPosition(solver, board, solverBoard, startx, starty);
    for (vector<int> &tile : solver) {
        (*board)[tile[0]][tile[1]].setState(-1);
        (*solverBoard)[tile[0]][tile[1]].setState(-1);
    }
    while (solver.size() > 0) {
        int spacesLeft2 = spacesLeft;
        int numPoints = solver.size();
        for (vector<int> &tile : solver) {
            auto mines = getMinesAtPoint(board, tile[0], tile[1]);
            auto smines = getMinesAtPoint(solverBoard, tile[0], tile[1]);
            auto savail = getAvailablePoints(solverBoard, tile[0], tile[1]);
            if (mines.size() == smines.size()) {
                for (vector<int> &tile2 : savail) {
                    (*solverBoard)[tile2[0]][tile2[1]].setState(-1);
                    (*board)[tile2[0]][tile2[1]].setState(-1);
                    spacesLeft--;
                    solver.push_back(tile2);
                }
                solver.erase(solver.begin());
                (*solverBoard)[tile[0]][tile[1]].setState(-1);
                (*board)[tile[0]][tile[1]].setState(-1);
                spacesLeft--;
            }
            else if (mines.size() == smines.size() + savail.size()) {
                for (vector<int> &tile2 : savail) {
                    (*solverBoard)[tile2[0]][tile2[1]].setState(1);
                    (*board)[tile2[0]][tile2[1]].setState(2);
                    spacesLeft--;
                }
                solver.erase(solver.begin());
                (*solverBoard)[tile[0]][tile[1]].setState(-1);
                (*board)[tile[0]][tile[1]].setState(-1);
                spacesLeft--;
            }
            else if (mines.size() - smines.size() == 2 && savail.size() == 3) {
                bool found = false;
                if (tile[1] > 0 && tile[1] < boardHeight - 1 && (*board)[tile[0]][tile[1] - 1].getState() <= 0 && (*board)[tile[0]][tile[1] + 1].getState() <= 0) {
                    auto mines2 = getMinesAtPoint(board, tile[0], tile[1] - 1);
                    auto smines2 = getMinesAtPoint(solverBoard, tile[0], tile[1] - 1);
                    auto mines3 = getMinesAtPoint(board, tile[0], tile[1] + 1);
                    auto smines3 = getMinesAtPoint(solverBoard, tile[0], tile[1] + 1);
                    if (mines2.size() - smines2.size() == 1 && mines3.size() - smines3.size() == 1) {
                        for (vector<int> &tile2 : savail) {
                            if (tile2[1] == tile[1]) {
                                (*solverBoard)[tile2[0]][tile2[1]].setState(-1);
                                (*board)[tile2[0]][tile2[1]].setState(-1);
                                solver.push_back(tile2);
                            }
                            else {
                                (*solverBoard)[tile2[0]][tile2[1]].setState(1);
                                (*board)[tile2[0]][tile2[1]].setState(2);
                            }
                            spacesLeft--;
                        }
                        solver.erase(solver.begin());
                        (*solverBoard)[tile[0]][tile[1]].setState(-1);
                        (*board)[tile[0]][tile[1]].setState(-1);
                        spacesLeft--;
                        found = true;
                    }
                }
                if (!found && tile[0] > 0 && tile[0] < boardWidth - 1 && (*board)[tile[0] - 1][tile[1]].getState() <= 0 && (*board)[tile[0] + 1][tile[1]].getState() <= 0) {
                    auto mines2 = getMinesAtPoint(board, tile[0] - 1, tile[1]);
                    auto smines2 = getMinesAtPoint(solverBoard, tile[0] - 1, tile[1]);
                    auto mines3 = getMinesAtPoint(board, tile[0] + 1, tile[1]);
                    auto smines3 = getMinesAtPoint(solverBoard, tile[0] + 1, tile[1]);
                    if (mines2.size() - smines2.size() == 1 && mines3.size() - smines3.size() == 1)
                    {
                        for (vector<int> &tile2 : savail) {
                            if (tile2[0] == tile[0]) {
                                (*solverBoard)[tile2[0]][tile2[1]].setState(-1);
                                (*board)[tile2[0]][tile2[1]].setState(-1);
                                solver.push_back(tile2);
                            }
                            else {
                                (*solverBoard)[tile2[0]][tile2[1]].setState(1);
                                (*board)[tile2[0]][tile2[1]].setState(2);
                            }
                            spacesLeft--;
                        }
                        solver.erase(solver.begin());
                        (*solverBoard)[tile[0]][tile[1]].setState(-1);
                        (*board)[tile[0]][tile[1]].setState(-1);
                        spacesLeft--;
                    }
                }
            }
            else if (mines.size() - smines.size() == 1 && ) {}
        }
    }
}

void Board::setSurroundingBombs() {
   for (int x = 0; x < boardWidth; x++) {
       for (int y = 0; y < boardHeight; y++) {
           int numMines = getNumMinesPoint(board, x, y);
           (*board)[x][y].setSurrBombs(numMines);
       }
   }
}









