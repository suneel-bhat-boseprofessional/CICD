#include <gui/notifications_screen/NotificationsView.hpp>
#include <cstring>

// Static storage
NotificationsView::Notification NotificationsView::notifications[NotificationsView::MAX_NOTIFICATIONS] = {};
int NotificationsView::notificationCount = 0;

NotificationsView::NotificationsView() :
    scrollOffset(0),
    dragStartY(0),
    lastDragY(0),
    dragging(false)
{
}

void NotificationsView::setupScreen()
{
    NotificationsViewBase::setupScreen();

    // Seed a few demo notifications on first entry so the screen is testable.
    // Remove this block if notifications come from elsewhere.
    if (notificationCount == 0)
    {
        addNotification(true,  "Open Circuit");
        addNotification(false, "Power Loss");
    }

    scrollOffset = 0;
    updateDisplay();
}

void NotificationsView::tearDownScreen()
{
    NotificationsViewBase::tearDownScreen();
}

void NotificationsView::addNotification(bool isAlert, const char* msg)
{
    // Insert at the front (newest first); shift older down.
    int last = (notificationCount < MAX_NOTIFICATIONS) ? notificationCount : (MAX_NOTIFICATIONS - 1);
    for (int i = last; i > 0; --i)
    {
        notifications[i] = notifications[i - 1];
    }
    notifications[0].used = true;
    notifications[0].isAlert = isAlert;
    std::strncpy(notifications[0].message, msg ? msg : "", MSG_BUF_SIZE - 1);
    notifications[0].message[MSG_BUF_SIZE - 1] = '\0';
    if (notificationCount < MAX_NOTIFICATIONS)
    {
        notificationCount++;
    }
}

int NotificationsView::getCount()
{
    return notificationCount;
}

void NotificationsView::updateDisplay()
{
    // Slot 1 shows notifications[scrollOffset]
    // Slot 2 shows notifications[scrollOffset + 1]
    int idx1 = scrollOffset;
    int idx2 = scrollOffset + 1;

    // ---- Slot 1 ----
    if (idx1 >= 0 && idx1 < notificationCount && notifications[idx1].used)
    {
        const Notification& n = notifications[idx1];
        touchgfx::Unicode::strncpy(slot1Buffer, n.message, MSG_BUF_SIZE);

        if (n.isAlert)
        {
            Alert1.setVisible(true);
            Alert_1.setVisible(true);
            Alert_1.setWildcard(slot1Buffer);
            Warning1.setVisible(false);
            Warning_1.setVisible(false);
        }
        else
        {
            Warning1.setVisible(true);
            Warning_1.setVisible(true);
            Warning_1.setWildcard(slot1Buffer);
            Alert1.setVisible(false);
            Alert_1.setVisible(false);
        }
        image2.setVisible(true);
    }
    else
    {
        Alert1.setVisible(false);
        Alert_1.setVisible(false);
        Warning1.setVisible(false);
        Warning_1.setVisible(false);
        image2.setVisible(false);
    }

    // ---- Slot 2 ----
    if (idx2 >= 0 && idx2 < notificationCount && notifications[idx2].used)
    {
        const Notification& n = notifications[idx2];
        touchgfx::Unicode::strncpy(slot2Buffer, n.message, MSG_BUF_SIZE);

        if (n.isAlert)
        {
            Alert2.setVisible(true);
            Alert_2.setVisible(true);
            Alert_2.setWildcard(slot2Buffer);
            Warning2.setVisible(false);
            Warning_2.setVisible(false);
        }
        else
        {
            Warning2.setVisible(true);
            Warning_2.setVisible(true);
            Warning_2.setWildcard(slot2Buffer);
            Alert2.setVisible(false);
            Alert_2.setVisible(false);
        }
        image3.setVisible(true);
    }
    else
    {
        Alert2.setVisible(false);
        Alert_2.setVisible(false);
        Warning2.setVisible(false);
        Warning_2.setVisible(false);
        image3.setVisible(false);
    }

    image2.invalidate();
    image3.invalidate();
    Alert1.invalidate();
    Alert2.invalidate();
    Warning1.invalidate();
    Warning2.invalidate();
    Alert_1.invalidate();
    Alert_2.invalidate();
    Warning_1.invalidate();
    Warning_2.invalidate();
}

void NotificationsView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        dragStartY = event.getY();
        lastDragY = event.getY();
        dragging = false;
    }
    NotificationsViewBase::handleClickEvent(event);
}

void NotificationsView::handleDragEvent(const touchgfx::DragEvent& event)
{
    dragging = true;
    int16_t y = event.getNewY();
    int16_t totalDelta = y - dragStartY;
    const int16_t SLOT_HEIGHT = 52; // ~distance between the two slots

    // Step the scroll offset each time we cross a slot height threshold.
    if (totalDelta <= -SLOT_HEIGHT)
    {
        // Dragged upward -> scroll to newer-older direction (show next entries)
        int maxOffset = (notificationCount > 2) ? (notificationCount - 2) : 0;
        if (scrollOffset < maxOffset)
        {
            scrollOffset++;
            updateDisplay();
        }
        dragStartY = y;
    }
    else if (totalDelta >= SLOT_HEIGHT)
    {
        // Dragged downward -> scroll back toward the top of the list
        if (scrollOffset > 0)
        {
            scrollOffset--;
            updateDisplay();
        }
        dragStartY = y;
    }
    NotificationsViewBase::handleDragEvent(event);
}

void NotificationsView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    if (event.getType() == touchgfx::GestureEvent::SWIPE_VERTICAL)
    {
        int maxOffset = (notificationCount > 2) ? (notificationCount - 2) : 0;
        if (event.getVelocity() < 0)
        {
            // swipe up -> show next item(s)
            if (scrollOffset < maxOffset)
            {
                scrollOffset++;
                updateDisplay();
            }
        }
        else if (event.getVelocity() > 0)
        {
            // swipe down -> show previous
            if (scrollOffset > 0)
            {
                scrollOffset--;
                updateDisplay();
            }
        }
    }
    NotificationsViewBase::handleGestureEvent(event);
}
