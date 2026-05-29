#ifndef NOTIFICATIONSVIEW_HPP
#define NOTIFICATIONSVIEW_HPP

#include <gui_generated/notifications_screen/NotificationsViewBase.hpp>
#include <gui/notifications_screen/NotificationsPresenter.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/events/GestureEvent.hpp>
#include <touchgfx/events/DragEvent.hpp>
#include <touchgfx/events/ClickEvent.hpp>

class NotificationsView : public NotificationsViewBase
{
public:
    static const int MAX_NOTIFICATIONS = 16;
    static const int MSG_BUF_SIZE = 64;

    struct Notification
    {
        bool used;
        bool isAlert;          // true = alert (orange), false = warning (red)
        char message[MSG_BUF_SIZE];
    };

    NotificationsView();
    virtual ~NotificationsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleDragEvent(const touchgfx::DragEvent& event);

    // Public API for adding notifications from anywhere (newest first).
    static void addNotification(bool isAlert, const char* msg);
    static int  getCount();

protected:
    static Notification notifications[MAX_NOTIFICATIONS];
    static int notificationCount;

    int scrollOffset;

    touchgfx::Unicode::UnicodeChar slot1Buffer[MSG_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar slot2Buffer[MSG_BUF_SIZE];

    // Drag tracking for vertical scroll
    int16_t dragStartY;
    int16_t lastDragY;
    bool    dragging;

    void updateDisplay();
};

#endif // NOTIFICATIONSVIEW_HPP
