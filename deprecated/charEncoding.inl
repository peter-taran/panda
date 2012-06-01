
Encoding::Encoding(const CPPDRG_NS::CharCvt *convertor)
:
    _cvt(convertor)
{}

bool Encoding::operator==(const Encoding &e2) const
{
    return _cvt == e2._cvt;
}

bool Encoding::operator!=(const Encoding &e2) const
{
    return _cvt != e2._cvt;
}

bool Encoding::operator<(const Encoding &e2) const
{
    return _cvt < e2._cvt;
}
