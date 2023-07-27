#include "gridscene.h"
#include "pathfinder.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMessageBox>
#include <future>

void GridScene::callGenerate() {
    resetTargets();
    updateGrid(generator.generateBlocks(cellsX, cellsY));
}

void GridScene::setTarget(CellGridItem *item, const bool setA) {
    if (setA) {
        if (item == targetB)
            targetB = nullptr;
        resetTarget(targetA);
        item->setBrush(QBrush(Qt::blue));
        targetA = item;
    } else {
        resetTarget(targetB);
        item->setBrush(QBrush(Qt::red));
        targetB = item;
    }
}

void GridScene::resetTarget(CellGridItem *item) {
    if (item) {
        item->setBrush(QBrush(Qt::white));
        resetPath();
    }
}

void GridScene::resetPath() {
    if (!lastPath.empty()) {
        auto itemsList{items(Qt::AscendingOrder)};
        for (const auto &index : lastPath)
            qgraphicsitem_cast<CellGridItem *>(itemsList.at(index))
                ->setBrush(QBrush(Qt::white));
    }
}

CellGridItem *GridScene::addCellGridItem(qreal x, qreal y, qreal w, qreal h,
                                         int index_x, int index_y,
                                         const QPen &pen, const QBrush &brush) {
    CellGridItem *item{new CellGridItem(x, y, w, h, index_x, index_y)};
    item->setPen(pen);
    item->setBrush(brush);
    addItem(item);
    return item;
}

void GridScene::updateGrid(const std::vector<bool> &gridWithBlocks) {
    if (cellsX + cellsY < 3) {
        QMessageBox::warning(views().front(), "Generate Grid",
                             "The grid is too small!");
        return;
    }

    clear();
    lastPath.clear();
    setSceneRect(0, 0, cellsX * cellSize, cellsY * cellSize);

    for (int i{}; i < cellsY; ++i) {
        for (int j{}; j < cellsX; ++j) {
            auto currentItem = [&]() {
                if (!gridWithBlocks[i * cellsX + j])
                    return addCellGridItem(j * cellSize, i * cellSize, cellSize, cellSize,
                                           j, i, QPen(), QBrush(Qt::white));
                else
                    return addCellGridItem(j * cellSize, i * cellSize, cellSize, cellSize,
                                           j, i, QPen(), QBrush(Qt::black));
            }();

            connect(&currentItem->object, &CellObject::targetChanged,
                    [this](CellGridItem *item) { setTarget(item, true); });
            connect(&currentItem->object, &CellObject::tryCallPathfinder,
                    [this](CellGridItem *item) {
                        if (targetA) {
                            setTarget(item, false);
                            findPath();
                        }
                    });
        }
    }
}

void GridScene::resetTargets() {
    targetA = nullptr;
    targetB = nullptr;
}

void GridScene::findPath() {
    Pathfinder finder(items(Qt::AscendingOrder), cellsX, cellsY, targetA,
                      targetB);
    auto f = std::async(std::launch::async, &Pathfinder::findPath, &finder);
    lastPath = f.get();
    emit info(std::make_tuple(targetA->index_x, targetA->index_y,
                              targetB->index_x, targetB->index_y,
                              lastPath.size()));
}

void GridScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) {
    if (auto viewList{views()}; !viewList.isEmpty()) {
        if (wheelEvent->delta() > 0)
            viewList.front()->scale(1.2, 1.2);
        else
            viewList.front()->scale(0.8, 0.8);
    }
}
