/*
 Implementation of class StateGraph for the bloc world problem
 Copyright (C) 2023 Christine Solnon
 Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
 modifier au titre des clauses de la Licence Publique Générale GNU, telle que
 publiée par la Free Software Foundation. Ce programme est distribué dans
 l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE ; sans même une garantie
 implicite de COMMERCIABILITE ou DE CONFORMITE A UNE UTILISATION PARTICULIERE.
 Voir la Licence Publique Générale GNU pour plus de détails.
 */
#include "state.h"
class StateGraph {
public:
  StateGraph();
  // Creates a state-transition problem

  State initialState() const;
  // Return the initial state

  bool isFinal(const State &s) const;
  // Return true if s is a final state

  int searchActions(const State &s);
  // Return the number of all possible actions from state s

  int getCost(const State &s, int i) const;
  // Precondition: 0<=i<searchActions(s)
  // Return the cost of performing ith action on state s

  State transition(const State &s, int i);
  // Precondition: 0<=i<searchActions(s)
  // Return the state obtained when performing ith action on state s

  void print(const State &s, const State &s_succ);
  // Display the action used to go from s to s_succ

  int h0(const State &s) const;
  int h1(const State &s) const;
  int h2(const State &s) const;
  int h3(const State &s) const;
  int h4(const State &s) const;

  int heuristic(const State &s) const;
  // Return a lower bound of the length of the shortest path from s to a final
  // state

private:
  vector<int> actions;
  int nbBlocs;  // Number of blocs
  int nbStacks; // Number of stacks
};
