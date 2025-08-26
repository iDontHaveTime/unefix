#ifndef EFIRTTI_HPP
#define EFIRTTI_HPP

namespace __cxxabiv1{
    struct __class_type_info{
        virtual ~__class_type_info() noexcept;
        virtual const char* name() const noexcept{return "unknown";}
    };
    struct __si_class_type_info : __class_type_info{
        const __class_type_info* base_type;
        virtual ~__si_class_type_info() noexcept;
    };
}

extern "C" __attribute__((weak)) const __cxxabiv1::__class_type_info typeinfo_dummy;

#endif // EFIRTTI_HPP
