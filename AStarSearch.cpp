/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : constains the A* algorithm main class
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#include "AStarSearch.hpp"

AStarSearch::AStarSearch(std::vector<std::vector<std::string>> &grid,
                         std::vector<int> &start_p, std::vector<int> &end_p) {

  _grid = new std::vector<std::vector<CellStates>>(FormatGridInput(grid));
  _startPoint = new std::vector<int>(start_p);
  _goalPoint = new std::vector<int>(end_p);
  _currentNode = new Node(start_p);
  _currentNode->UpdateH(_currentNode->ComputeH(*_goalPoint));
  _currentNode->UpdateF(_currentNode->GetH() + _currentNode->GetG());
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
    node.UpdateH(node.ComputeH(*_goalPoint));
    node.UpdateG(_g);
    node.UpdateF(node.GetG() + node.GetH());
    _openList->push_back(node);
  }
}

bool AStarSearch::Compare(const Node &node1, const Node &node2) {
  if (node1 < node1) {
    return true;
  } else {
    return false;
  }
}

void AStarSearch::PopItemOpenList() {

  //_openList->pop_back();
  _openList->clear();
}

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
    auto candidate_cell =
        std::vector<int>{item[0] + (_currentNode->GetCoordinates()[0]),
                         item[1] + (_currentNode->GetCoordinates()[1])};
    if (CellMovePossibiltyStates::CELL_POSSIBLE_TO_MOVE ==
        CheckCellState(candidate_cell)) {
      AddItemOpenList(candidate_cell);
      UpdateGrid(candidate_cell, CellStates::CELL_STATE_CLOSE);
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
    PopItemOpenList();
    _g++;
    ExpandOpenList();
  }
  std::cout << "No Possibe Path !" << std::endl;

  return std::vector<std::vector<CellStates>>{};
}

std::vector<std::vector<std::string>>
AStarSearch::FormatGridOutput(std::vector<std::vector<CellStates>> &inputGrid) {
  std::vector<std::vector<std::string>> formatted_grid{};
  for (auto row : inputGrid) {
    std::vector<std::string> formatted_line{};
    for (auto item : row) {
      switch (item) {
      case CellStates::CELL_END_POINT: {
        formatted_line.push_back(goal_str);
        break;
      }
      case CellStates::CELL_START_POINT: {
        formatted_line.push_back(start_str);
        break;
      }
      case CellStates::CELL_STATE_CLOSE: {
        formatted_line.push_back(close_str);
        break;
      }
      case CellStates::CELL_STATE_OBSTACLE: {
        formatted_line.push_back(obstacle_str);
        break;
      }
      case CellStates::CELL_STATE_OPEN: {
        formatted_line.push_back(open_str);
        break;
      }
      case CellStates::CELL_STATE_PATH: {
        formatted_line.push_back(path_str);
        break;
      }
      }
    }
    formatted_grid.push_back(formatted_line);
  }
  return formatted_grid;
}

std::vector<std::vector<CellStates>>
AStarSearch::FormatGridInput(std::vector<std::vector<std::string>> &inputGrid) {

  std::vector<std::vector<CellStates>> formatted_grid{};

  for (auto row : inputGrid) {
    std::vector<CellStates> formatted_line{};
    for (auto item : row) {
      if (item == goal_str) {
        formatted_line.push_back(CellStates::CELL_END_POINT);
      } else if (item == start_str) {
        formatted_line.push_back(CellStates::CELL_START_POINT);
      } else if (item == open_str) {
        formatted_line.push_back(CellStates::CELL_STATE_OPEN);
      } else if (item == obstacle_str) {
        formatted_line.push_back(CellStates::CELL_STATE_OBSTACLE);
      } else if (item == close_str) {
        formatted_line.push_back(CellStates::CELL_STATE_CLOSE);
      } else if (item == path_str) {
        formatted_line.push_back(CellStates::CELL_STATE_PATH);
      }
    }
    formatted_grid.push_back(formatted_line);
  }
  return formatted_grid;
}

bool AStarSearch::GoalIsAttained() {
  if (_currentNode->GetCoordinates() == *_goalPoint) {
    return true;
  } else {
    return false;
  }
}

void AStarSearch::ShowGrid() {
  auto formatted_grid = FormatGridOutput(*_grid);
  for (auto row : formatted_grid) {
    for (auto item : row) {
      std::cout << item;
    }
    std::cout << std::endl;
  }
}