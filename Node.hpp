/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : Node class header file
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#include <cmath>
#include <vector>

class Node {
public:
  Node(std::vector<int> &coordinates);
  void UpdateG(int g);
  void UpdateH(int h);
  void UpdateF(int f);
  std::vector<int> GetCoordinates();
  void UpdateCoordinates(std::vector<int> coordiantes);
  int ComputeH(std::vector<int> goal_coordinates);
  bool operator<(const Node &other) const;

private:
  std::vector<int> _coordinates;
  int _g = 0;
  int _h = 0;
  int _f = 0;
};

#endif