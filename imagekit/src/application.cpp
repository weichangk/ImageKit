#include "inc/application.h"
#include "inc/startupwindow.h"


Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{
    // setOrganizationName(ORGANIZATION_NAME);
    // setOrganizationDomain(ORGANIZATION_DOMAIN);
    // setApplicationName(APPLICATION_NAME);
    // setApplicationDisplayName(APPLICATION_DISPLAY_NAME);

    // setQuitOnLastWindowClosed(false);

    initUi();
}

void Application::initUi()
{
    // UseHighDpiPixmaps is default from Qt6
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    // QString icoLocalPath = QCoreApplication::applicationDirPath() + '/' + QStringLiteral(PROJECT_ICON_NAME);
    // QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH);

    // // Try first to find the app icon in the current/build directory
    // appIcon_ = QIcon(icoLocalPath);
    // if (appIcon_.isNull())
    //     appIcon_ = QIcon(icoSysPath);

    m_Settings.load();

    m_StartupWindow = new StartupWindow;
    // m_StartupWindow->setWindowIcon(appIcon_);
    // m_StartupWindow->setWindowTitle(applicationDisplayName());
    m_StartupWindow->show(); // FIXME: crash without this

    // trayIcon_->setIcon(appIcon_);
    // trayIcon_->setWidget(mainWindow_);

    // connect(this, &QApplication::aboutToQuit, trayIcon_, &QObject::deleteLater);
    // connect(this, &QApplication::aboutToQuit, mainWindow_, &QObject::deleteLater);
    // connect(this, &QApplication::aboutToQuit, this, [this]() {
    //     mainWindow_->saveSettings();
    //     m_Settings.save();
    // });
}

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    return app.exec();
}
