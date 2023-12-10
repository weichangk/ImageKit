/*
 * @Author: weick
 * @Date: 2023-12-09 22:00:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 00:23:09
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include <QButtonGroup>

class CompressionWindow : public ABaseWidget {
    Q_OBJECT
public:
    enum CompressionOutType {
        PNG = 0,
        JPEG,
        WEBP
    };
    Q_ENUM(CompressionOutType)

    explicit CompressionWindow(QWidget *parent = 0);
    ~CompressionWindow();

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
};

