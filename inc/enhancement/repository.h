#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "model.h"
#include "import/importlistrepository.h"

using namespace qtmaterialmvp;

class EnhancementRepository : public Repository {
public:
    explicit EnhancementRepository();
    ~EnhancementRepository();

    QList<SEnhanceModelData> getModelDatas();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;
};