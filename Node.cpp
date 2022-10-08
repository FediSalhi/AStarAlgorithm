/************************************************************************************
 * Author               : Fedi Salhi <fadi.salhi@outlook.fr>
 * Creation Date        : 08/10/2022
 * Description          : Node class
 *
 * Revision No          : R000
 * Revision Date        :
 * Revision Description :
 *************************************************************************************/

#include "Node.hpp"

Node::Node(std::vector<int> &coordinates) : _coordinates(coordinates){};

void Node::UpdateG(int g) { _g = g; }

void Node::UpdateH(int h) { _h = h; }

void Node::UpdateF(int f) { _f = f; }

std::vector<int> Node::GetCoordinates() { return _coordinates; }

void Node::UpdateCoordinates(std::vector<int> coordiantes) {
  _coordinates = coordiantes;
};

int Node::ComputeH(std::vector<int> goal_coordinates) {
  // compute Manhatten distance
  std::vector<int> current_coordinates = GetCoordinates();
  return (abs(current_coordinates[0] - goal_coordinates[0]) +
          abs(current_coordinates[1] - goal_coordinates[1]));
}

bool Node::operator<(const Node &other) const {
  if (this->_f < other._f) {
    return true;
  } else {
    return false;
  }
}
