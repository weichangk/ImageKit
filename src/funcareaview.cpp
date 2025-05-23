#include "funcareaview.h"
#include "message/funcchangemessage.h"

FuncAreaView::FuncAreaView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

HomeView *FuncAreaView::homeView() const {
    return m_pHomeView;
}

MyFileView *FuncAreaView::myFileView() const {
    return m_pMyFileView;
}

CompressionView *FuncAreaView::compressionView() const {
    return m_pCompressionView;
}

ConversionView *FuncAreaView::conversionView() const {
    return m_pConversionView;
}

CroppingView *FuncAreaView::croppingView() const {
    return m_pCroppingView;
}

EffectsView *FuncAreaView::effectsView() const {
    return m_pEffectsView;
}

EnhancementView *FuncAreaView::enhancementView() const {
    return m_pEnhancementView;
}

EraseView *FuncAreaView::eraseView() const {
    return m_pEraseView;
}

GifGenerationView *FuncAreaView::gifGenerationView() const {
    return m_pGifGenerationView;
}

InpaintingView *FuncAreaView::inpaintingView() const {
    return m_pInpaintingView;
}

BackgroungRemoverView *FuncAreaView::backgroundRemoverView() const {
    return m_pBackgroundRemoverView;
}

ThumbnailMakerView *FuncAreaView::thumbnailMakerView() const {
    return m_pThumbnailMakerView;
}

DownloaderView *FuncAreaView::downloaderView() const {
    return m_pDownloaderView;
}

ImagePreviewView *FuncAreaView::imagePreviewView() const {
    return m_pImagePreviewView;
}

GifPreviewView *FuncAreaView::gifPreviewView() const {
    return m_pGifPreviewView;
}

void FuncAreaView::createUi() {
    setObjectName("FuncAreaView");
    setAttribute(Qt::WA_StyledBackground);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->setContentsMargins(0, 0, 0, 0);
    m_pStackedLayout->setSpacing(0);

    m_pHomeView = new HomeView(this);
    m_pMyFileView = new MyFileView(this);
    m_pCompressionView = new CompressionView(this);
    m_pConversionView = new ConversionView(this);
    m_pCroppingView = new CroppingView(this);
    m_pEffectsView = new EffectsView(this);
    m_pEnhancementView = new EnhancementView(this);
    m_pEraseView = new EraseView(this);
    m_pGifGenerationView = new GifGenerationView(this);
    m_pInpaintingView = new InpaintingView(this);
    m_pBackgroundRemoverView = new BackgroungRemoverView(this);
    m_pThumbnailMakerView = new ThumbnailMakerView(this);
    m_pDownloaderView = new DownloaderView(this);
    m_pImagePreviewView = new ImagePreviewView(this);
    m_pGifPreviewView = new GifPreviewView(this);

    m_pStackedLayout->insertWidget(EFunc::FuncHome, m_pHomeView);
    m_pStackedLayout->insertWidget(EFunc::FuncMyFile, m_pMyFileView);
    m_pStackedLayout->insertWidget(EFunc::FuncConversion, m_pConversionView);
    m_pStackedLayout->insertWidget(EFunc::FuncCompression, m_pCompressionView);
    m_pStackedLayout->insertWidget(EFunc::FuncEnhancement, m_pEnhancementView);
    m_pStackedLayout->insertWidget(EFunc::FuncErase, m_pEraseView);
    m_pStackedLayout->insertWidget(EFunc::FuncBackgroungRemover, m_pBackgroundRemoverView);
    m_pStackedLayout->insertWidget(EFunc::FuncCropping, m_pCroppingView);
    m_pStackedLayout->insertWidget(EFunc::FuncGifMaker, m_pGifGenerationView);
    m_pStackedLayout->insertWidget(EFunc::FuncThumbnailMaker, m_pThumbnailMakerView);
    m_pStackedLayout->insertWidget(EFunc::FuncDownloader, m_pDownloaderView);
    m_pStackedLayout->insertWidget(EFunc::FuncInpainting, m_pInpaintingView);
    m_pStackedLayout->insertWidget(EFunc::FuncEffects, m_pEffectsView);
    m_pStackedLayout->insertWidget(EFunc::FuncImagePreview, m_pImagePreviewView);
    m_pStackedLayout->insertWidget(EFunc::FuncGifPreview, m_pGifPreviewView);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addLayout(m_pStackedLayout);
}

void FuncAreaView::connectSig() {
}

void FuncAreaView::setCurrentFuncView(EFunc func) {
    m_pStackedLayout->setCurrentIndex(func);
}

bool FuncAreaView::handleMessage(IMessage* message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        EFunc ef = (EFunc)msg->code();
        // setCurrentFuncView(ef);
        std::function<void(EFunc)> func = [&](EFunc e) {
            setCurrentFuncView(e);
        };
        if (ef == EFunc::FuncUndo || ef == EFunc::FuncRedo) {
            ef == EFunc::FuncUndo ? m_rFuncNavigationHistory.undo() : m_rFuncNavigationHistory.redo();
        } else {
            m_ePreviousFunc = m_eCurrentFunc;
            m_eCurrentFunc = ef;
            if (m_ePreviousFunc != m_eCurrentFunc) {
                m_rFuncNavigationHistory.executeCommand(m_ePreviousFunc, ef, func);
            }
        }
    }
    return false;
}