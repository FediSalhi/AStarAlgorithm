/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 09/10/2022
 * Description          : This class reads and process the grid
 *************************************************************************************/

#ifndef GRID_HPP
#define GRID_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Grid {
public:
  Grid(const std::string &filePath) : _filePath(filePath){};

  ~Grid() = default;

  std::vector<std::vector<std::string>> ReadGrid();

  bool CheckChar(const char &c);

  bool CheckGrid();

  std::vector<int> GetStartPoint();

  std::vector<int> GetGoalPoint();

private:
  std::string _filePath;

  std::vector<std::vector<std::string>> _grid;

  const std::vector<char> _allowedCharList = {'.', '|', 'G', 'S'};

  std::vector<int> _startPoint;

  std::vector<int> _goalPoint;
};

#endif