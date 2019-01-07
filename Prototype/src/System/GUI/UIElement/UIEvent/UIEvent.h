#pragma once
#include <string>

//UIEvents are sent to action listeners to communicate data
class UIEvent {
public:
    UIEvent(std::string _message = "");
    ~UIEvent();

    inline std::string getMessage() const { return message; }
private:
    const std::string message;
};