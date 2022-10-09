/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : contains the main function used to test A* algorithm
 *************************************************************************************/

#include "AStarSearch.hpp"
#include "Grid.hpp"
#include <iostream>

int main() {

  Grid grid("/home/fedi/Desktop/Projects/A_Star_CPP/grid1.txt");
  // Grid grid("/home/fedi/Desktop/Projects/A_Star_CPP/grid2.txt");
  // Grid grid("/home/fedi/Desktop/Projects/A_Star_CPP/grid3.txt");

  auto grid_str = grid.ReadGrid();

  if (grid.CheckGrid()) {
    auto startPoint = grid.GetStartPoint();
    auto goalPoint = grid.GetGoalPoint();
    AStarSearch A(grid_str, startPoint, goalPoint);
    std::cout << "=========== Input Grid ===========" << std::endl << std::endl;
    A.ShowGrid();
    std::cout << std::endl
              << std::endl
              << "=========== Solution ===========" << std::endl
              << std::endl;
    A.Search();
    A.ShowGrid();
  }
  return 0;
}