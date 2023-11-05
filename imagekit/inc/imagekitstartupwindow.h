#pragma once
#include "imagekit_global.h"

class ATopbar;
class ACanMoveWidget;
class APushButton;
class ImageFuncView;
class ImageFuncModel;
class ImageFuncDelegate;
class ImageFunc;
class IMAGEKIT_EXPORT ImageKitStartupWindow : public ABaseWidget
{
    Q_OBJECT
public:
    ImageKitStartupWindow(QWidget *parent = nullptr);
    ~ImageKitStartupWindow();
    void imageFuncModelAppend(QList<ImageFunc *> funcs);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

    void paintEvent(QPaintEvent *event) override;

private:
    ATopbar * m_Topbar = nullptr;
    ACanMoveWidget * m_Navbar = nullptr;
    AWidget *m_FuncArea = nullptr;

    APushButton *m_LogoBtn = nullptr;
    APushButton *m_VipBtn = nullptr;
    APushButton *m_VipRightsBtn = nullptr;

    APushButton *m_FuncBtn = nullptr;
    APushButton *m_FilesBtn = nullptr;
    APushButton *m_SettingsBtn = nullptr;

    ImageFuncView *m_ImageFuncView = nullptr;
    ImageFuncModel *m_ImageFuncModel = nullptr;
    ImageFuncDelegate *m_ImageFuncDelegate = nullptr;
};
