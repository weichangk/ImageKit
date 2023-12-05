/*
 * @Author: weick
 * @Date: 2023-12-05 22:54:18
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:54:18
 */

#include "inc/aarrowwidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

AArrowWidget::AArrowWidget(QWidget *parent) :
    ABaseWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(m_shadowWidth);
    this->setGraphicsEffect(shadowEffect);
}

void AArrowWidget::setCenterWidget(QWidget *widget) {
    QHBoxLayout *hMainLayout = new QHBoxLayout(this);
    hMainLayout->setSpacing(0);
    if (m_triangleDirection == 1) {
        hMainLayout->setContentsMargins(m_shadowWidth, m_shadowWidth + m_triangleHeight, m_shadowWidth, m_shadowWidth);
    } else if (m_triangleDirection == 2) {
        hMainLayout->setContentsMargins(m_shadowWidth, m_shadowWidth, m_shadowWidth + m_triangleHeight, m_shadowWidth);
    } else if (m_triangleDirection == 3) {
        hMainLayout->setContentsMargins(m_shadowWidth, m_shadowWidth, m_shadowWidth, m_shadowWidth + m_triangleHeight);
    } else {
        hMainLayout->setContentsMargins(m_shadowWidth + m_triangleHeight, m_shadowWidth, m_shadowWidth, m_shadowWidth);
    }
    hMainLayout->addWidget(widget);
}

void AArrowWidget::setShadowWidth(int width) {
    m_shadowWidth = width;
}

void AArrowWidget::setBorderRadius(int radius) {
    m_borderRadius = radius;
}

void AArrowWidget::setTriangleDirection(int direction) {
    m_triangleDirection = direction;
}

void AArrowWidget::setTriangleX(int x) {
    m_triangleX = x;
}

void AArrowWidget::setTriangleY(int y) {
    m_triangleY = y;
}

void AArrowWidget::setTriangleInfo(int width, int height) {
    m_triangleWidth = width;
    m_triangleHeight = height;
}

void AArrowWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));

    // 小三角区域;
    QPolygon trianglePolygon;
    QPainterPath drawPath;
    if (m_triangleDirection == 1) {
        trianglePolygon << QPoint(m_triangleX, m_triangleHeight + m_shadowWidth);
        trianglePolygon << QPoint(m_triangleX + m_triangleWidth / 2, m_shadowWidth);
        trianglePolygon << QPoint(m_triangleX + m_triangleWidth, m_triangleHeight + m_shadowWidth);

        drawPath.addRoundedRect(QRect(m_shadowWidth,
                                      m_triangleHeight + m_shadowWidth,
                                      width() - m_shadowWidth * 2,
                                      height() - m_shadowWidth * 2 - m_triangleHeight),
                                m_borderRadius, m_borderRadius);
    } else if (m_triangleDirection == 2) {
        trianglePolygon << QPoint(width() - m_shadowWidth - m_triangleHeight, m_triangleY);
        trianglePolygon << QPoint(width() - m_shadowWidth, m_triangleY + m_triangleWidth / 2);
        trianglePolygon << QPoint(width() - m_shadowWidth - m_triangleHeight, m_triangleY + m_triangleWidth);

        drawPath.addRoundedRect(QRect(m_shadowWidth,
                                      m_shadowWidth,
                                      width() - m_shadowWidth * 2 - m_triangleHeight,
                                      height() - m_shadowWidth * 2),
                                m_borderRadius, m_borderRadius);
    } else if (m_triangleDirection == 3) {
        trianglePolygon << QPoint(m_triangleX, height() - m_triangleHeight - m_shadowWidth);
        trianglePolygon << QPoint(m_triangleX + m_triangleWidth / 2, height() - m_triangleHeight);
        trianglePolygon << QPoint(m_triangleX + m_triangleWidth, height() - m_triangleHeight - m_shadowWidth);

        drawPath.addRoundedRect(QRect(m_shadowWidth,
                                      m_shadowWidth,
                                      width() - m_shadowWidth * 2,
                                      height() - m_shadowWidth * 2 - m_triangleHeight),
                                m_borderRadius, m_borderRadius);
    } else {
        trianglePolygon << QPoint(m_triangleHeight + m_shadowWidth, m_triangleY);
        trianglePolygon << QPoint(m_shadowWidth, m_triangleY + m_triangleWidth / 2);
        trianglePolygon << QPoint(m_triangleHeight + m_shadowWidth, m_triangleY + m_triangleWidth);

        drawPath.addRoundedRect(QRect(m_triangleHeight + m_shadowWidth,
                                      m_shadowWidth,
                                      width() - m_shadowWidth * 2 - m_triangleHeight,
                                      height() - m_shadowWidth * 2),
                                m_borderRadius, m_borderRadius);
    }

    // Rect + Triangle;
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}
