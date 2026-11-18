#pragma once


class ISchranke {
public:
    virtual ~ISchranke() = default;
    virtual void öffnen() = 0;
    virtual void schliessen() = 0;
};
