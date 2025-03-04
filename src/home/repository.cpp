#include "home/repository.h"

HomeRepository::HomeRepository() {
}

HomeRepository::~HomeRepository() {
}

QList<SFuncItemData> HomeRepository::datas() {
    return {
        SFuncItemData{
            EFunc::FuncConversion,
            EFuncItemBtnType::AddFile,
            "Image Converter",
            "Convert images to other formats.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncCompression,
            EFuncItemBtnType::AddFile,
            "Background Remover",
            "Automatically remove backgrounds from images.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/Compress.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncGifMaker,
            EFuncItemBtnType::AddFile,
            "GIF Maker",
            "Create a GIF from multiple images.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/Gifmaker.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncCropping,
            EFuncItemBtnType::AddFile,
            "Image Crop",
            "Automatically crop image.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/SmartTrim.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncErase,
            EFuncItemBtnType::StartNow,
            "Watermark Remover",
            "Batch remove watermarks from images.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/AIRemoveWatermark.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncEnhancement,
            EFuncItemBtnType::AddFile,
            "Image Enhancer",
            "Batch enhance images with AI for improved clarity and quality.",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/AIImageEnhance.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncInpainting,
            EFuncItemBtnType::AddFile,
            "功能1",
            "这是功能1的描述",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
        SFuncItemData{
            EFunc::FuncEffects,
            EFuncItemBtnType::AddFile,
            "功能1",
            "这是功能1的描述",
            "Start Now",
            "Add File(s)",
            false,
            false,
            QPixmap(":/qtmaterial/img/vcu/common/toolcovers/ImageConverter.png"),
            QPixmap(),
            QPixmap(),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_arrowright_white.svg"),
            QPixmap(":/qtmaterial/img/vcu/dark/icon24/icon24_add_white.svg"),
        },
    };
}
