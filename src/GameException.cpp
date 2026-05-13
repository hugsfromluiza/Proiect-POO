#include "GameException.h"

GameException::GameException(const std::string& msg) : message(msg) {}

const char* GameException::what() const noexcept {
    return message.c_str();
}

LogicException::LogicException(const std::string& msg) : GameException("Logic Error: " + msg) {}
