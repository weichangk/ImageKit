#include "enhancement/view.h"
#include "enhancement/presenter.h"
#include "settings.h"

EnhancementView::EnhancementView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *EnhancementView::getImportListView() {
    return m_pImportListView;
}

void EnhancementView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void EnhancementView::createUi() {
    setObjectName("EnhancementView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("EnhancementView_m_pTitleLbl");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setContentsMargins(20, 20, 20, 20);
    importGuideLayout->setSpacing(0);

    m_pImportGuide = new ImportGuide(this);

    m_pSmapleWidget = new QWidget(this);
    m_pSmapleWidget->setFixedHeight(100);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setAlignment(Qt::AlignCenter);

    m_pSmaple1ImageLbl = new ClickableLabel(this);
    m_pSmaple1ImageLbl->setFixedSize(128, 72);
    m_pSmaple2ImageLbl = new ClickableLabel(this);
    m_pSmaple2ImageLbl->setFixedSize(128, 72);

    auto sampleImageLayout = new QHBoxLayout();
    sampleImageLayout->setContentsMargins(0, 0, 0, 0);
    sampleImageLayout->setSpacing(14);
    sampleImageLayout->addStretch();
    sampleImageLayout->addWidget(m_pSmaple1ImageLbl);
    sampleImageLayout->addWidget(m_pSmaple2ImageLbl);
    sampleImageLayout->addStretch();

    smapleWidgetLayout->addWidget(m_pSmapleTitleLbl);
    smapleWidgetLayout->addLayout(sampleImageLayout);

    importGuideLayout->addWidget(m_pImportGuide, 1);
    importGuideLayout->addSpacing(14);
    importGuideLayout->addWidget(m_pSmapleWidget);

    //
    m_pWorkspaceWidget = new QWidget(this);
    auto bodyWidgetLayout = new QHBoxLayout(m_pWorkspaceWidget);
    bodyWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bodyWidgetLayout->setSpacing(0);

    m_pLeftWidget = new QWidget(this);
    auto LeftWidgetLayout = new QVBoxLayout(m_pLeftWidget);
    LeftWidgetLayout->setContentsMargins(0, 0, 0, 0);
    LeftWidgetLayout->setSpacing(0);

    m_pRightWidget = new QWidget(this);
    m_pRightWidget->setFixedWidth(320);
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(0, 0, 0, 0);
    rightWidgetLayout->setSpacing(0);

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    //
    m_pImageViewer = new ImageViewer(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    m_pChooseModelLbl = new QLabel(this);
    m_pChooseModelLbl->setObjectName("EnhancementView_m_pChooseModelLbl");
    m_pChooseModelLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_pModelListView = new ListView<SEnhanceModelData>(this);
    m_pModelListView->setFixedHeight(360);
    m_pModelListView->setSpacing(8);
    m_pModelListDelegate = new EnhanceModelListDelegate(m_pModelListView);
    m_pModelListView->setItemDelegate(m_pModelListDelegate);
    m_pModelListView->viewport()->installEventFilter(m_pModelListDelegate);

    auto settingWidget = new QWidget(this);
    auto settingLWidget = new QWidget(this);
    auto settingRWidget = new QWidget(this);
    auto settingWidgetLayout = new QHBoxLayout(settingWidget);
    settingWidgetLayout->setContentsMargins(8, 8, 20, 0);
    settingWidgetLayout->setSpacing(8);
    settingWidgetLayout->addWidget(settingLWidget, 1);
    settingWidgetLayout->addWidget(settingRWidget, 1);

    auto settingLWidgetLayout = new QVBoxLayout(settingLWidget);
    settingLWidgetLayout->setContentsMargins(0, 0, 0, 0);
    settingLWidgetLayout->setSpacing(0);

    auto settingRWidgetLayout = new QVBoxLayout(settingRWidget);
    settingRWidgetLayout->setContentsMargins(0, 0, 0, 0);
    settingRWidgetLayout->setSpacing(0);

    m_pUpscaleLbl = new QLabel(this);
    m_pUpscaleLbl->setObjectName("EnhancementView_m_pUpscaleLbl");
    m_pUpscaleLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pUpscaleCbb = new QComboBox(this);
    m_pUpscaleCbb->setFixedHeight(32);
    m_pUpscaleCbbFilter = new ComboBoxFilter(m_pUpscaleCbb);
    m_pUpscaleCbb->installEventFilter(m_pUpscaleCbbFilter);

    settingLWidgetLayout->addWidget(m_pUpscaleLbl);
    settingLWidgetLayout->addSpacing(4);
    settingLWidgetLayout->addWidget(m_pUpscaleCbb);

    m_pCustomOutputWidthCkb = new QCheckBox(this);
    m_pCustomOutputWidthLdt = new QLineEdit(this);
    settingRWidgetLayout->addWidget(m_pCustomOutputWidthCkb);
    settingRWidgetLayout->addSpacing(4);
    settingRWidgetLayout->addWidget(m_pCustomOutputWidthLdt);

    m_pCompressionLbl = new QLabel(this);
    m_pCompressionCbb = new QComboBox(this);
    settingLWidgetLayout->addSpacing(8);
    settingLWidgetLayout->addWidget(m_pCompressionLbl);
    settingLWidgetLayout->addSpacing(4);
    settingLWidgetLayout->addWidget(m_pCompressionCbb);

    m_pSaveAsFormatLbl = new QLabel(this);
    m_pSaveAsFormatCbb = new QComboBox(this);
    settingRWidgetLayout->addSpacing(8);
    settingRWidgetLayout->addWidget(m_pSaveAsFormatLbl);
    settingRWidgetLayout->addSpacing(4);
    settingRWidgetLayout->addWidget(m_pSaveAsFormatCbb);

    settingLWidgetLayout->addStretch();
    settingRWidgetLayout->addStretch();

    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("EnhancementView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("EnhancementView_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_file.png");

    auto outputFolderLayout = new QHBoxLayout();
    outputFolderLayout->setContentsMargins(0, 0, 0, 0);
    outputFolderLayout->setSpacing(0);

    outputFolderLayout->addWidget(m_pOutputFolderLbl);
    outputFolderLayout->addWidget(m_pOutputFolderCbb, 1);
    outputFolderLayout->addStretch();
    outputFolderLayout->addWidget(m_pOpenOutputFolderBtn);

    rightWidgetLayout->addWidget(m_pChooseModelLbl);
    rightWidgetLayout->addWidget(m_pModelListView);
    rightWidgetLayout->addWidget(settingWidget);
    rightWidgetLayout->addStretch();
    rightWidgetLayout->addWidget(m_pExportBtn);
    rightWidgetLayout->addLayout(outputFolderLayout);

    //
    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pWorkspaceWidget);

    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    //
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addLayout(stackedMarginLayout, 1);
}

void EnhancementView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &EnhancementView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &EnhancementView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &EnhancementView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &EnhancementView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &EnhancementView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &EnhancementView::onGuideImportFile);
    connect(m_pModelListView, &AbstractListView::sigCurrentChanged, this, &EnhancementView::ondModelListViewCurrentChanged);
    connect(m_pExportBtn, &QPushButton::clicked, this, &EnhancementView::onExportBtnClicked);
}

void EnhancementView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
        loadModelList();
        initUpscaleCbbItem();
        initCompressionCbbItem();
        initSaveAsFormatCbbItem();
    }
}

void EnhancementView::loadSampleImage() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EnhancementView::importSampleImage1() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void EnhancementView::importSampleImage2() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void EnhancementView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->enhanceOutPath());
}

void EnhancementView::loadModelList() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pModelListView->changeData(prst->getModelDatas());
    setModelListCurrentIndex(0);
}

void EnhancementView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void EnhancementView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void EnhancementView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void EnhancementView::setModelListCurrentIndex(int index) {
    QModelIndex modelIndex = m_pModelListView->model()->index(index, 0);
    m_pModelListView->setCurrentIndex(modelIndex);
}

void EnhancementView::initUpscaleCbbItem() {
    QStringList texts;
    texts.append("1x");
    texts.append("2x");
    texts.append("4x");
    texts.append("8x");
    m_pUpscaleCbb->addItems(texts);
}

void EnhancementView::upscaleSettingVisible(bool visible) {
    m_pUpscaleLbl->setVisible(visible);
    m_pUpscaleCbb->setVisible(visible);
}

void EnhancementView::initCompressionCbbItem() {
    QStringList texts;
    texts.append("0%");
    texts.append("10%");
    texts.append("20%");
    texts.append("30%");
    texts.append("40%");
    texts.append("50%");
    texts.append("60%");
    texts.append("70%");
    texts.append("80%");
    texts.append("90%");
    texts.append("100%");
    m_pCompressionCbb->addItems(texts);
}

void EnhancementView::initSaveAsFormatCbbItem() {
    QStringList texts;
    texts.append("png");
    texts.append("jpg");
    texts.append("jpeg");
    texts.append("webp");
    m_pSaveAsFormatCbb->addItems(texts);
}

void EnhancementView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Ai Image Enhancer"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pChooseModelLbl->setText(tr("Choose AI Model"));
    m_pUpscaleLbl->setText(tr("Upscaler Setting"));
    m_pCustomOutputWidthCkb->setText(tr("Custom width"));
    m_pCompressionLbl->setText(tr("Compression"));
    m_pSaveAsFormatLbl->setText(tr("Save as format"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void EnhancementView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void EnhancementView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void EnhancementView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void EnhancementView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void EnhancementView::onGuideImportFile(const QStringList &filePaths) {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}

void EnhancementView::ondModelListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto data = current.data(Qt::UserRole).value<SEnhanceModelData>();
    upscaleSettingVisible(data.id == 5);
}

void EnhancementView::onExportBtnClicked() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    prst->Enhancement();
}