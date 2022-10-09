/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : constains the main A* algorithm
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#include "AStarSearch.hpp"

AStarSearch::AStarSearch(std::vector<std::vector<std::string>> &grid,
                         std::vector<int> &startPoint,
                         std::vector<int> &goalPoint) {

  // the goal point is also an open point, so let's format the grid
  grid[goalPoint[0]][goalPoint[1]] = ".";
  _grid = new std::vector<std::vector<CellStates>>(FormatGridInput(grid));
  _startPoint = new std::vector<int>(startPoint);
  _goalPoint = new std::vector<int>(goalPoint);
  _currentNode = new Node(startPoint);
  _currentNode->SetH(_currentNode->ComputeH(*_goalPoint));
  _currentNode->SetF(_currentNode->GetH() + _currentNode->GetG());
  _openList = new std::vector<Node>{*_currentNode};
  _g = 0;
}

AStarSearch::~AStarSearch() {
  if (_grid != nullptr) {
    delete[] _grid;
  };
  if (_startPoint != nullptr) {
    delete[] _startPoint;
  };
  if (_goalPoint != nullptr) {
    delete[] _goalPoint;
  };
  if (_currentNode != nullptr) {
    delete _currentNode;
  };
  if (_openList != nullptr) {
    delete[] _openList;
  };
}

void AStarSearch::UpdateGrid(const std::vector<int> &coordinates,
                             CellStates newState) {
  if (!coordinates.empty()) {
    (*_grid)[coordinates[0]][coordinates[1]] = newState;
  }
}

void AStarSearch::AddItemOpenList(std::vector<int> &coordinates) {
  if (!coordinates.empty()) {
    Node node(coordinates);
    node.SetH(node.ComputeH(*_goalPoint));
    node.SetG(_g);
    node.SetF(node.GetG() + node.GetH());
    _openList->push_back(node);
  }
}

void AStarSearch::ClearOpenList() { _openList->clear(); }

void AStarSearch::SortOpenList() {
  std::sort(_openList->begin(), _openList->end(),
            [](const Node &node1, const Node &node2) {
              return node1.GetF() < node2.GetF();
            });
}

void AStarSearch::UpdateCurrentNode(const std::vector<Node> *sortedList) {
  *_currentNode = (*sortedList)[0];
  UpdateGrid(_currentNode->GetCoordinates(), CellStates::CELL_STATE_PATH);
}

Node *AStarSearch::GetCurrentNode() { return this->_currentNode; }

OnGridStates AStarSearch::CheckCellOnGrid(const std::vector<int> &coordinates) {
  if (((coordinates[0] >= 0) && (coordinates[0] < (*_grid)[0].size())) &&
      ((coordinates[1] >= 0) && (coordinates[1] < (*_grid)[1].size()))) {
    return OnGridStates::CELL_ON_GRID;
  } else {
    return OnGridStates::CELL_OFF_GRID;
  }
}

CellMovePossibiltyStates
AStarSearch::CheckCellState(std::vector<int> &coordinates) {
  if ((CheckCellOnGrid(coordinates) == OnGridStates::CELL_ON_GRID) &&
      ((*_grid)[coordinates[0]][coordinates[1]] ==
       CellStates::CELL_STATE_OPEN)) {
    return CellMovePossibiltyStates::CELL_POSSIBLE_TO_MOVE;
  } else {
    return CellMovePossibiltyStates::CELL_IMPOSSIBLE_TO_MOVE;
  }
}

void AStarSearch::ExpandOpenList() {
  _openList->clear();
  for (auto item : movements) {
    auto candidateCell =
        std::vector<int>{item[0] + (_currentNode->GetCoordinates()[0]),
                         item[1] + (_currentNode->GetCoordinates()[1])};
    if (CellMovePossibiltyStates::CELL_POSSIBLE_TO_MOVE ==
        CheckCellState(candidateCell)) {
      AddItemOpenList(candidateCell);
      UpdateGrid(candidateCell, CellStates::CELL_STATE_CLOSE);
    }
  }
}

std::vector<std::vector<CellStates>> AStarSearch::Search() {
  while (!_openList->empty()) {
    SortOpenList();
    UpdateCurrentNode(_openList);
    if (GoalIsAttained()) {
      return *_grid;
    }
    ClearOpenList();
    IncrementG();
    ExpandOpenList();
  }
  std::cout << "No Possible Path !" << std::endl;
  // exit(-1);

  return std::vector<std::vector<CellStates>>{};
}

std::vector<std::vector<std::string>>
AStarSearch::FormatGridOutput(std::vector<std::vector<CellStates>> &inputGrid) {
  std::vector<std::vector<std::string>> formattedGrid{};
  for (auto row : inputGrid) {
    std::vector<std::string> formattedLine{};
    for (auto item : row) {
      switch (item) {
      case CellStates::CELL_END_POINT: {
        formattedLine.push_back(_goalStr);
        break;
      }
      case CellStates::CELL_START_POINT: {
        formattedLine.push_back(_startStr);
        break;
      }
      case CellStates::CELL_STATE_CLOSE: {
        formattedLine.push_back(_closeStr);
        break;
      }
      case CellStates::CELL_STATE_OBSTACLE: {
        formattedLine.push_back(_obstacleStr);
        break;
      }
      case CellStates::CELL_STATE_OPEN: {
        formattedLine.push_back(_openStr);
        break;
      }
      case CellStates::CELL_STATE_PATH: {
        formattedLine.push_back(_pathStr);
        break;
      }
      }
    }
    formattedGrid.push_back(formattedLine);
  }
  return formattedGrid;
}

std::vector<std::vector<CellStates>>
AStarSearch::FormatGridInput(std::vector<std::vector<std::string>> &inputGrid) {

  std::vector<std::vector<CellStates>> formattedGrid{};

  for (auto row : inputGrid) {
    std::vector<CellStates> formattedLine{};
    for (auto item : row) {
      if (item == _goalStr) {
        formattedLine.push_back(CellStates::CELL_END_POINT);
      } else if (item == _startStr) {
        formattedLine.push_back(CellStates::CELL_START_POINT);
      } else if (item == _openStr) {
        formattedLine.push_back(CellStates::CELL_STATE_OPEN);
      } else if (item == _obstacleStr) {
        formattedLine.push_back(CellStates::CELL_STATE_OBSTACLE);
      } else if (item == _closeStr) {
        formattedLine.push_back(CellStates::CELL_STATE_CLOSE);
      } else if (item == _pathStr) {
        formattedLine.push_back(CellStates::CELL_STATE_PATH);
      }
    }
    formattedGrid.push_back(formattedLine);
  }
  return formattedGrid;
}

bool AStarSearch::GoalIsAttained() {
  if (_currentNode->GetCoordinates() == *_goalPoint) {
    return true;
  } else {
    return false;
  }
}

void AStarSearch::ShowGrid() {
  auto formattedGrid = FormatGridOutput(*this->_grid);
  formattedGrid[(*_startPoint)[0]][(*_startPoint)[1]] = "S";
  formattedGrid[(*_goalPoint)[0]][(*_goalPoint)[1]] = "G";

  for (auto row : formattedGrid) {
    for (auto item : row) {
      std::cout << item;
    }
    std::cout << std::endl;
  }
}

void AStarSearch::IncrementG() { _g++; };