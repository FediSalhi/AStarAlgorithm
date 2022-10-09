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
  void SetG(int g);
  void SetH(int h);
  void SetF(int f);
  int GetF() const;
  int GetG() const;
  int GetH() const;
  std::vector<int> GetCoordinates();
  void UpdateCoordinates(std::vector<int> coordiantes);
  int ComputeH(std::vector<int> goal_coordinates);
  bool operator<(const Node &other) const;
  bool operator!=(const Node &other) const;
  Node operator-(const Node &other);

private:
  std::vector<int> _coordinates;
  int _g = 0;
  int _h = 0;
  int _f = 0;
};

#endif