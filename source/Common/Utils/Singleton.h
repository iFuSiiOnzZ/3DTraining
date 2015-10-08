#pragma once
#include <assert.h>

template <typename T> class CSingleton
{
    protected:

        static T* ms_Singleton; 

    public:
        CSingleton(void)
        {
            assert(!ms_Singleton);
            ms_Singleton = static_cast< T* >(this);
        }

        virtual ~CSingleton(void)
        {
            assert(ms_Singleton);  ms_Singleton = 0;
        }

        static T& GetSingleton(void)
        {
            assert(ms_Singleton);
            return *ms_Singleton;
        }

        static T* GetSingletonPtr(void)
        {
            return ms_Singleton;
        }
};

template<typename T> T* CSingleton<T>::ms_Singleton = 0;
