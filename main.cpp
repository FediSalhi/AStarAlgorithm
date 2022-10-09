/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : constains the main function used to test A* algorithm
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#include "AStarSearch.hpp"
#include <iostream>

int main() {

  std::vector<std::vector<CellStates>> grid = {
      {CellStates::CELL_START_POINT, CellStates::CELL_STATE_OPEN,
       CellStates::CELL_STATE_OPEN},
      {CellStates::CELL_STATE_OPEN, CellStates::CELL_STATE_OBSTACLE,
       CellStates::CELL_STATE_OPEN},
      {CellStates::CELL_STATE_OPEN, CellStates::CELL_STATE_OBSTACLE,
       CellStates::CELL_END_POINT},
  };

  std::vector<std::vector<std::string>> grid_str = {{"S", "|", ".", "."},
                                                    {".", ".", ".", "."},
                                                    {".", "|", ".", "."},
                                                    {".", ".", ".", "."}};

  auto x = std::vector<int>{0, 0};
  auto y = std::vector<int>{0, 2};

  AStarSearch A(grid_str, x, y);

  A.ShowGrid();
  std::cout << std::endl;
  auto solution = A.Search();
  A.ShowGrid();

  /*   std::vector<std::vector<std::string>> out = A.FormatGridOutput(grid);
    for (auto item : out) {
      for (auto s : item) {
        std::cout << s;
      }
      std::cout << std::endl;
    }

    auto in = A.FormatGridInput(out);
    int debug = 0; */
  return 0;
}