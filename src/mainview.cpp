#include "mainview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

TitlebarView *MainView::titlebarView() const {
    return m_pTitlebarView;
}

NavbarView *MainView::navbarView() const {
    return m_pNavbarView;
}

FuncAreaView *MainView::funcAreaView() const {
    return m_pFuncAreaView;
}

void MainView::createUi() {
    setObjectName("MainView");
    setAttribute(Qt::WA_StyledBackground);
    setMinimumSize(1096, 680);
    setFixedSize(1096, 680);
    setWindowFlags(Qt::FramelessWindowHint);

    auto ShadowEffect = new ShadowPixmap(this);

    m_pTitlebarView = new TitlebarView(this);

    m_pNavbarView = new NavbarView(this);

    m_pFuncAreaView = new FuncAreaView(this);

    auto rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);
    rightLayout->addWidget(m_pTitlebarView);
    rightLayout->addWidget(m_pFuncAreaView);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_pNavbarView);
    layout->addLayout(rightLayout, 1);
}

void MainView::connectSig() {
}