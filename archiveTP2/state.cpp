/*
 Implementation of class State for the bloc world problem
 Copyright (C) 2023 Christine Solnon
 Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
 modifier au titre des clauses de la Licence Publique Générale GNU, telle que
 publiée par la Free Software Foundation. Ce programme est distribué dans
 l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE ; sans même une garantie
 implicite de COMMERCIABILITE ou DE CONFORMITE A UNE UTILISATION PARTICULIERE.
 Voir la Licence Publique Générale GNU pour plus de détails.
 */

#include "state.h"
#include <iostream>

State::State(int nbStacks, int nbBlocs) {
  // Return the state where nbBlocs blocs are evenly distributed on nbStacks
  // stacks
  stack = vector<string>(nbStacks, "");
  for (int j = 0; j < nbBlocs; j++)
    stack[j % nbStacks] += 'a' + j;
}

State::State(const State &s, int j, int k) {
  // Precondition: 0<=j<stack.size(), 0<=k<stack.size(), and stack[i].length()>0
  // Constructor that creates the state obtained from s by moving the bloc
  // on the top of stack j to the top of stack k
  int nbStacks = s.stack.size();
  stack = vector<string>(nbStacks);
  for (int i = 0; i < nbStacks; i++) {
    if (i == j)
      stack[i] = s.stack[i].substr(0, s.stack[i].length() - 1);
    else if (i == k)
      stack[i] = s.stack[i] + s.stack[j].substr(s.stack[j].length() - 1, 1);
    else
      stack[i] = s.stack[i];
  }
}

State::State(){};

int State::getNbBlocs(int i) const {
  // Precondition: 0<=i<nbStacks
  // Return the numbr of blocs on stack i
  return stack[i].length();
}

int State::getBloc(int i, int j) const {
  // Precondition: 0<=i<stack.size() and 0<=j<getNbBlocs(i)
  // Return the jth bloc on stack i
  return stack[i][j];
}

void State::print() const {
  // Print this
  for (unsigned int k = 0; k < stack.size(); k++)
    cout << "stack[" << k << "]=" << stack[k] << " ";
}

bool State::operator==(const State &s) const {
  // Return true if this=s
  for (unsigned int i = 0; i < stack.size(); i++)
    if (stack[i] != s.stack[i])
      return false;
  return true;
}
