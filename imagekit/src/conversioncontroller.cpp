/*
 * @Author: weick
 * @Date: 2023-12-21 23:57:42
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 21:21:43
 */

#include "inc/conversioncontroller.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "../acore/inc/afoldermgr.h"
#include "../acore/inc/afilemgr.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <Magick++.h>

using namespace Magick;

namespace imageconversion {
ConversionController::ConversionController() {
    m_ConversionWindow = new ConversionWindow;
    init();
    sigConnect();
}

ConversionController::~ConversionController() {
}

void ConversionController::showWindow() {
    m_ConversionWindow->show();
}

void ConversionController::closeWindow() {
    m_ConversionWindow->close();
}

void ConversionController::init() {
    AFolderMgr::addFolder(SETTINGS->conversionOutPath());
    QString formats = CONV_OUT_FORMATS;
    m_FormatDatas = formats.split(' ');
    m_ConversionWindow->addFormatListWidgetItems(m_FormatDatas);
}

void ConversionController::sigConnect() {
    connect(SIGNALS, &Signals::sigOpenFileDialog, this, &ConversionController::openConvFileDialog);
    connect(SIGNALS, &Signals::sigDeleteFile, this, &ConversionController::delConvData);
    connect(SIGNALS, &Signals::sigStatus, this, &ConversionController::convStatus);
    connect(SIGNALS, &Signals::sigSwitchChecked, this, &ConversionController::switchChecked);
    connect(SIGNALS, &Signals::sigCheckedAll, this, &ConversionController::allChecked);
    connect(SIGNALS, &Signals::sigDeleteByChecked, this, &ConversionController::delByChecked);
    connect(SIGNALS, &Signals::sigChangeFormat, this, &ConversionController::changeConvFormat);

    connect(&m_ConvWatcher, &QFutureWatcher<void>::finished, this, [=]() {
        emit SIGNALS->sigStatus2View(Status::FINISHED);
    });
}

void ConversionController::openConvFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addConvData(selectedFiles);
    }
}

void ConversionController::addConvData(const QStringList filePaths) {
    for (const QString &filePath : filePaths) {
        Data conversionData;
        conversionData.file_path = filePath;
        conversionData.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/agui/res/image/checked1-24.png");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/agui/res/image/unchecked1-24.png");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.unchecked_icon = unCheckedIcon;
        conversionData.is_checked = true;
        m_ConvDatas.append(conversionData);
    }
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::delConvData(const QString filePath) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    m_ConvDatas.erase(std::remove_if(m_ConvDatas.begin(), m_ConvDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), m_ConvDatas.end());
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::convStatus(Status state) {
    switch (state) {
    case Status::NONE:
        break;
    case Status::START:
        startConv();
        break;
    case Status::FINISHED:
        finishedConv();
        break;
    case Status::CANCEL:
        cancelConv();
        break;
    }
}

void ConversionController::startConv() {
    auto task = [&]() {
        Image image;
        QString filePath;
        QFileInfo fileInfo;
        foreach (const auto &data, m_ConvDatas) {
            fileInfo = AFileMgr::fileInfo(data.file_path);
            if (fileInfo.exists() && data.is_checked) {
                filePath = AFileMgr::joinPathAndFileName(SETTINGS->conversionOutPath(), QString("%1.%2").arg(fileInfo.baseName()).arg(SETTINGS->conversionOutFormat()));
                AFileMgr::renameIfExists(filePath);
                image.read(data.file_path.toStdString());
                image.write(filePath.toStdString());
            }
        }
    };
    m_ConvWatcher.setFuture(QtConcurrent::run(task));
}

void ConversionController::finishedConv() {
}

void ConversionController::cancelConv() {
}

void ConversionController::switchChecked(const QString filePath, const bool checked) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_ConvDatas.begin(), m_ConvDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath));
    if (it != m_ConvDatas.end()) {
        it->is_checked = !it->is_checked;
    }
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::allChecked(bool checked) {
    for (auto &data : m_ConvDatas) {
        data.is_checked = checked;
    }
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::delByChecked() {
    m_ConvDatas.erase(std::remove_if(m_ConvDatas.begin(), m_ConvDatas.end(), [](const Data &cd) {
                          return cd.is_checked == true;
                      }),
                      m_ConvDatas.end());
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::changeConvFormat(const QString format) {
    SETTINGS->setConversionOutFormat(format);
    m_ConversionWindow->changeConvToBtnText(SETTINGS->conversionOutFormat());
}
} // namespace imageconversion