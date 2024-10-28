/*
 * @Author: weick
 * @Date: 2023-12-05 22:51:45
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:51:45
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "aenum.h"
#include <QPainter>
#include <QEvent>
#include <QPixmap>

class AGUI_EXPORT AFourStateImageWidget : public ABaseWidget {
    Q_OBJECT
public:
    AFourStateImageWidget(QWidget *parent = 0);
    ~AFourStateImageWidget();
    void setFourPixmap(QPixmap pixmap);
    void setNormalPixmap(QPixmap pixmap);
    void setHoverPixmap(QPixmap pixmap);
    void setPressedPixmap(QPixmap pixmap);
    void setDisablePixmap(QPixmap pixmap);
    void setState(AEnum::StyleStatus state);

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    AEnum::StyleStatus m_State = AEnum::StyleStatus::Normal;
    QPixmap m_FourPixmap;
    QPixmap m_NormalPixmap;
    QPixmap m_HoverPixmap;
    QPixmap m_PressedPixmap;
    QPixmap m_DisabledPixmap;
};
