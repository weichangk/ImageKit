#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "core/font.h"
#include "core/object.h"
#include "filter/languagefilter.h"
#include "filter/comboboxfilter.h"
#include "importguide.h"
#include "model.h"
#include "listdelegate.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class CroppingView : public QWidget, public View {
    Q_OBJECT
public:
    explicit CroppingView(QWidget *parent = nullptr);
    ~CroppingView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();

private Q_SLOTS:
    void onLanguageChange();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;

    QWidget *m_pContentWidget = nullptr;

    IconButton *m_pAddFileBtn = nullptr;
    IconButton *m_pAddFolderBtn = nullptr;
    IconButton *m_pClearFileBtn = nullptr;
    QLabel *m_pOutputFormatLbl = nullptr;
    QLineEdit *m_pOutputFormatEdit = nullptr;
    QComboBox *m_pOutputFormatCbb = nullptr;
    ComboBoxFilter *m_pOutputFormatCbbFilter = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pStartAllBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ListView<SCroppingData> *m_pListView = nullptr;
    CroppingListDelegate *m_pListDelegate = nullptr;
};