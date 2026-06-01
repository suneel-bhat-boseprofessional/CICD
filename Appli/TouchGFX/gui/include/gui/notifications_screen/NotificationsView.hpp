#ifndef NOTIFICATIONSVIEW_HPP
#define NOTIFICATIONSVIEW_HPP

#include <gui_generated/notifications_screen/NotificationsViewBase.hpp>
#include <gui/notifications_screen/NotificationsPresenter.hpp>
#include <touchgfx/Unicode.hpp>

class NotificationsView : public NotificationsViewBase
{
public:
    static const int MAX_NOTIFICATIONS = 16;
    static const int MSG_BUF_SIZE = 32;

    struct Notification
    {
        bool used;
        int  type;             // 1 = alert, 0 = warning
        char message[MSG_BUF_SIZE];
    };

    NotificationsView();
    virtual ~NotificationsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer8& item, int16_t itemIndex);

    // Public API for adding notifications (newest first).
    static void addNotification(int type, const char* msg);
    static int  getCount();

protected:
    static Notification notifications[MAX_NOTIFICATIONS];
    static int notificationCount;
};

#endif // NOTIFICATIONSVIEW_HPP
