
namespace CPPDRG_NS
{
    
// ��������� ����������� ����� ��������� ��������� �� �������
// � ��� ��������� � �������
struct CharCvt
{
    // todo: ������, ��� ������, ���� ����������� ���������� ������� ����������
    
    // todo: ������, ����� �� ���� �������� ������������ ���������?
    // ���������, ��� ���, ����� �� ������� ��������
};

} // namespace CPPDRG_NS

// �������� ���������
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
