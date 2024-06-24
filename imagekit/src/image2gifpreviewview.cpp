/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:50:47
 */

#include "inc/image2gifpreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace image2gif {
Image2GifPreviewView::Image2GifPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifPreviewView::~Image2GifPreviewView() {
}

void Image2GifPreviewView::createUi() {
    auto mainLay = new AVBoxLayout(this);

    preview_widget_ = new AWidget(this);
    mainLay->addWidget(preview_widget_, 1);

    preview_pixmap_label_ = new ALabel(preview_widget_);
    preview_pixmap_label_->setScaledContents(false);
    auto preview_pixmap_label_layout = new AHBoxLayout();
    preview_pixmap_label_layout->addStretch();
    preview_pixmap_label_layout->addWidget(preview_pixmap_label_);
    preview_pixmap_label_layout->addStretch();
    auto preview_widget_layout = new AVBoxLayout(preview_widget_);
    preview_widget_layout->addStretch();
    preview_widget_layout->addLayout(preview_pixmap_label_layout);
    preview_widget_layout->addStretch();

}

void Image2GifPreviewView::changeLanguage() {
}

void Image2GifPreviewView::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigListItemDataSelected, this, &Image2GifPreviewView::preViewDataSelected);
}

void Image2GifPreviewView::preViewDataSelected(Data *data) {
    if (data == nullptr) {
        return;
    }
    loadSelectedPixmap(data->file_path);
    updateSelectedPixmapSize();
}

void Image2GifPreviewView::loadSelectedPixmap(const QString &path) {
    if (path.isEmpty()) {
        return;
    }
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        return;
    }
    preview_pixmap_ = pixmap;
    // preview_pixmap_label_->setPixmap(pixmap);
}

void Image2GifPreviewView::updateSelectedPixmapSize() {
    if (preview_pixmap_.isNull()) {
        return;
    }

    QSize labelSize = preview_widget_->size();
    QSize pixmapSize = preview_pixmap_.size();

    if (pixmapSize.width() > labelSize.width() || pixmapSize.height() > labelSize.height()) {
        preview_pixmap_ = preview_pixmap_.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    preview_pixmap_label_->setPixmap(preview_pixmap_);
}
} // namespace image2gif