#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class CroppingPresenter : public Presenter {
public:
    explicit CroppingPresenter(IView* view, IRepository *repository);
    ~CroppingPresenter();
};