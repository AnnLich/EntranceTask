#include "pathfinder.h"
#include <QBrush>
#include <queue>

std::vector<size_t> Pathfinder::findPath() {
    std::vector<std::vector<int>> dirMap(columns, std::vector<int>(rows));
    std::vector<std::vector<bool>> closed(columns, std::vector<bool>(rows));
    std::vector<std::vector<int>> opened(columns, std::vector<int>(rows));

    std::priority_queue<Node, std::vector<Node>, cmp> q;

    {
        Node startNode(std::make_pair(point_A->index_x, point_A->index_y), 0, 0);
        startNode.calculateFValue(
            std::make_pair(point_B->index_x, point_B->index_y));
        q.push(startNode);
    }

    while (!q.empty()) {
        Node currentNode(q.top().curPos, q.top().g, q.top().f);
        int col = currentNode.curPos.first;
        int row = currentNode.curPos.second;

        q.pop();
        opened[col][row] = 0;
        closed[col][row] = true;

        if (row == point_B->index_y && col == point_B->index_x) {
            while (!q.empty())
                q.pop();

            return getPath(dirMap);
        }

        for (int i{}; i < directions; i++) {
            int xNext = col + xDirections[i];
            int yNext = row + yDirections[i];

            if (!(xNext < 0 || xNext > columns - 1 || yNext < 0 || yNext > rows - 1 ||
                  isBlock(xNext, yNext) || closed[xNext][yNext])) {
                Node nextNode(std::make_pair(xNext, yNext), currentNode.g,
                              currentNode.f);
                ++nextNode.g;
                nextNode.calculateFValue(
                    std::make_pair(point_B->index_x, point_B->index_y));

                if (opened[xNext][yNext] == 0) {
                    opened[xNext][yNext] = nextNode.f;
                    q.push(std::move(nextNode));

                    dirMap[xNext][yNext] = (i + directions / 2) % directions;
                } else if (opened[xNext][yNext] > nextNode.f) {
                    opened[xNext][yNext] = nextNode.f;

                    dirMap[xNext][yNext] = (i + directions / 2) % directions;

                    std::priority_queue<Node, std::vector<Node>, cmp> temp;
                    while (!(q.top().curPos.first == xNext &&
                             q.top().curPos.second == yNext)) {
                        temp.push(q.top());
                        q.pop();
                    }

                    q.pop();

                    while (!temp.empty()) {
                        q.push(temp.top());
                        temp.pop();
                    }

                    q.push(std::move(nextNode));
                }
            }
        }
    }

    return std::vector<size_t>();
}

bool Pathfinder::isBlock(const int x, const int y) {
    if (auto cell{qgraphicsitem_cast<CellGridItem *>(items.at(y * columns + x))};
        QColor(0, 0, 0) == cell->brush().color())
        return true;

    return false;
}

std::vector<size_t>
Pathfinder::getPath(const std::vector<std::vector<int>> &dirMap) {
    std::vector<size_t> path;
    int row = point_B->index_y;
    int col = point_B->index_x;
    while (!(row == point_A->index_y && col == point_A->index_x)) {
        auto j = dirMap[col][row];

        if (!(row == point_B->index_y && col == point_B->index_x)) {
            path.emplace_back(row * columns + col);
            if (auto cell{qgraphicsitem_cast<CellGridItem *>(items.at(path.back()))})
                cell->setBrush(QBrush(Qt::green));
        }

        col += xDirections[j];
        row += yDirections[j];
    }
    return path;
}
