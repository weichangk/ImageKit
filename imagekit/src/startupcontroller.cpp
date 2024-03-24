/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 12:50:08
 */

#include "inc/startupcontroller.h"
#include "inc/startupwindow.h"
#include "inc/signals.h"

StartupController::StartupController() {
    m_StartupWindow = new StartupWindow();
    m_ConversionController = new ConversionController();
    m_CompressionController = new CompressionController();
    edit_controller_ = new imageedit::EditController();
    sigConnect();
}

StartupController::~StartupController() {
}

void StartupController::showFunc(ImageFunc func) {
    switch (func) {
    case ImageFunc::STARTUP:
        m_StartupWindow->show();
        break;
    case ImageFunc::CONVERSION:
        m_StartupWindow->close();
        m_ConversionController->showWindow();
        break;
    case ImageFunc::COMPRESSION:
        m_StartupWindow->close();
        m_CompressionController->showWindow();
        break;
    case ImageFunc::EDIT:
        m_StartupWindow->close();
        edit_controller_->showWindow();
        break;
    default:
        break;
    }
}

void StartupController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigGotoFunc, this, &StartupController::showFunc);
}
