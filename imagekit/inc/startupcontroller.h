/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:29
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:44:46
 */

#pragma once
#include "startupwindow.h"
#include "models.h"
#include "conversioncontroller.h"
#include "compressioncontroller.h"
#include "editcontroller.h"
#include <QObject>

class StartupController : public QObject {
    Q_OBJECT
public:
    explicit StartupController();
    ~StartupController();
    void showFunc(ImageFunc func);

private:
    void sigConnect();

private:
    StartupWindow *m_StartupWindow = 0;
    ConversionController *m_ConversionController = 0;
    imagecompression::CompressionController *compression_controller_ = nullptr;
    imageedit::EditController *edit_controller_ = nullptr;
};
