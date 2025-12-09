#include "board.h"


Board::Board(Shader& shader) {
    boardWidth = 30, boardHeight = 16, boardMines = 99;
    for (int i = 0; i < boardWidth; i++) {
        totalWidth = 0;
        while (totalWidth < 660) {
            totalHeight = 0;
            while (totalHeight < 352) {
                board[i].push_back(std::make_unique<Tile>(shader, vec2(71 + totalWidth + 10, 196 + totalHeight + 10), vec2(20, 20), color(154/255.0, 154/255.0, 154/255.0, 1)));
                totalHeight += 22;
            }
            totalWidth += 22;
        }
    }
}

Board::~Board() {
    for (vector<std::unique_ptr<Tile>> &tiles : board) {
        for (int i = 0; i < tiles.size(); i++) {
            tiles[i]->~Tile();
        }
    }
}

void Board::setUniformsAndDraw() const {
    for (const vector<std::unique_ptr<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            tile->setUniforms();
            tile->draw();
        }
    }
}

int Board::getTotalMines(vector<vector<std::unique_ptr<Tile>>>& board) const {
    int num = 0;
    for (const vector<std::unique_ptr<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            if (tile->getState() > 0) num++;
        }
    }
    return num;
}

int Board::getMaxMinesAllowed(vector<vector<std::unique_ptr<Tile>>>& board) const {
    int num = 0;
    for (const vector<std::unique_ptr<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            if (tile->getState() == 0) num++;
        }
    }
    return num;
}

void Board::placeRandomMines(vector<vector<std::unique_ptr<Tile>>>& board, int& numleft) {
    int num = getMaxMinesAllowed(board);
    if (numleft > num) numleft = num;
    while (numleft > 0) {
        int posx = std::rand() % boardWidth;
        int posy = std::rand() % boardHeight;
        while ((board)[posx][posy]->getState() != 0)
        {
            posx = std::rand() % boardWidth;
            posy = std::rand() % boardHeight;
        }
        (board)[posx][posy]->setState(1);
        numleft--;
    }
}

void Board::clearPoint(vector<vector<std::unique_ptr<Tile>>>& board, int& posx, int& posy) {
    int num = 0;
    for (int x = posx - 1; x <= posx + 1; x++) {
        if (x >= 0 && x < boardWidth) {
            for (int y = posy - 1; y <= posy + 1; y++) {
                if (y >= 0 && y < boardHeight) {
                    if ((board)[x][y]->getState() > 0) num++;
                    if ((board)[x][y]->getState() <= 1) (board)[x][y]->setState(-1);
                }
            }
        }
    }
    placeRandomMines(board, num);
}

int Board::getNumMinesPoint(vector<vector<std::unique_ptr<Tile>>>& board, int& x, int& y) const {
    int num = 0;
    if (x > 0 && y > 0 && (board)[x-1][y-1]->getState() > 0) num++;
    if (x > 0 && (board)[x-1][y]->getState() > 0) num++;
    if (y < boardHeight - 1 && x > 0 && (board)[x-1][y+1]->getState() > 0) num++;
    if (y > 0 && (board)[x][y-1]->getState() > 0) num++;
    if (y < boardHeight - 1 && (board)[x][y+1]->getState() > 0) num++;
    if (y > 0 && x < boardWidth - 1 && (board)[x+1][y-1]->getState() > 0) num++;
    if (x < boardWidth - 1 && (board)[x+1][y]->getState() > 0) num++;
    if (y < boardHeight - 1 && x < boardWidth - 1 && (board)[x+1][y+1]->getState() > 0) num++;
    return num;
}

void Board::openBoardPosition(vector<vector<int>> &points, vector<vector<std::unique_ptr<Tile>>> &board, vector<vector<std::unique_ptr<Tile>>> &dispBoard, int x, int y) {
    if ((board)[x][y]->getState() < 0) (dispBoard)[x][y]->setState(-1);
    else if ((board)[x][y]->getState() == 1) (dispBoard)[x][y]->setState(1);
    else if ((board)[x][y]->getState() == 2) (dispBoard)[x][y]->setState(2);
    points.push_back(vector<int>{x, y});
    if (getNumMinesPoint(board, x, y) != 0) {
        if (x > 0 && y > 0 && (board)[x-1][y-1]->getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y-1);
        if (x > 0 && (dispBoard)[x-1][y]->getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y);
        if (x > 0 && y < boardHeight - 1 && (dispBoard)[x-1][y+1]->getState() == 0) openBoardPosition(points, board, dispBoard, x-1, y+1);
        if (y > 0 && (dispBoard)[x][y-1]->getState() == 0) openBoardPosition(points, board, dispBoard, x, y-1);
        if (y < boardHeight - 1 && (dispBoard)[x][y+1]->getState() == 0) openBoardPosition(points, board, dispBoard, x, y+1);
        if (y > 0 && x < boardWidth - 1 && (dispBoard)[x+1][y-1]->getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y-1);
        if (x < boardWidth - 1 && (dispBoard)[x+1][y]->getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y);
        if (y < boardHeight - 1 && x < boardWidth - 1 && (dispBoard)[x+1][y+1]->getState() == 0) openBoardPosition(points, board, dispBoard, x+1, y+1);
    }
}

vector<vector<int>> Board::getMinesAtPoint(vector<vector<std::unique_ptr<Tile>>>& board, int x, int y) {
    vector<vector<int>> points;
    if (x > 0 && y > 0 && (board)[x-1][y-1]->getState() > 0) points.push_back(vector<int>{x-1, y-1});
    if (y > 0 && (board)[x][y-1]->getState() > 0) points.push_back(vector<int>{x, y-1});
    if (x < boardWidth - 1 && y > 0 && (board)[x+1][y-1]->getState() > 0) points.push_back(vector<int>{x+1, y-1});
    if (x > 0 && (board)[x-1][y]->getState() > 0) points.push_back(vector<int>{x-1, y});
    if (x < boardWidth - 1 && (board)[x+1][y]->getState() > 0) points.push_back(vector<int>{x+1, y});
    if (x > 0 && y < boardHeight - 1 && (board)[x-1][y+1]->getState() > 0) points.push_back(vector<int>{x-1, y+1});
    if (y < boardHeight - 1 && (board)[x][y+1]->getState() > 0) points.push_back(vector<int>{x, y+1});
    if (x < boardWidth - 1 && y < boardHeight - 1 && (board)[x+1][y+1]->getState() > 0) points.push_back(vector<int>{x+1, y+1});
    return points;
}

vector<vector<int>> Board::getAvailablePoints(vector<vector<std::unique_ptr<Tile>>>& board, int x, int y) {
    vector<vector<int>> points;
    if (x > 0 && y > 0 && (board)[x-1][y-1]->getState() == 0) points.push_back(vector<int>{x-1, y-1});
    if (y > 0 && (board)[x][y-1]->getState() == 0) points.push_back(vector<int>{x, y-1});
    if (x < boardWidth - 1 && y > 0 && (board)[x+1][y-1]->getState() == 0) points.push_back(vector<int>{x+1, y-1});
    if (x > 0 && (board)[x-1][y]->getState() == 0) points.push_back(vector<int>{x-1, y});
    if (x < boardWidth - 1 && (board)[x+1][y]->getState() == 0) points.push_back(vector<int>{x+1, y});
    if (x > 0 && y < boardHeight - 1 && (board)[x-1][y+1]->getState() == 0) points.push_back(vector<int>{x-1, y+1});
    if (y < boardHeight - 1 && (board)[x][y+1]->getState() == 0) points.push_back(vector<int>{x, y+1});
    if (x < boardWidth - 1 && y < boardHeight - 1 && (board)[x+1][y+1]->getState() == 0) points.push_back(vector<int>{x+1, y+1});
    return points;
}

void Board::generateBoard(int &startx, int &starty) {
    clearPoint(board, startx, starty);
    placeRandomMines(board, boardMines);
    vector<vector<int>> solver;
    vector<vector<std::unique_ptr<Tile>>> solverBoard;
    int minesLeft = getTotalMines(board);
    int spacesLeft = boardWidth * boardHeight;
    openBoardPosition(solver, board, solverBoard, startx, starty);
    for (vector<int> &tile : solver) {
        (board)[tile[0]][tile[1]]->setState(-1);
        (solverBoard)[tile[0]][tile[1]]->setState(-1);
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
                    (solverBoard)[tile2[0]][tile2[1]]->setState(-1);
                    (board)[tile2[0]][tile2[1]]->setState(-1);
                    spacesLeft--;
                    solver.push_back(tile2);
                }
                solver.erase(solver.begin());
                (solverBoard)[tile[0]][tile[1]]->setState(-1);
                (board)[tile[0]][tile[1]]->setState(-1);
                spacesLeft--;
            }
            else if (mines.size() == smines.size() + savail.size()) {
                for (vector<int> &tile2 : savail) {
                    (solverBoard)[tile2[0]][tile2[1]]->setState(1);
                    (board)[tile2[0]][tile2[1]]->setState(2);
                    spacesLeft--;
                }
                solver.erase(solver.begin());
                (solverBoard)[tile[0]][tile[1]]->setState(-1);
                (board)[tile[0]][tile[1]]->setState(-1);
                spacesLeft--;
            }
            else if (mines.size() - smines.size() == 2 && savail.size() == 3) {
                bool found = false;
                if (tile[1] > 0 && tile[1] < boardHeight - 1 && (board)[tile[0]][tile[1] - 1]->getState() <= 0 && (board)[tile[0]][tile[1] + 1]->getState() <= 0) {
                    auto mines2 = getMinesAtPoint(board, tile[0], tile[1] - 1);
                    auto smines2 = getMinesAtPoint(solverBoard, tile[0], tile[1] - 1);
                    auto mines3 = getMinesAtPoint(board, tile[0], tile[1] + 1);
                    auto smines3 = getMinesAtPoint(solverBoard, tile[0], tile[1] + 1);
                    if (mines2.size() - smines2.size() == 1 && mines3.size() - smines3.size() == 1) {
                        for (vector<int> &tile2 : savail) {
                            if (tile2[1] == tile[1]) {
                                (solverBoard)[tile2[0]][tile2[1]]->setState(-1);
                                (board)[tile2[0]][tile2[1]]->setState(-1);
                                solver.push_back(tile2);
                            }
                            else {
                                (solverBoard)[tile2[0]][tile2[1]]->setState(1);
                                (board)[tile2[0]][tile2[1]]->setState(2);
                            }
                            spacesLeft--;
                        }
                        solver.erase(solver.begin());
                        (solverBoard)[tile[0]][tile[1]]->setState(-1);
                        (board)[tile[0]][tile[1]]->setState(-1);
                        spacesLeft--;
                        found = true;
                    }
                }
                if (!found && tile[0] > 0 && tile[0] < boardWidth - 1 && (board)[tile[0] - 1][tile[1]]->getState() <= 0 && (board)[tile[0] + 1][tile[1]]->getState() <= 0) {
                    auto mines2 = getMinesAtPoint(board, tile[0] - 1, tile[1]);
                    auto smines2 = getMinesAtPoint(solverBoard, tile[0] - 1, tile[1]);
                    auto mines3 = getMinesAtPoint(board, tile[0] + 1, tile[1]);
                    auto smines3 = getMinesAtPoint(solverBoard, tile[0] + 1, tile[1]);
                    if (mines2.size() - smines2.size() == 1 && mines3.size() - smines3.size() == 1)
                    {
                        for (vector<int> &tile2 : savail) {
                            if (tile2[0] == tile[0]) {
                                (solverBoard)[tile2[0]][tile2[1]]->setState(-1);
                                (board)[tile2[0]][tile2[1]]->setState(-1);
                                solver.push_back(tile2);
                            }
                            else {
                                (solverBoard)[tile2[0]][tile2[1]]->setState(1);
                                (board)[tile2[0]][tile2[1]]->setState(2);
                            }
                            spacesLeft--;
                        }
                        solver.erase(solver.begin());
                        (solverBoard)[tile[0]][tile[1]]->setState(-1);
                        (board)[tile[0]][tile[1]]->setState(-1);
                        spacesLeft--;
                    }
                }
            }
            else if (mines.size() - smines.size() == 1 && savail.size() == 3) {
                if (savail[0][0] == savail [1][0] && savail[0][0] == savail [2][0]) {
                    if (tile[1] > 0 && (board)[tile[0]][tile[1] - 1]->getState() <= 0)
                    {
                        auto mines2 = getMinesAtPoint(board, tile[0], tile[1] - 1);
                        auto smines2 = getMinesAtPoint(solverBoard, tile[0], tile[1] - 1);
                        auto savail2 = getAvailablePoints(solverBoard, tile[0], tile[1] - 1);
                        if (mines2.size() - smines2.size() == 1 && savail2.size() == 2) {
                            int x = savail2[0][0];
                            int y = std::max({savail[0][1], savail[1][1], savail[2][1]});
                            (solverBoard)[x][y]->setState(-1);
                            (board)[x][y]->setState(-1);
                            solver.push_back(vector<int>{x, y});
                        }
                    }
                    if (tile[1] < boardHeight - 1 && (board)[tile[0]][tile[1] + 1]->getState() <= 0) {
                        auto mines2 = getMinesAtPoint(board, tile[0], tile[1] + 1);
                        auto smines2 = getMinesAtPoint(solverBoard, tile[0], tile[1] + 1);
                        auto savail2 = getAvailablePoints(solverBoard, tile[0], tile[1] + 1);
                        if (mines2.size() - smines2.size() == 1 && savail2.size() == 2) {
                            int x = savail2[0][0];
                            int y = std::min({savail[0][1], savail[1][1], savail[2][1]});
                            (solverBoard)[x][y]->setState(-1);
                            (board)[x][y]->setState(-1);
                            solver.push_back(vector<int>{x, y});
                        }
                    }
                }
                else if (savail[0][1] == savail[1][1] && savail[0][1] == savail[2][1]) {
                    if (tile[0] > 0 && (board)[tile[0] - 1][tile[0]]->getState() <= 0) {
                        auto mines2 = getMinesAtPoint(board, tile[0] - 1, tile[0]);
                        auto smines2 = getMinesAtPoint(solverBoard, tile[0] - 1, tile[0]);
                        auto savail2 = getAvailablePoints(solverBoard, tile[0] - 1, tile[0]);
                        if (mines2.size() - smines2.size() == 1 && savail2.size() == 2) {
                            int x = std::max({savail[0][0], savail[1][0], savail[2][0]});
                            int y = savail[0][1];
                            (solverBoard)[x][y]->setState(-1);
                            (board)[x][y]->setState(-1);
                            solver.push_back(vector<int>{x, y});
                        }
                    }
                    if (tile[0] < boardWidth - 1 && (board)[tile[0] + 1][tile[1]]->getState() <= 0) {
                        auto mines2 = getMinesAtPoint(board, tile[0] + 1, tile[1]);
                        auto smines2 = getMinesAtPoint(solverBoard, tile[0] + 1, tile[1]);
                        auto savail2 = getAvailablePoints(solverBoard, tile[0] + 1, tile[1]);
                        if (mines2.size() - smines2.size() == 1 && savail2.size() == 2) {
                            int x = std::max({savail[0][0], savail[1][0], savail[2][0]});
                            int y = savail[0][1];
                            (solverBoard)[x][y]->setState(-1);
                            (board)[x][y]->setState(-1);
                            solver.push_back(vector<int>{x, y});
                        }
                    }
                }
            }
            else if (mines.size() - smines.size() == 1 && savail.size() == 2) {
                vector<int> tile2;
                if (savail[0][1] == savail[1][1] && (tile[0] == savail[0][0] || tile[0] == savail[1][0])) {
                    if (tile[0] - 1 == savail[0][0] || tile[0] - 1 == savail[1][0]) tile2 = vector<int>{tile[0] - 1, tile[1]};
                    if (tile[0] + 1 == savail[0][0] || tile[0] + 1 == savail[1][0]) tile2 = vector<int>{tile[0] + 1, tile[1]};
                }
                else if (savail[0][0] == savail[1][0] && (tile[1] == savail[0][1] || tile[1] == savail[1][1])) {
                    if (tile[1] - 1 == savail[0][1] || tile[1] - 1 == savail[1][1]) tile2 = vector<int>{tile[0], tile[1] - 1};
                    if (tile[1] + 1 == savail[0][1] || tile[1] + 1 == savail[1][1]) tile2 = vector<int>{tile[0], tile[1] - 1};
                }
                if (tile2.size() > 0) {
                    auto mines2 = getMinesAtPoint(board, tile2[0], tile2[1]);
                    auto smines2 = getMinesAtPoint(solverBoard, tile2[0], tile2[1]);
                    auto savail2 = getAvailablePoints(solverBoard, tile2[0], tile2[1]);
                    if (mines2.size() - smines2.size() == 1) {
                        for (vector<int> tile2 : savail2) {
                            if (tile2[0] == savail[0][0] && tile2[1] == savail[0][1] || (tile2[0] == savail[1][0] && tile2[1] == savail[1][1])) continue;
                            (solverBoard)[tile2[0]][tile2[1]]->setState(-1);
                            (board)[tile2[0]][tile2[1]]->setState(-1);
                            solver.push_back(tile2);
                        }
                    }
                }
            }
        }
        if (spacesLeft2 == spacesLeft && solver.size() == numPoints) {
            int minnum = -1;
            int total = 0;
            int spaces = 0;
            for (int i = 0; i < solver.size(); i++) {
                auto mines2 = getMinesAtPoint(board, solver[i][0], solver[i][1]);
                auto smines2 = getMinesAtPoint(solverBoard, solver[i][0], solver[i][1]);
                auto savail2 = getAvailablePoints(solverBoard, solver[i][0], solver[i][1]);
                if (minnum == -1 || total > mines2.size() - smines2.size() || (total == mines2.size() - smines2.size() && spaces > savail2.size())) {
                    minnum = i;
                    total = mines2.size() - smines2.size();
                    spaces = savail2.size();
                }
            }
            if (minnum > -1) clearPoint(board, solver[minnum][0], solver[minnum][1]);
            else break;
        }
    }
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; y++)
        {
            if ((board)[x][y]->getState() == 0)
            {
                (board)[x][y]->setState(1);
                minesLeft++;
            }
            else if ((board)[x][y]->getState() == -1)
            {
                int maxmines = 0;
                if (x > 0 && y > 0) maxmines++;
                if (y > 0) maxmines++;
                if (x < boardWidth - 1 && y > 0) maxmines++;
                if (x > 0) maxmines++;
                if (x < boardWidth - 1) maxmines++;
                if (x > 0 && y < boardHeight - 1) maxmines++;
                if (y < boardHeight - 1) maxmines++;
                if (x < boardWidth - 1 && y < boardHeight - 1) maxmines++;
                auto mines = getMinesAtPoint(board, x, y);
                if (mines.size() == maxmines) {
                    (board)[x][y]->setState(1);
                    minesLeft++;
                }
            }
        }
    }
}

void Board::tileLeftClick(const vec2 &point) {
    //tile uncovered if a tile in board is left-clicked.
    for (int x = 0; x < boardWidth; x++) {
        for (int y = 0; y < boardHeight; y++) {
            if (point.x < board[x][y]->getRight() &&
                point.x > board[x][y]->getLeft() &&
                point.y < board[x][y]->getTop() &&
                point.y > board[x][y]->getBottom()) uncoverTile(x, y);
        }
    }
}

bool Board::tileClicked(const vec2 &point) {
    bool clicked = false;
    for (int x = 0; x < boardWidth; x++) {
        for (int y = 0; y < boardHeight; y++) {
            if (point.x < board[x][y]->getRight() &&
                point.x > board[x][y]->getLeft() &&
                point.y < board[x][y]->getTop() &&
                point.y > board[x][y]->getBottom()) clicked = true;
        }
    }
    return clicked;
}

void Board::uncoverTile(int x, int y) {
    board[x][y]->setClicked(true);
    if (board[x][y]->getSurrBombs() == 0) {
        if (x > 0 && y > 0 && (board)[x-1][y-1]->getSurrBombs() == 0) uncoverTile(x-1, y-1);
        if (x > 0 && (board)[x-1][y]->getSurrBombs() == 0) uncoverTile(x-1, y);
        if (x > 0 && y < boardHeight - 1 && (board)[x-1][y+1]->getSurrBombs() == 0) uncoverTile(x-1, y+1);
        if (y > 0 && (board)[x][y-1]->getSurrBombs() == 0) uncoverTile(x, y-1);
        if (y < boardHeight - 1 && (board)[x][y+1]->getSurrBombs() == 0) uncoverTile(x, y+1);
        if (y > 0 && x < boardWidth - 1 && (board)[x+1][y-1]->getSurrBombs() == 0) uncoverTile(x+1, y-1);
        if (x < boardWidth - 1 && (board)[x+1][y]->getSurrBombs() == 0) uncoverTile(x+1, y);
        if (y < boardHeight - 1 && x < boardWidth - 1 && (board)[x+1][y+1]->getSurrBombs() == 0) uncoverTile(x+1, y+1);
    }
}

vector<vector<int>> Board::showVals() {
    vector<vector<int>> vals;
    for (int x = 0; x < boardWidth; x++) {
        for (int y = 0; y < boardHeight; y++) {
            if (board[x][y]->getSurrBombs() > 0 && board[x][y]->getClicked()) vals.push_back(vector<int>{x, y});
        }
    }
    return vals;
}

void Board::setSurroundingBombs() {
   for (int x = 0; x < boardWidth; x++) {
       for (int y = 0; y < boardHeight; y++) {
           int numMines = getNumMinesPoint(board, x, y);
           (board)[x][y]->setSurrBombs(numMines);
       }
   }
}
