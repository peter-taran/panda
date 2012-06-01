
namespace Impl
{

struct EncodingMethods
{
    virtual Memoffs charMemSizeMax() = 0;
    virtual Bool anyCharacterCanBeEncoded() = 0;
};

}