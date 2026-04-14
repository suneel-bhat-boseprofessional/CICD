#include <gui/brightness_screen/BrightnessView.hpp>
#include <gui/brightness_screen/BrightnessPresenter.hpp>
#include <gui/model/Model.hpp>

BrightnessPresenter::BrightnessPresenter(BrightnessView& v)
    : view(v)
{

}

void BrightnessPresenter::activate()
{

}

void BrightnessPresenter::deactivate()
{

}

int BrightnessPresenter::getBrightness() const
{
    return model->getLcdBrightness();
}

void BrightnessPresenter::setBrightness(int value)
{
    model->setLcdBrightness(value);
}
