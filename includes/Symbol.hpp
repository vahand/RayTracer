/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Symbol
*/

#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

#include <memory>
#include <exception>
#include <iostream>
#include <dlfcn.h>

template <class T> class Symbol {
    public:
        class SymbolException : public std::exception {
            public:
                SymbolException() : _error(dlerror()) {}
                const char * what(void) const throw() final {
                    return this->_error.c_str();
                }

            private:
                const std::string _error;
        };

        Symbol() {}
        Symbol(std::shared_ptr<void> &handler, const char *symbol)
        {
            this->_handle = handler;
            this->_name = symbol;
            void *func_ptr = dlsym(this->_handle.get(), symbol);
            if (func_ptr == nullptr)
                throw SymbolException();
            T *(*func_ptr_casted)() = reinterpret_cast<T *(*)()>(func_ptr);
            this->_symbol = std::unique_ptr<T>(func_ptr_casted());
            if (this->_symbol == nullptr)
                throw SymbolException();
        }
        Symbol(Symbol<T> &&other)
        {
            this->_name = other._name;
            this->_symbol = std::move(other._symbol);
            this->_handle = other._handle;
        }
        Symbol(Symbol<T> &) = delete;
        Symbol(const Symbol<T> &) = delete;
        ~Symbol() {}

        std::unique_ptr<T> &getSymbol() { return this->_symbol; }

        Symbol<T>& operator=(Symbol<T> &) = delete;
        Symbol<T>& operator=(Symbol<T>&& other)
        {
            if (this != &other) {
                this->_name = other._name;
                this->_symbol = std::move(other._symbol);
                this->_handle = other._handle;
            }
            return *this;
        }
        Symbol<T>& operator=(const Symbol<T> &) = delete;

    protected:
    private:
        std::string _name;
        std::shared_ptr<void> _handle;
        std::unique_ptr<T> _symbol;
};

#endif /* !SYMBOL_HPP_ */
