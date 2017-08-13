#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define INDEXOUTOFBOUNDSEXCEPTION_H

#include <exception>

namespace hba {

    class IndexOutOfBoundsException
    {
    private:
        const char* message = nullptr;
    public:
        IndexOutOfBoundsException() {}
        IndexOutOfBoundsException(const char* mesg) {message = mesg;}

        virtual const char* what() const throw() {
            return message;
        }

    };

}

#endif // INDEXOUTOFBOUNDSEXCEPTION_H
