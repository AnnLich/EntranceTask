#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "cellgriditem.h"
#include <QGraphicsItem>

class Pathfinder {
public:
    Pathfinder(const QList<QGraphicsItem *> &items, const int columns,
               const int rows, CellGridItem *point_A, CellGridItem *point_B)
        : items(items), rows(rows), columns(columns), point_A(point_A),
        point_B(point_B) {}

    std::vector<size_t> findPath();

private:
    bool isBlock(const int x, const int y);
    std::vector<size_t> getPath(const std::vector<std::vector<int>> &dirMap);

private:
    const QList<QGraphicsItem *> items;
    int rows;
    int columns;

    CellGridItem *point_A;
    CellGridItem *point_B;

    static constexpr int directions{4};
    static constexpr std::array<int, directions> xDirections{0, 1, 0, -1};
    static constexpr std::array<int, directions> yDirections{1, 0, -1, 0};
};

struct Node {
    Node(const std::pair<int, int> &curPos, int g, int f)
        : curPos(curPos), g(g), f(f) {}

    void calculateFValue(const std::pair<int, int> &dest) {
        f = g + abs(dest.first - curPos.first) + abs(dest.second - curPos.second);
    }

    std::pair<int, int> curPos;
    int g{};
    int f{};
};

struct cmp {
    bool operator()(const Node &left, const Node &right) const {
        return left.f > right.f;
    }
};

#endif // PATHFINDER_H
