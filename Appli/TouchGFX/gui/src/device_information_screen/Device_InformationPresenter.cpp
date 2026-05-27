#include <gui/device_information_screen/Device_InformationView.hpp>
#include <gui/device_information_screen/Device_InformationPresenter.hpp>

// Request device info from the backend over UART when this screen becomes active
#include "../../../Core/Inc/protocol.h"

Device_InformationPresenter::Device_InformationPresenter(Device_InformationView& v)
    : view(v)
{

}

void Device_InformationPresenter::activate()
{
    Protocol_RequestDeviceInfo();

}

void Device_InformationPresenter::deactivate()
{

}

void Device_InformationPresenter::notifyDeviceInfoChanged()
{
    view.updateDeviceInfo();
}
