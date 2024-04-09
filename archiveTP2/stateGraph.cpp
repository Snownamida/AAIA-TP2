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
#include "stateGraph.h"
#include "state.h"

StateGraph::StateGraph() {
  // Constructor that creates a bloc world planning problem
  cout << "Enter the number of stacks: ";
  cin >> nbStacks;
  cout << "Enter the number of blocs: ";
  cin >> nbBlocs;
  if (nbStacks <= 0 || nbBlocs <= 0) {
    cout << "The number of stacks and the number of blocs must be positive "
            "numbers"
         << endl;
    exit(0);
  }
}

State StateGraph::initialState() const {
  // Return the initial state
  return State(nbStacks, nbBlocs);
}

bool StateGraph::isFinal(const State &s) const {
  // Return true if s is a final state
  for (int i = 0; i < nbStacks - 1; i++)
    if (s.getNbBlocs(i) > 0)
      return false;
  for (int i = 0; i < nbBlocs; i++)
    if (s.getBloc(nbStacks - 1, i) != 'a' + nbBlocs - 1 - i)
      return false;
  return true;
}

int StateGraph::searchActions(const State &s) {
  // Return the number of all possible actions from state s
  // initialize actions with all possible actions from state s
  // An action is an integer value a such that a/nbStacks is the stack from
  // which a bloc is removed and a%nbStacks is the stack on which the bloc is
  // added
  actions.clear();
  for (int i = 0; i < nbStacks; i++) {
    if (s.getNbBlocs(i) > 0) {
      for (int j = 0; j < nbStacks; j++) {
        if (i != j)
          actions.push_back(i * nbStacks + j);
      }
    }
  }
  return actions.size();
}

int StateGraph::h0(const State &s) const { return 0; }
int StateGraph::h1(const State &s) const {
  int c = 0;
  for (auto it = s.stack.begin(); it != s.stack.end() - 1; ++it) {
    c += it->length();
  }
  return c;
}
int StateGraph::h2(const State &s) const {
  int est_h1 = h1(s);

  auto lastCol = s.stack.back();
  int nbBadBlock = lastCol.length();
  char lettreDuBonBlock = 'a' + nbBlocs - 1;

  for (unsigned long i = 0; i < lastCol.length(); ++i) {
    if (lastCol[i] == lettreDuBonBlock) {
      --nbBadBlock;
      --lettreDuBonBlock;
    } else
      break;
  }

  return est_h1 + 2 * nbBadBlock;
}
int StateGraph::h3(const State &s) const {
  int c = 0;
  return c;
}
int StateGraph::h4(const State &s) const {
  int est_h2 = h2(s);

  int nbBadBlock = 0;

  // 在不是最后一列的列上, 查看有多少个方块在它之下有比它大的方块.
  // 这些方块需要在某一时刻挪到不是最后一列的位置上,
  // 让它们下面那些比它大的方块先去最后一列
  // 算法 : 对于每一列, 从下往上遍历. 让每一个方块和它之下的最大方块作比较
  for (auto it = s.stack.begin(); it < s.stack.end() - 1; ++it) {
    auto col = *it;
    char maxLetterCol = 0;
    for (unsigned long i = 0; i < col.size(); ++i) {
      if (maxLetterCol > col[i]) {
        ++nbBadBlock;
      } else {
        maxLetterCol = col[i];
      }
    }
  }
  return est_h2 + nbBadBlock;
}

int StateGraph::heuristic(const State &s) const { return h4(s); }

State StateGraph::transition(const State &s, int i) {
  // Return the state obtained when performing ith action on state s
  return State(s, actions[i] / nbStacks, actions[i] % nbStacks);
}

int StateGraph::getCost(const State &s, int i) const {
  // Precondition: 0<=i<searchActions(s)
  // Return the cost of performing ith action on state s
  return 1;
}

void StateGraph::print(const State &s, const State &s_succ) {
  static State s0 = initialState();
  if (s == s0) {
    printf("Init: ");
    s.print();
    cout << "h : " << heuristic(s);
    printf("\n");
  }
  // Print the action that has been used to go from s to s_succ
  for (int i = 0; i < nbStacks; i++) {
    if (s.getNbBlocs(i) > 0) {
      for (int j = 0; j < nbStacks; j++) {
        if (i != j && State(s, i, j) == s_succ) {
          printf("%d->%d: ", i, j);
          s_succ.print();
          cout << "h : " << heuristic(s_succ);
          printf("\n");
          return;
        }
      }
    }
  }
}
