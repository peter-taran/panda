
// Fill memory with zeroes
inline void zeroMem(const MemArea &area)
{
    memset(area.start().asPtr(), 0, area.size().asRaw());
}

// Fill memory with filler byte
inline void fillMem(const MemArea &area, const Byte filler)
{
    memset(area.start().asPtr(), filler, area.size().asRaw());
}

// Fill POD-variable with zeroes
template<class Class>
inline void zeroVar(Class &object) 
{
    zeroMem(
        MemArea(Addr(&object), Adif(sizeof(object)))
    );
}
