#pragma once

#include"rv_pch.hpp"

#include"core/mat.h"

enum EventType : unsigned char
{
    EventTypeWindowClose = 0, EventTypeWindowResize,
    EventTypeMouseMoved
};

class Event
{
public:
    Event() = delete;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    virtual ~Event() = default;

    virtual std::string getName() = 0;

    EventType m_Type;
protected:
    Event(EventType type)
        : m_Type(type)
    {
    }
};

class EventWindowClose : public Event
{
public:
    EventWindowClose()
        :   Event(EventTypeWindowClose)
    {}
    virtual ~EventWindowClose() = default;

    virtual std::string getName() override { return "EventWindowClose"; }
};

class EventWindowResize : public Event
{
public:
    EventWindowResize(int width, int height)
        :   Event(EventTypeWindowResize), m_Width(width), m_Height(height)
    {}
    virtual ~EventWindowResize() = default;

    int m_Width;
    int m_Height;

    virtual std::string getName() override { return "EventWindowResize"; }
};

class EventMouseMoved : public Event
{
public:
    EventMouseMoved(const Vec2f& position)
        : Event(EventTypeMouseMoved), m_Position(position)
    {}

    virtual std::string getName() override { return "EventMouseMoved"; }
    Vec2f m_Position;
};