#include "cellgriditem.h"
#include <QBrush>

CellGridItem::CellGridItem(qreal x, qreal y, qreal w, qreal h, int index_x,
                           int index_y, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, w, h, parent), index_x(index_x),
    index_y(index_y) {
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

void CellGridItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
    if (QColor(Qt::black) != brush().color())
        object.targetChanged(this);
}

void CellGridItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    if (QColor(Qt::black) != brush().color() &&
        QColor(Qt::blue) != brush().color() && QColor(Qt::red) != brush().color())
        emit object.tryCallPathfinder(this);
}
