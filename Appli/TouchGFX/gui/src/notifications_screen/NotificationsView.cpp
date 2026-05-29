#include <gui/notifications_screen/NotificationsView.hpp>
#include <cstring>

// Static storage
NotificationsView::Notification NotificationsView::notifications[NotificationsView::MAX_NOTIFICATIONS] = {};
int NotificationsView::notificationCount = 0;

NotificationsView::NotificationsView()
{
}

void NotificationsView::setupScreen()
{
    NotificationsViewBase::setupScreen();

    // Seed demo notifications on first entry (remove when real data arrives)
    if (notificationCount == 0)
    {
        addNotification(1, "Open Circuit");
        addNotification(0, "Power Loss");
        addNotification(1, "Overheating");
    }

    scrollList1.setNumberOfItems(notificationCount);
    scrollList1.invalidate();
}

void NotificationsView::tearDownScreen()
{
    NotificationsViewBase::tearDownScreen();
}

void NotificationsView::addNotification(int type, const char* msg)
{
    // Insert at the front (newest first); shift older down.
    int last = (notificationCount < MAX_NOTIFICATIONS) ? notificationCount : (MAX_NOTIFICATIONS - 1);
    for (int i = last; i > 0; --i)
    {
        notifications[i] = notifications[i - 1];
    }
    notifications[0].used = true;
    notifications[0].type = type;
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

void NotificationsView::scrollList1UpdateItem(CustomContainer8& item, int16_t itemIndex)
{
    if (itemIndex >= 0 && itemIndex < notificationCount && notifications[itemIndex].used)
    {
        item.setData(notifications[itemIndex].type, notifications[itemIndex].message);
    }
    else
    {
        item.setData(0, "");
    }
}
