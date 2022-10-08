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

AStarSearch::AStarSearch(std::vector<std::vector<CellStates>> &grid,
                         std::vector<int> &start_p, std::vector<int> &end_p) {

  _grid = new std::vector<std::vector<CellStates>>(grid);
  _startPoint = new std::vector<int>(start_p);
  _goalPoint = new std::vector<int>(end_p);
  _currentNode = new Node(start_p);
  _currentNode->UpdateH(_currentNode->ComputeH(*_goalPoint));
  _openList = new std::vector<Node>{*_currentNode};
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

void AStarSearch::UpdateGrid(std::vector<int> &coordinates,
                             CellStates newState) {
  if (!coordinates.empty()) {
    (*_grid)[coordinates[0]][coordinates[1]] = newState;
  }
}

void AStarSearch::AddItemOpenList(std::vector<int> &coordinates) {
  if (!coordinates.empty()) {
    _openList->push_back(Node(coordinates));
  }
}

bool AStarSearch::Compare(const Node &node1, const Node &node2) {
  if (node1 < node1) {
    return true;
  } else {
    return false;
  }
}

void AStarSearch::PopItemOpenList() { _openList->pop_back(); }

void AStarSearch::SortOpenList() {

  std::sort(*_openList->begin(), *_openList->end(),
            [](const Node &node1, const Node &node2) {
              if (node1 < node2) {
                return true;
              } else {
                return false;
              }
            });
}

void AStarSearch::UpdateCurrentNode(const std::vector<Node> *sortedList) {
  *_currentNode = (*sortedList)[0];
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
  for (auto item : movements) {
    auto candidate_cell =
        std::vector<int>{item[0] + (_currentNode->GetCoordinates()[0]),
                         item[1] + (_currentNode->GetCoordinates()[1])};
    if (CellMovePossibiltyStates::CELL_POSSIBLE_TO_MOVE ==
        CheckCellState(candidate_cell)) {
      AddItemOpenList(candidate_cell);
    }
  }
}

std::vector<std::vector<CellStates>> AStarSearch::Search() {
  // TODO
  return std::vector<std::vector<CellStates>>{};
}

std::vector<std::vector<std::string>>
AStarSearch::FormatGridOutput(std::vector<std::vector<CellStates>> &inputGrid) {
  // TODO
  return std::vector<std::vector<std::string>>{};
}

std::vector<std::vector<CellStates>> AStarSearch::FormatGridOutput(
    std::vector<std::vector<std::string>> &outputGrid) {
  // TODO
  return std::vector<std::vector<CellStates>>{};
}