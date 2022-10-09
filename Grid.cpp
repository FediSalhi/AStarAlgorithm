/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : This class reads and process the grid
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#include "Grid.hpp"

std::vector<std::vector<std::string>> Grid::ReadGrid() {

  std::ifstream gridFileStream(_filePath);
  std::vector<std::vector<std::string>> grid{};
  std::string line;
  std::vector<std::string> line_v{};

  if (gridFileStream) {
    while (getline(gridFileStream, line)) {
      for (auto c : line) {
        line_v.push_back(std::string{c});
      }
      grid.push_back(line_v);
      line_v.clear();
    }
  } else {
    std::cout << "Grid file could not be read !" << std::endl;
  }
  _grid = grid;
  return grid;
}

bool Grid::CheckChar(const char &c) {
  if (std::find(_allowedCharList.begin(), _allowedCharList.end(), c) ==
      _allowedCharList.end()) {
    return false;
  } else {
    return true;
  }
}

bool Grid::CheckGrid() {
  bool gridCharIsValid = true;
  bool gridStartPointIsValid = false;
  bool gridGoalPointIsValid = false;
  int numberStartPoints = 0;
  int numberGoalPoints = 0;

  // check every char in the grid is ok
  for (auto row : _grid) {
    for (auto item : row) {
      if (!CheckChar(item[0])) {
        gridCharIsValid = false;
      }
    }
  }

  // check there is exactly one start point
  for (int i = 0; i < _grid.size(); i++) {
    for (int j = 0; j < _grid[0].size(); j++) {
      if (_grid[i][j] == "S") {
        numberStartPoints++;
        _startPoint = {i, j};
      }
    }
  }
  if (numberStartPoints != 1) {
    std::cout << "The grid is not valid! Please check the Start point"
              << std::endl;
    exit(-1);
  } else {
    gridStartPointIsValid = true;
  }

  // check there is exactly one goal point
  for (int i = 0; i < _grid.size(); i++) {
    for (int j = 0; j < _grid[0].size(); j++) {
      if (_grid[i][j] == "G") {
        numberGoalPoints++;
        _goalPoint = {i, j};
      }
    }
  }
  if (numberGoalPoints != 1) {
    std::cout << "The grid is not valid! Please check the Goal point"
              << std::endl;
    exit(-1);
  } else {
    gridGoalPointIsValid = true;
  }

  return (gridCharIsValid && gridStartPointIsValid && gridGoalPointIsValid);
}

std::vector<int> Grid::GetStartPoint() { return _startPoint; }

std::vector<int> Grid::GetGoalPoint() { return _goalPoint; }