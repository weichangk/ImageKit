/*
 * @Author: weick
 * @Date: 2023-12-05 23:05:54
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:05:54
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class QWidget;
class ATopbar;
class QTreeWidget;
class QStackedWidget;
class AComboBox;
class ATextEdit;
class QShortcut;
class MainWindow : public ABaseWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private slots:
    void slotLangComboxIndexChanged(int index);

private:
    void createTree();

private:
    ATopbar *m_topbar = nullptr;
    QTreeWidget *m_treeWidget = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
    AComboBox *langCombox = nullptr;

    ATextEdit *testTextEdit = nullptr;

    QShortcut *enterShortcut = nullptr;
};
