#include "enhancement/repository.h"

#include <QCoreApplication>

EnhancementRepository::EnhancementRepository() {
}

EnhancementRepository::~EnhancementRepository() {
}

QList<SEnhanceModelData> EnhancementRepository::getModelDatas() {
    QList<SEnhanceModelData> datas;
    return datas;
}

QString EnhancementRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString EnhancementRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}