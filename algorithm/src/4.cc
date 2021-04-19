#include <eigen3/Eigen/Dense>
#include <iostream>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;
using namespace Eigen;

#define INF 999
struct Graph {
  int vexnum;
  MatrixXi matrix;
  Graph(int n) : vexnum(n), matrix(n, n) {}
};

void floyd(Graph &G, MatrixXi &path, MatrixXi &dist) {

  for (auto i = 0; i < G.vexnum; i++) {
    for (auto j = 0; j < G.vexnum; j++) {
      dist(i,j) = G.matrix(i,j);
      path(i,j) = j;
    }
  }

  for (auto k = 0; k < G.vexnum; k++) {
    for (auto i = 0; i < G.vexnum; i++) {
      for (auto j = 0; j < G.vexnum; j++) {
        if (k == 0) {
          if (i == j || G.matrix(i,j) == INF)
            path(i,j) = INF;
          else
            path(i,j) = i;
        } else {
          if (dist(i,j) > dist(i,k) + dist(k,j))
            path(i,j) = path(k,j);
        }

        auto tmp = (dist(i,k) == INF || dist(k,j) == INF)
                      ? INF
                      : (dist(i,k) + dist(k,j));
        if (dist(i,j) > tmp) {
          dist(i,j) = tmp;
        }
      }
    }
  }
}
void printAllPath(MatrixXi &path, int i, int j) {
  if (path(i,j) == INF) path(i,j) = 0;
  if (i == j)
    printf("%d ", i + 1);
  else {
    printAllPath(path, i, path(i,j));
    printf("%d ", j + 1);
  }
}

int main() {
  Graph g(5);
  MatrixXi path(5,5);
  MatrixXi dist(5,5);
  g.matrix.setZero();

  g.matrix(0,1) = 3;
  g.matrix(0,2) = 8;
  g.matrix(0,3) = INF;
  g.matrix(0,4) = -4;
  g.matrix(1,0) = INF;
  g.matrix(1,2) = INF;
  g.matrix(1,3) = 1;
  g.matrix(1,4) = 7;
  g.matrix(2,0) = INF;
  g.matrix(2,1) = 4;
  g.matrix(2,3) = INF;
  g.matrix(2,4) = INF;
  g.matrix(3,0) = 2;
  g.matrix(3,1) = INF;
  g.matrix(3,2) = -5;
  g.matrix(3,4) = INF;
  g.matrix(4,0) = INF;
  g.matrix(4,1) = INF;
  g.matrix(4,2) = INF;
  g.matrix(4,3) = 6;

  std::cout << g.matrix << std::endl;

  printf("route:\n");
  floyd(g, path, dist);
  for (auto i = 0; i < g.vexnum; i++) {
    for (auto j = 0; j < g.vexnum; j++) {
      printAllPath(path, j, i);
      if (i == j)
        printf("%d", i + 1);
      printf("\n");
    }
  }
}
