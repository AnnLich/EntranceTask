#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include "cellgriditem.h"
#include "generator.h"
#include <QGraphicsScene>

class GridScene : public QGraphicsScene {
    Q_OBJECT

public:
    GridScene(QObject *parent = nullptr) : QGraphicsScene(parent){}

    CellGridItem *addCellGridItem(qreal x, qreal y, qreal w, qreal h, int i,
                                  int j, const QPen &pen = QPen(),
                                  const QBrush &brush = QBrush());

signals:
    void info(std::tuple<int, int, int, int, int> info);

public slots:
    void callGenerate();
    void findPath();

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

private slots:
    void setTarget(CellGridItem *item, const bool setA = true);

private:
    void updateGrid(const std::vector<bool> &gridWithBlocks);
    void resetTargets();
    void resetTarget(CellGridItem *item);
    void resetPath();

public:
    int cellsX{};
    int cellsY{};

private:
    CellGridItem *targetA{nullptr};
    CellGridItem *targetB{nullptr};

    std::vector<size_t> lastPath;

    Generator generator;

    static constexpr double cellSize{50.0};
};

#endif // GRIDSCENE_H
