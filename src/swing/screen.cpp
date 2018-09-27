#include "screen.hpp"

void Screen::processEvent(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
            _widgetUnderCursor.reset();
            for (const auto& widget : _widgets) {
                if (widget->contains(event.motion.x, event.motion.y)) {
                    _widgetUnderCursor = widget;
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (_widgetUnderCursor.lock()) {
                _activeWidget = _widgetUnderCursor;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (!_activeWidget.expired() &&
                    _activeWidget.lock() == _widgetUnderCursor.lock()) {
                _activeWidget.lock()->perform();
            }
            _activeWidget.reset();
            break;
    }
}

void Screen::draw(SDL_Renderer* renderer) const
{
    auto active = _activeWidget.lock();
    auto underCursor = _widgetUnderCursor.lock();
    for (const auto& widget : _widgets) {
        if (_activeWidget.lock() == widget) {
            widget->draw(renderer, WidgetState::Active);
        } else if (_activeWidget.expired() && widget == underCursor) {
            widget->draw(renderer, WidgetState::Focused);
        } else {
            widget->draw(renderer, WidgetState::Passive);
        }
    }
}
