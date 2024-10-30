#include "inc/editfilelistview.h"
#include "inc/signals.h"
#include "core/painterhelper.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>

namespace imageedit {
inline QRect fileItemDeteleRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + rc.width() - 16 - 16, rc.y() + 16, 16, 16);
}

inline QRect fileItemNameRect(QRect itemRect) {
    auto rc = itemRect;
    auto deleteRect = fileItemDeteleRect(rc);
    int nameX = rc.x() + 16;
    int nameWidth = deleteRect.x() - 16 - nameX;
    return QRect(nameX, rc.y() + 12, nameWidth, 24);
}

EditFileItemDelegate::EditFileItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

EditFileItemDelegate::~EditFileItemDelegate() {
}

bool EditFileItemDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        event_type_ = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            curpos_ = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

void EditFileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<Data>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = event_type_ == QEvent::MouseButtonPress && rc.contains(curpos_);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto borderRect = rc.adjusted(1, 1, -1, -1);
    painter->setBrush(QColor("#2F2D2D"));
    painter->drawRoundedRect(borderRect, 0, 0);
    painter->setBrush(Qt::NoBrush);

    if (hover) {
        auto delIconRect = fileItemDeteleRect(rc);
        PainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    QPen pen(QColor("#1F1F1F"));
    pen.setWidth(1);
    painter->setPen(pen);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(Qt::blue);
    painter->setPen(pen);
    if (selected) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    QString fileName = data.file_name;
    auto nameRect = fileItemNameRect(rc);
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    }
    painter->drawText(nameRect, Qt::PlainText, fileName);
    painter->setPen(Qt::NoPen);
}

QSize EditFileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return size_;
}

void EditFileItemDelegate::changeSizeHint(const QSize &size) {
    size_ = size;
}

EditFileListView::EditFileListView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

EditFileListView::~EditFileListView() {
}

void EditFileListView::changeData(QList<Data> datas) {
    file_list_view_->chageData(datas);
}

void EditFileListView::setCurrentIndex(int index) {
    file_list_view_->setCurrentIndex(file_list_view_->model()->index(index, 0));
}

int EditFileListView::currentIndex() {
    return file_list_view_->currentIndex().row();
}

void EditFileListView::createUi() {
    file_name_label_ = new QLabel(this);
    file_name_label_->setText("文件名");

    add_file_button_ = new QPushButton(this);
    add_file_button_->setObjectName("OnlyIconButton");
    add_file_button_->setFixedSize(24, 24);
    add_file_button_->setIconSize(QSize(24, 24));
    add_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    delete_file_button_ = new QPushButton(this);
    delete_file_button_->setObjectName("OnlyIconButton");
    delete_file_button_->setFixedSize(24, 24);
    delete_file_button_->setIconSize(QSize(24, 24));
    delete_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    auto buttonsWidget = new QWidget(this);
    buttonsWidget->setFixedHeight(32);
    auto buttonsLayout = new QHBoxLayout(buttonsWidget);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->addWidget(file_name_label_);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(add_file_button_);
    buttonsLayout->addWidget(delete_file_button_);

    file_list_view_ = new ListView<Data>(this);
    file_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    file_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    file_list_view_->setResizeMode(QListView::Adjust);
    file_list_view_->setViewMode(QListView::ListMode);
    file_list_view_->setFlow(QListView::TopToBottom);
    file_list_view_->setDragEnabled(false);
    file_list_view_->setSelectionMode(QAbstractItemView::SingleSelection);

    auto delegate = new EditFileItemDelegate(this);
    file_list_view_->setItemDelegate(delegate);
    file_list_view_->viewport()->installEventFilter(delegate);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(file_list_view_, 1);
}

void EditFileListView::sigConnect() {
    connect(add_file_button_, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigOpenFileDialog(this);
    });
    connect(delete_file_button_, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigDeleteAll();
    });
    connect(file_list_view_, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<Data>();
        QRect rc = file_list_view_->visualRect(index); // sizeHint大小，如果布局导致实际大小不是sizeHint大小时下面的位置计算就不对了
        int posx = file_list_view_->mapFromGlobal(QCursor::pos()).x();
        int posy = file_list_view_->mapFromGlobal(QCursor::pos()).y();
        QRect delIconRect = fileItemDeteleRect(rc);
        if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
            && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
            emit SIGNALS->sigDeleteFile(data.file_path);
            return;
        }
        emit SIGNALS->sigClickedFile(data.file_path);
    });
}
} // namespace imageedit