#pragma once
#include "globalview.h"
#include "filter/shadowwindow.h"
#include "mvp/view.h"
#include "titlebarview.h"
#include "navbarview.h"
#include "funcareaview.h"

using namespace qtmaterialmvp;
using namespace qtmaterialfilter;

class MainView : public QWidget, public View {
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override {
    }
    
    TitlebarView *titlebarView() const;
    NavbarView *navbarView() const;
    FuncAreaView *funcAreaView() const;

private:
    void createUi();
    void connectSig();

private:
    TitlebarView *m_pTitlebarView = nullptr;
    NavbarView *m_pNavbarView = nullptr;
    FuncAreaView *m_pFuncAreaView = nullptr;
};