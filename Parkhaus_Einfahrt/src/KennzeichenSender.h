#pragma once
#include <string>


class IKennzeichenSender {
public:
    virtual ~IKennzeichenSender() = default;
    virtual void sende(const std::string& kennzeichen) = 0;
};

