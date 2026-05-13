#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg);
    const char* what() const noexcept override;
};

class LogicException : public GameException {
public:
    explicit LogicException(const std::string& msg);
};

#endif
