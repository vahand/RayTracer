/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Loader
*/

#ifndef LOADER_HPP_
#define LOADER_HPP_

#include "Symbol.hpp"

class Loader {
    public:
        class LoaderException : public std::exception {
            public:
                LoaderException(std::string const &message) { _message = message;}
                const char *what() const noexcept override { return _message.c_str();}

            private:
                std::string _message;
        };
        Loader();
        Loader(std::string filename);
        ~Loader() {};

        // void *getHandle() const { return this->_handle.get(); }

        template <class T>
        Symbol<T> getInstance(const char *symbol)
        {
            return Symbol<T>(this->_handle, symbol);
        }

        template <class T>
        T call(const char *symbol)
        {
            void *func_ptr = dlsym(this->_handle.get(), symbol);
            if (func_ptr == nullptr)
                throw LoaderException(dlerror());
            T (*func_ptr_casted)() = reinterpret_cast<T (*)()>(func_ptr);
            return func_ptr_casted();
        }

        std::shared_ptr<void> _handle;
    protected:
    private:
};

#endif /* !LOADER_HPP_ */
