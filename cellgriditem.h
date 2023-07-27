#ifndef CELLGRIDITEM_H
#define CELLGRIDITEM_H

#include <QGraphicsRectItem>
class CellGridItem;

class CellObject : public QObject {
    Q_OBJECT

public:
    CellObject() = default;

signals:
    void targetChanged(CellGridItem *);
    void targetAReseted(CellGridItem *);
    void tryCallPathfinder(CellGridItem *);
};

class CellGridItem : public QGraphicsRectItem {
public:
    CellGridItem(qreal x, qreal y, qreal w, qreal h, int index_x, int index_y,
                 QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;

public:
    CellObject object;
    int index_x{};
    int index_y{};
};

#endif // CELLGRIDITEM_H
