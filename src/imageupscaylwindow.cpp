#include "inc/imageupscaylwindow.h"
#include "inc/signals.h"
#include "control/shadoweffect.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace imageupscayl {
ImageUpscaylWindow::ImageUpscaylWindow(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageUpscaylWindow::~ImageUpscaylWindow() {
}

void ImageUpscaylWindow::changeFileListData(QList<Data> datas) {
    if (datas.count() == 0) {
        stacked_widget_->setCurrentIndex(0);
    } else {
        stacked_widget_->setCurrentIndex(1);
    }
    file_list_view_->changeData(datas);
}

void ImageUpscaylWindow::setFileListCurrentIndex(int index) {
    file_list_view_->setCurrentIndex(index);
}

int ImageUpscaylWindow::fileListCurrentIndex() {
    return file_list_view_->currentIndex();
}

void ImageUpscaylWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1200, 760);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    topbar_ = new TopbarWidget(this);
    topbar_->setCloseBtnTopRight10Radius();
    topbar_->setMinVisible(false);
    topbar_->setMaxVisible(false);
    mainLayout->addWidget(topbar_);

    auto topbarLayout = new QHBoxLayout(topbar_->contentWidget());
    topbarLayout->setContentsMargins(0, 0, 0, 0);
    topbarLayout->setSpacing(12);
    topbarLayout->addSpacing(12);
    auto logoLayout = new QHBoxLayout();
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->setSpacing(4);
    logo_label_ = new QLabel(this);
    QPixmap logo(":/agui/res/image/Compression-logo-32.png");
    logo_label_->setPixmap(logo);
    logoLayout->addWidget(logo_label_);
    name_label_ = new QLabel(this);
    name_label_->setObjectName("edit_window_name_lable");
    name_label_->setText("图片增强");
    logoLayout->addWidget(name_label_);
    topbarLayout->addLayout(logoLayout);
    topbarLayout->addStretch();

    auto bodyLayout = new QHBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 25);

    auto bodyBg = new QWidget(this);
    bodyBg->setObjectName("edit_window_body_bg");
    bodyLayout->addWidget(bodyBg, 1);
    auto bodyBgLayout = new QHBoxLayout(bodyBg);
    bodyBgLayout->setContentsMargins(0, 0, 0, 0);
    
    stacked_widget_ = new QStackedWidget(this);
    bodyBgLayout->addWidget(stacked_widget_, 1);

    import_guide_ = new ImportGuideWidget(this);
    stacked_widget_->addWidget(import_guide_);

    auto workWidget = new QWidget(this);
    stacked_widget_->addWidget(workWidget);

    auto workWidgetLayout = new QHBoxLayout(workWidget);
    workWidgetLayout->setContentsMargins(0, 0, 0, 0);
    
    auto leftWidget = new QWidget(this);
    leftWidget->setFixedWidth(260);
    workWidgetLayout->addWidget(leftWidget);

    auto leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    setting_button_ = new QPushButton(this);
    leftLayout->addWidget(setting_button_);
    file_list_button_ = new QPushButton(this);
    leftLayout->addWidget(file_list_button_);

    left_stacked_widget_ = new QStackedWidget(this);
    leftLayout->addWidget(left_stacked_widget_);

    setting_view_ = new ImageUpscaylSettingView(this);
    left_stacked_widget_->addWidget(setting_view_);

    file_list_view_ = new ImageUpscaylFileListView(this);
    left_stacked_widget_->addWidget(file_list_view_);

    upscayl_button_ = new QPushButton(this);
    leftLayout->addWidget(upscayl_button_);

    preview_view_ = new ImageUpscaylPreviewView(this);
    workWidgetLayout->addWidget(preview_view_, 1);

    mainLayout->addLayout(bodyLayout, 1);

    auto shadow = new ShadowEffect(this);
}

void ImageUpscaylWindow::sigConnect() {
    connect(topbar_, &TopbarWidget::sigMin, this, [=]() { showMinimized(); });
    connect(topbar_, &TopbarWidget::sigMax, this, [=]() { showMaximized(); });
    connect(topbar_, &TopbarWidget::sigNormal, this, [=]() { showNormal(); });
    connect(topbar_, &TopbarWidget::sigClose, this, [=]() {
        close();
        emit ::SIGNALS->sigGotoFunc(ImageFunc::STARTUP);
    });
    connect(import_guide_, &ImportGuideWidget::sigClicked, this, [=]() {
        emit SIGNALS->sigOpenFileDialog(this);
    });
    connect(setting_button_, &QPushButton::clicked, this, [=]() {
        left_stacked_widget_->setCurrentIndex(0);
    });
    connect(file_list_button_, &QPushButton::clicked, this, [=]() {
        left_stacked_widget_->setCurrentIndex(1);
    });
}
void ImageUpscaylWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor("#181818"));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor("#402F38"));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void ImageUpscaylWindow::moveEvent(QMoveEvent *event) {
    QWidget::moveEvent(event);
    emit SIGNALS->sigWindowMove();
}
} // namespace imageupscayl