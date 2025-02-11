#include "compression/presenter.h"
#include "compression/repository.h"

#include <QFileInfo>

CompressionPresenter::CompressionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

CompressionPresenter::~CompressionPresenter() {
}

QList<SCompressionData> CompressionPresenter::datas() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    return rep->datas();
}

void CompressionPresenter::appendData(const QStringList filePaths) {
    QList<SCompressionData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SCompressionData data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(200 + 8 - 4 - 12, 200 + 8 - 24 - 12), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/icon16_close");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/icon16_checkbox_checked");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/icon16_checkbox_checked");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.unchecked_icon = unCheckedIcon;
        data.is_checked = true;
        tempDatas.append(data);
    }
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->appendData(tempDatas);
}

void CompressionPresenter::deleteData(const QStringList filePaths) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->deleteData(filePaths);
    for (auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void CompressionPresenter::deleteCheckedData() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->deleteCheckedData();
    for (auto data : rep->datas()) {
        if (data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void CompressionPresenter::clearData() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void CompressionPresenter::switchCheckedData(const QString filePath) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void CompressionPresenter::checkedAllData(bool checked) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->checkedAllData(checked);
}