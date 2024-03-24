/*
 * @Author: weick
 * @Date: 2023-12-09 22:00:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 21:08:40
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../agui/inc/arotatingpixmapwidget.h"
#include "inc/conversionlistview.h"
#include "inc/models.h"
#include <QListWidget>
#include <QStyledItemDelegate>

namespace imageconversion {
class ConversionFormatPopup;
class ConversionWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit ConversionWindow(QWidget *parent = 0);
    ~ConversionWindow();
    void changeData(QList<Data> datas);
    void addFormatListWidgetItems(const QStringList items);
    void changeConvToBtnText(const QString format);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateCheckAllBtnState(bool checked);
    void updateBtnsEnabledByChangeData(QList<Data> datas);
    void formatPopup();
    void showConverting(bool isShow);
    void convStatus(Status state);
    void startConv();
    void finishedConv();
    void cancelConv();

private:
    ATopbar *m_Topbar = 0;
    ALabel *m_LogoLab = 0;
    ALabel *m_NameLab = 0;
    APushButton *m_SetingBtn = 0;
    ConversionListView *m_ConversionListView = 0;
    APushButton *m_AddGuideBtn = 0;
    APushButton *m_ConvToBtn = 0;
    APushButton *m_AddFileBtn = 0;
    APushButton *m_DelFileBtn = 0;
    APushButton *m_CheckAllBtn = 0;
    APushButton *m_ConvAllBtn = 0;
    AWidgetWithRotatingItem *m_ConvertingWidget = 0;
    ConversionFormatPopup *m_FormatPopup = 0;
};

class ConversionFormatPopup : public ABaseWidget {
    Q_OBJECT
public:
    explicit ConversionFormatPopup(QWidget *parent = 0);
    void addFormatListWidgetItems(const QStringList items);

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    void formatItemClicked(QListWidgetItem *item);

private:
    QListWidget *m_FormatListWidget = 0;
};

class ConversionFormatListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionFormatListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
} // namespace imageconversion