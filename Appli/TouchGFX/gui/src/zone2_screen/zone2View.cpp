#include <gui/zone2_screen/zone2View.hpp>
#include <gui/model/Model.hpp>

zone2View::zone2View()
{

}

void zone2View::setupScreen()
{
    zone2ViewBase::setupScreen();

    int zone = presenter->getSelectedZone();
    int volume = presenter->getZoneVolume(zone);

    slider1.setValue(volume);

    // Workaround: textArea1 is a TextArea, not TextAreaWithOneWildcard.
    // To show the zone name, you must use setTypedText with a pre-defined TypedText,
    // or change the UI to use TextAreaWithOneWildcard for dynamic names.
    // For now, this will just keep the default text.
    // TODO: Update UI to use TextAreaWithOneWildcard for dynamic zone names.
    textArea1.invalidate();
}

void zone2View::tearDownScreen()
{
    zone2ViewBase::tearDownScreen();
}

void zone2View::volumeChanged(int value)
{
    int zone = presenter->getSelectedZone();
    presenter->setZoneVolume(zone, value);
}
