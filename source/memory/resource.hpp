#pragma once

namespace Resource
{
    std::atomic<u3> in_use;
    void*alloc(u3 sz);
    void free(void*p);
};
