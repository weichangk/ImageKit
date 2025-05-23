#include "funcarearepository.h"

FuncAreaRepository::FuncAreaRepository() {
    m_pHomeRepository = new HomeRepository();
    m_pMyFileRepository = new MyFileRepository();
    m_pCompressionRepository = new CompressionRepository();
    m_pConversionRepository = new ConversionRepository();
    m_pCroppingRepository = new CroppingRepository();
    m_pEffectsRepository = new EffectsRepository();
    m_pEnhancementRepository = new EnhancementRepository();
    m_pEraseRepository = new EraseRepository();
    m_pGifGenerationRepository = new GifGenerationRepository();
    m_pInpaintingRepository = new InpaintingRepository();
    m_pBackgroungRemoverRepository = new BackgroungRemoverRepository();
    m_pThumbnailMakerRepository = new ThumbnailMakerRepository();
    m_pDownloaderRepository = new DownloaderRepository();
    m_pGifPreviewRepository = new GifPreviewRepository();
}

FuncAreaRepository::~FuncAreaRepository() {
}

HomeRepository *FuncAreaRepository::homeRepository() const {
    return m_pHomeRepository;
}

MyFileRepository *FuncAreaRepository::myFileRepository() const {
    return m_pMyFileRepository;
}

CompressionRepository *FuncAreaRepository::compressionRepository() const {
    return m_pCompressionRepository;
}

ConversionRepository *FuncAreaRepository::conversionRepository() const {
    return m_pConversionRepository;
}

CroppingRepository *FuncAreaRepository::croppingRepository() const {
    return m_pCroppingRepository;
}

EffectsRepository *FuncAreaRepository::effectsRepository() const {
    return m_pEffectsRepository;
}

EnhancementRepository *FuncAreaRepository::enhancementRepository() const {
    return m_pEnhancementRepository;
}

EraseRepository *FuncAreaRepository::eraseRepository() const {
    return m_pEraseRepository;
}

GifGenerationRepository *FuncAreaRepository::gifGenerationRepository() const {
    return m_pGifGenerationRepository;
}

InpaintingRepository *FuncAreaRepository::inpaintingRepository() const {
    return m_pInpaintingRepository;
}

BackgroungRemoverRepository *FuncAreaRepository::backgroungRemoverRepository() const {
    return m_pBackgroungRemoverRepository;
}

ThumbnailMakerRepository *FuncAreaRepository::thumbnailMakerRepository() const {
    return m_pThumbnailMakerRepository;
}

DownloaderRepository *FuncAreaRepository::downloaderRepository() const {
    return m_pDownloaderRepository;
}

GifPreviewRepository *FuncAreaRepository::gifPreviewRepository() const {
    return m_pGifPreviewRepository;
}
