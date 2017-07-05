#pragma once

#include <Utils/Definitions.h>
#include <memory>

namespace utils
{
    template<typename Derived, typename Base>
    std::unique_ptr<Derived> 
    dynamic_unique_ptr_cast( std::unique_ptr<Base>& p )
    {
        std::unique_ptr<Derived> result(nullptr);
        if(Derived *wetResult = dynamic_cast<Derived *>(p.get())) 
        {
            p.release();
            result.reset(wetResult);
            return std::move(result);
        }
        return std::move(result);
    }

    constexpr EndianType GetEndianOrder() {
        return
            ((0xFFFFFFFF & 1) == (uint32_t) EndianType::LittleEndian)
                ? EndianType::LittleEndian
                : ((0xFFFFFFFF & 1) == (uint32_t) EndianType::BigEndian )
                    ? EndianType::BigEndian
                        : EndianType::Unknown;
    }

}

