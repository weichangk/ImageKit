/*
 * @Author: weick
 * @Date: 2023-12-05 23:04:11
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-05 23:51:11
 */

#include "inc/startupwindow.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../agui/inc/aicontextwidget.h"
#include "../agui/inc/afourstateimagewidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include "../awidget/inc/apushbutton.h"
#include "inc/imagefunc.h"
#include "inc/imagefuncview.h"
#include "inc/imagefuncmodel.h"
#include "inc/imagefuncdelegate.h"
#include <QPainter>
#include <QPainterPath>

StartupWindow::StartupWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

StartupWindow::~StartupWindow() {
}

void StartupWindow::imageFuncModelAppend(QList<ImageFunc *> funcs) {
    // m_ImageFuncModel->append(funcs);
}

void StartupWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new AHBoxLayout(this);

    auto leftLayout = new AVBoxLayout();
    mainLayout->addLayout(leftLayout);

    auto rightLayout = new AVBoxLayout();
    mainLayout->addLayout(rightLayout);

    // left
    m_Navbar = new ACanMoveWidget(this);
    m_Navbar->setFixedWidth(140);
    leftLayout->addWidget(m_Navbar, 1);

    auto navbarLayout = new AVBoxLayout(m_Navbar);
    navbarLayout->setContentsMargins(12, 24, 12, 24);
    navbarLayout->setSpacing(10);

    auto logoLayout = new AHBoxLayout();
    logoLayout->setSpacing(6);
    navbarLayout->addLayout(logoLayout);

    m_LogoBtn = new APushButton(m_Navbar);
    m_LogoBtn->setObjectName("StartupWindow_m_LogoBtn");
    m_LogoBtn->setFixedSize(32, 32);
    logoLayout->addWidget(m_LogoBtn);

    auto vipLayout = new AVBoxLayout();
    vipLayout->setSpacing(0);
    logoLayout->addLayout(vipLayout);

    m_VipBtn = new APushButton(m_Navbar);
    m_VipBtn->setObjectName("StartupWindow_m_VipBtn");
    m_VipBtn->setText("登录");
    vipLayout->addWidget(m_VipBtn);

    m_VipRightsBtn = new APushButton(m_Navbar);
    m_VipRightsBtn->setObjectName("StartupWindow_m_VipRightsBtn");
    m_VipRightsBtn->setText("会员特惠");
    vipLayout->addWidget(m_VipRightsBtn);

    navbarLayout->addSpacing(20);

    QMap<int, QVariantList> navbarData;
    navbarData.insert(StartupNav::MyFunc, QVariantList() << ":/res/image/icon24_menu_myfuncs.png"
                                                         << "全部功能");
    navbarData.insert(StartupNav::MyFiles, QVariantList() << ":/res/image/icon24_menu_myfiles.png"
                                                          << "我的文件");
    navbarData.insert(StartupNav::MySettings, QVariantList() << ":/res/image/icon24_menu_mysettings.png"
                                                             << "设置");
    m_anavbarwidget = new ANavbarWidget(navbarData, this);
    navbarLayout->addWidget(m_anavbarwidget);

    navbarLayout->addStretch();

    // right
    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    rightLayout->addWidget(m_Topbar);

    auto funcLayout = new AHBoxLayout();
    funcLayout->setContentsMargins(0, 0, 1, 1);
    rightLayout->addLayout(funcLayout, 1);

    m_FuncArea = new AWidget(this);
    m_FuncArea->setObjectName("StartupWindow_m_FuncArea");
    funcLayout->addWidget(m_FuncArea, 1);

    auto funcAreaLayout = new AHBoxLayout(m_FuncArea);
    funcAreaLayout->setContentsMargins(20, 20, 20, 20);

    // m_ImageFuncView = new ImageFuncView(this);
    // m_ImageFuncModel = new ImageFuncModel(m_ImageFuncView);
    // m_ImageFuncDelegate = new ImageFuncDelegate(m_ImageFuncView);
    // m_ImageFuncView->setObjectName("StartupWindow_m_ImageFuncView");
    // m_ImageFuncView->setModel(m_ImageFuncModel);
    // m_ImageFuncView->setItemDelegate(m_ImageFuncDelegate);
    // m_ImageFuncView->viewport()->installEventFilter(m_ImageFuncDelegate);//关键
    // funcAreaLayout->addWidget(m_ImageFuncView, 1);

    auto shadow = new AShadowEffect(this);
}

void StartupWindow::changeLanguage() {
}

void StartupWindow::sigConnect() {
    connect(m_Topbar, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]() { close(); });
}

void StartupWindow::paintEvent(QPaintEvent *event) {
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

void StartupWindow::slotNavClicked(QString objectName) {
    if ("m_FuncBtn" == objectName) {
    } else if ("m_FilesBtn" == objectName) {
    } else if ("m_SettingsBtn" == objectName) {
    }
}
