#include <memory>

enum EventType{
    EVENT_ACCEPT,
    EVENT_CLOSE,
    EVENT_READ,
    EVENT_WRITE,
    EVENT_ERROR
};

class Handle{
    public:
                
};

class EventHandler{
    public:
        void virtual handleEvent(EventType type) = 0;
        std::shared_ptr<Handle> virtual getHandle() const = 0;
};
