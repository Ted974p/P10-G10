#pragma once

class IActivable
{
public:
    virtual ~IActivable() = default;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual bool IsActive() const = 0;
};
