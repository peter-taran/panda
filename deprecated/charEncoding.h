
namespace CPPDRG_NS
{
    
// »нтерфейс конвертации строк некоторой кодировки из ”никода
// в эту кодировку и обратно
struct CharCvt
{
    // todo: не€сно, что делать, если конвертаци€ некоторого символа невозможна
    
    // todo: не€сно, нужно ли сюда включать наименование кодировки?
    // склон€юсь, что нет, лучше их сделать реестром
};

} // namespace CPPDRG_NS

// ќписание кодировки
class Encoding
{
public:
    inline Encoding(const CPPDRG_NS::CharCvt *convertor);
    
    inline bool operator==(const Encoding &e2) const;
    inline bool operator!=(const Encoding &e2) const;
    inline bool operator<(const Encoding &e2) const;

private:
    const CPPDRG_NS::CharCvt* _cvt;
};

struct Encoding1251: public Encoding
{
    Encoding1251();
};
