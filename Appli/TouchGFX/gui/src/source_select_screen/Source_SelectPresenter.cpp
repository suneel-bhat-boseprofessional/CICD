#include <gui/source_select_screen/Source_SelectView.hpp>
#include <gui/source_select_screen/Source_SelectPresenter.hpp>
#include <gui/model/Model.hpp>

Source_SelectPresenter::Source_SelectPresenter(Source_SelectView& v)
    : view(v)
{
}

void Source_SelectPresenter::activate()
{
}

void Source_SelectPresenter::deactivate()
{
}

int Source_SelectPresenter::getSelectedZone()
{
    return model->getSelectedZone();
}

int Source_SelectPresenter::getSourceCount()
{
    return model->getZoneSourceCount(model->getSelectedZone());
}

const char* Source_SelectPresenter::getSourceName(int srcIdx)
{
    return model->getZoneSourceName(model->getSelectedZone(), srcIdx);
}

int Source_SelectPresenter::getSelectedSource()
{
    return model->getSelectedSource(model->getSelectedZone());
}

void Source_SelectPresenter::setSelectedSource(int srcIdx)
{
    model->setSelectedSource(model->getSelectedZone(), srcIdx);
}

void Source_SelectPresenter::zoneNamesUpdated()
{
    view.sourcesUpdated();
}
