/*
 * @Author: weick
 * @Date: 2023-12-09 22:47:15
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:06:24
 */

#include "inc/conversionwindow.h"
#include "inc/conversionmodels.h"
#include "inc/signals.h"
#include "inc/models.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

ConversionWindow::ConversionWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ConversionWindow::~ConversionWindow() {
}

void ConversionWindow::changeData(QList<ConversionData> datas) {
    m_ConversionListView->chageData(datas);
}

void ConversionWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new AVBoxLayout(this);

    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    mainLayout->addWidget(m_Topbar);

    auto topbarLayout = new AHBoxLayout(m_Topbar->contentWidget());
    topbarLayout->setSpacing(12);
    topbarLayout->addStretch();
    m_SetingBtn = new APushButton(this);
    m_SetingBtn->setObjectName("OnlyIconButton");
    m_SetingBtn->setFixedSize(24, 24);
    m_SetingBtn->setIconSize(QSize(24, 24));
    m_SetingBtn->setIcon(QIcon(":/agui/res/image/setting-24.png"));
    topbarLayout->addWidget(m_SetingBtn);
    QWidget *topbarSplit = new QWidget(this);
    topbarSplit->setStyleSheet("background-color:#2F2F2F");
    topbarSplit->setFixedSize(1, 16);
    topbarLayout->addWidget(topbarSplit);
    topbarLayout->addSpacing(12);

    auto bodyLayout = new AVBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 0);

    auto convertListViewBG = new AWidget(this);
    convertListViewBG->setObjectName("ConversionWindow_convertListViewBG");
    bodyLayout->addWidget(convertListViewBG);

    auto convertListViewBGLayout = new AVBoxLayout(convertListViewBG);
    m_ConversionListView = new ConversionListView(this);
    convertListViewBGLayout->addWidget(m_ConversionListView);

    mainLayout->addLayout(bodyLayout);

    auto bottomBG = new AWidget(this);
    bottomBG->setFixedHeight(64);
    auto bottomLayout = new AHBoxLayout(bottomBG);
    bottomLayout->setContentsMargins(25, 0, 25, 0);
    bottomLayout->setSpacing(12);

    m_AddFileBtn = new APushButton(this);
    m_AddFileBtn->setObjectName("FullBGButton_FS15");
    m_AddFileBtn->setFixedSize(80, 32);
    m_AddFileBtn->setText("导入");
    m_AddFileBtn->setIconSize(QSize(24, 24));
    m_AddFileBtn->setIcon(QIcon(":/agui/res/image/add-24.png"));
    bottomLayout->addWidget(m_AddFileBtn);

    m_DelFileBtn = new APushButton(this);
    m_DelFileBtn->setObjectName("FullBGButton_FS15");
    m_DelFileBtn->setFixedSize(80, 32);
    m_DelFileBtn->setText("删除");
    m_DelFileBtn->setIconSize(QSize(24, 24));
    m_DelFileBtn->setIcon(QIcon(":/agui/res/image/delete-24.png"));
    bottomLayout->addWidget(m_DelFileBtn);

    m_CheckAllBtn = new APushButton(this);
    m_CheckAllBtn->setObjectName("FullBGButton_FS15");
    m_CheckAllBtn->setFixedSize(80, 32);
    m_CheckAllBtn->setText("全选");
    m_CheckAllBtn->setIconSize(QSize(24, 24));
    m_CheckAllBtn->setIcon(QIcon(":/agui/res/image/checked-24.png"));
    bottomLayout->addWidget(m_CheckAllBtn);

    bottomLayout->addStretch();

    m_ConvToBtn = new APushButton(this);
    m_ConvToBtn->setObjectName("FullBGButton_FS15");
    m_ConvToBtn->setFixedSize(124, 32);
    m_ConvToBtn->setText("转换为PNG");
    m_ConvToBtn->setIconSize(QSize(24, 24));
    m_ConvToBtn->setIcon(QIcon(":/agui/res/image/export-24.png"));
    // m_ConvToBtn->setLayoutDirection(Qt::RightToLeft);

    bottomLayout->addWidget(m_ConvToBtn);

    m_ConvAllBtn = new APushButton(this);
    m_ConvAllBtn->setObjectName("FullBGButton_FS15");
    m_ConvAllBtn->setFixedSize(124, 32);
    m_ConvAllBtn->setText("开始转换");
    m_ConvAllBtn->setIconSize(QSize(24, 24));
    m_ConvAllBtn->setIcon(QIcon(":/agui/res/image/refresh-24.png"));
    bottomLayout->addWidget(m_ConvAllBtn);

    mainLayout->addWidget(bottomBG);

    auto shadow = new AShadowEffect(this);

    m_AddGuideBtn = new APushButton(this);
    m_AddGuideBtn->setObjectName("ConversionWindow_m_AddGuideBtn");
    m_AddGuideBtn->setFixedSize(96 * 3, 96 * 2);
    m_AddGuideBtn->setIconSize(QSize(96, 96));
    m_AddGuideBtn->setIcon(QIcon(":/agui/res/image/image-file-add-96.png"));
}

void ConversionWindow::changeLanguage() {
}

void ConversionWindow::sigConnect() {
    connect(m_Topbar, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]() {
        close();
        emit Signals::getInstance()->sigGotoFunc(Models::Funcs::Startup);
    });
    connect(m_ConversionListView, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<ConversionData>();
        QRect rc = m_ConversionListView->visualRect(index);
        int posx = m_ConversionListView->mapFromGlobal(QCursor::pos()).x();
        int posy = m_ConversionListView->mapFromGlobal(QCursor::pos()).y();
        QRect borderRect = rc.adjusted(1 + 8, 1 + 8, -1, -1);
        QRect delIconRect = QRect(borderRect.x() + borderRect.width() - 24 - 2, borderRect.y() + 2, 24, 24);

        if (data.m_IsAdd) {
            emit Signals::getInstance()->sigOpenConvFileDialog(this);
        } else {
            if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
                && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
                emit Signals::getInstance()->sigDelConvFile(data.m_FilePath);
            }
        }
    });
}

void ConversionWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor(32, 32, 32, 255));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor(96, 96, 96, 255));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void ConversionWindow::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    m_AddGuideBtn->setGeometry((width() - m_AddGuideBtn->width()) / 2, (height() - m_AddGuideBtn->height()) / 2, m_AddGuideBtn->width(), m_AddGuideBtn->height());
}
