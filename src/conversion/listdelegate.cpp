#include "conversion/listdelegate.h"
#include "conversion/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

ListDelegate::ListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<Data>();
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, -8, -8);
    
    QColor bgColor = QColor("#232334");
    if (hover) {
        bgColor = QColor("#463c6c");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, 8, 8);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = rc.adjusted(4, 24, -12, -12);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, 8, true);

    auto checkedRect = QRect(bgRect.x() + 4, bgRect.y() + 4, 16, 16);
    Painter::paintPixmap(painter, checkedRect, data.is_checked ? data.checked_icon : data.unchecked_icon, 1, 0, true);

    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    if (hover) {
        Painter::paintPixmap(painter, delRect, data.delete_icon, 1, 0, true);
    }

    auto nameRect = QRect(checkedRect.right() + 4, checkedRect.y(), delRect.x() - checkedRect.right() - 4, 16);
    QColor nameColor = QColor("#ffffff");
    QPen pen(nameColor);
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(10);
    painter->setFont(font);
    QString fileName = data.file_name;
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, fileName);
    painter->setPen(Qt::NoPen);
}

bool ListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_EventType = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            m_CurPos = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}

void ListDelegate::changeSizeHint(const QSize &size) {
    m_Size = size;
}