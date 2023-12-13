/*
 * @Author: weick
 * @Date: 2023-12-09 22:00:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:58:32
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "inc/conversionlistview.h"
#include <QButtonGroup>

class ConversionWindow : public ABaseWidget {
    Q_OBJECT
public:
    enum ConvertOutType {
        PNG = 0,
        JPG,
        JPEG,
        SVG
    };
    Q_ENUM(ConvertOutType)

    explicit ConversionWindow(QWidget *parent = 0);
    ~ConversionWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;

private:
    ATopbar *m_Topbar = 0;
    ACanMoveWidget *m_Navbar = 0;
    APushButton *m_LogoBtn = 0;
    ALabel *m_ProductLab = 0;
    ANavbarWidget *m_Navbarwidget = 0;
    ConversionListView *m_ConversionListView = 0;
};
