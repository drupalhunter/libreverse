#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <ext/malloc_allocator.h>
#include <sys/mman.h>
#include <boost/cstdint.hpp>

namespace reverse { namespace data_types {

    template <typename DataType>
    class Memory_Allocator : public __gnu_cxx::malloc_allocator < DataType >
    {
    public:

        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef DataType* pointer;
        typedef const DataType* const_pointer;
        typedef DataType& reference;
        typedef const DataType& const_reference;
        typedef DataType value_type;

        template <typename U>
        struct rebind {
            typedef Memory_Allocator<U> other;
        };

        Memory_Allocator ( boost::int32_t prot = 0,
                           boost::int32_t flags = 0 )
            : __gnu_cxx::malloc_allocator<DataType>(),
              m_prot ( prot ),
              m_flags ( flags )
        {}

        Memory_Allocator ( const Memory_Allocator& rhs )
            : __gnu_cxx::malloc_allocator<DataType>(),
              m_prot ( rhs.m_prot ),
              m_flags ( rhs.m_flags )
        {}

        ~Memory_Allocator(){}

        pointer
        allocate ( size_type __n, const void* hint = 0 )
        {
            if ( __builtin_expect ( __n > this->max_size(), false ) )
                {
                    std::__throw_bad_alloc();
                }

            pointer __ret = static_cast<DataType*>
                ( mmap ( const_cast<void*>(hint),
                         __n * sizeof(DataType),
                         m_prot,
                         m_flags,
                         0,
                         0 ) );

            if (!__ret)
                {
                    std::__throw_bad_alloc();
                }

            return __ret;
        }

      // __p is not permitted to be a null pointer.
      void
      deallocate ( pointer __p, size_type __n )
        {
            munmap ( static_cast<void*>(__p), __n );
        }

    private:

        boost::int32_t m_prot;
        boost::int32_t m_flags;
    };
} /* Namespace data_types */
} /* namespace reverse */

#endif /* MEMORY_ALLOCATOR_H */
