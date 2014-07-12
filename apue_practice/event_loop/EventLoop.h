#include <unistd.h>
#include <memory>
#include <sys/epoll.h>

enum EventType{
    EVENT_ACCEPT,
    EVENT_CLOSE,
    EVENT_READ,
    EVENT_WRITE,
    EVENT_ERROR
};


class EventHandler{
    public:
        EventHandler(int sockfd, epoll_event event):sockfd_(sockfd), event_(event){}
        virtual ~EventHandler();
        void virtual handleEvent(EventType type) = 0;
        epoll_event getEvent() const{return event_;}

    private:
        int sockfd_;
        epoll_event event_;
};
