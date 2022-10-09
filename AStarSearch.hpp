/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : Header file A* algorithm main class
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#ifndef A_STAR_SEARCH_HPP
#define A_STAR_SEARCH_HPP

#include "Node.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

enum class CellStates {
  CELL_STATE_OPEN,
  CELL_STATE_CLOSE,
  CELL_STATE_OBSTACLE,
  CELL_STATE_PATH,
  CELL_START_POINT,
  CELL_END_POINT,
};

enum class OnGridStates {
  CELL_ON_GRID,
  CELL_OFF_GRID,
};

enum class CellMovePossibiltyStates {
  CELL_POSSIBLE_TO_MOVE,
  CELL_IMPOSSIBLE_TO_MOVE,
};

class AStarSearch {
public:
  AStarSearch(std::vector<std::vector<std::string>> &grid,
              std::vector<int> &start_p, std::vector<int> &end_p);

  ~AStarSearch();

  void UpdateGrid(const std::vector<int> &coordinates, CellStates newState);

  void AddItemOpenList(std::vector<int> &coordinates);

  void PopItemOpenList();

  void SortOpenList();

  bool Compare(const Node &node1, const Node &node2);

  void UpdateCurrentNode(const std::vector<Node> *sortedList);

  Node *GetCurrentNode();

  OnGridStates CheckCellOnGrid(const std::vector<int> &coordinates);

  CellMovePossibiltyStates CheckCellState(std::vector<int> &coordinates);

  void ExpandOpenList();

  std::vector<std::vector<CellStates>> Search();

  std::vector<std::vector<std::string>>
  FormatGridOutput(std::vector<std::vector<CellStates>> &inputGrid);

  std::vector<std::vector<CellStates>>
  FormatGridInput(std::vector<std::vector<std::string>> &outputGrid);

  void ShowGrid();

  bool GoalIsAttained();

private:
  std::vector<std::vector<CellStates>> *_grid;

  std::vector<int> *_startPoint;

  std::vector<int> *_goalPoint;

  Node *_currentNode;

  std::vector<Node> *_openList;

  const std::vector<std::vector<int>> movements = {
      {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

  std::string open_str = ".";
  std::string obstacle_str = "|";
  std::string path_str = "*";
  std::string close_str = ".";
  std::string start_str = "S";
  std::string goal_str = "G";

  int _g;
};

#endif