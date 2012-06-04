

#ifndef CPPDRG_DEFAULT_MB_ENCODING
    #define CPPDRG_DEFAULT_MB_ENCODING Encoding1251()
#endif

// ��������������� ������ ��������. �������� ����� � ������ ����������.
class String
{
public:
    ~String();
    String(Uninitialized); // same as String()
    
    // ������������� ������ �������
    String();
    
    // ������������� ��������
    // ���������� �� ���������� ������ String, ����������� ������ �� �������� ������
    // ���� ��������� ���������� ��������� �������, ��������� � ���������� String
    String(char *str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String(wchar_t *str);
    String(char *str, Umem charCount, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String(wchar_t *str, Umem charCount);
    #ifdef CPPDRG_SUPPORT_STD_STRING
        String(std::string &str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
        String(std::wstring &str);
    #endif
    
    // ���������� ���������� ������ String, �������� ������ ����� ����������
    String(const String &str);

    // ����������� String � String
    // ���������� ���������� ������ String, �������� ������ ����� ����������
    String& operator=(const String &str);
    String& operator=(const wchar_t *str);
    String& operator=(const std::wstring &str);
    
    // ���� ������� assign � ���� �� �����������, ��� � � �������������
    // ���������� ���������� ������ String, �������� ������ ����� ����������
    String& assign(const char *str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String& assign(const wchar_t *str);
    String& assign(const char *str, Umem charCount, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String& assign(const wchar_t *str, Umem charCount);
    #ifdef CPPDRG_SUPPORT_STD_STRING
        String& assign(const std::string &str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
        String& assign(const std::wstring &str);
    #endif
    
    // String ����� ������� � �� ������� ����������. ����� �����������, ������� ��
    // � ����� ����������� ������� ���, ����� ������
    bool ownContents() const;
    String& makeContentsOwned();

    // �������� �� ������� � ������� ������
    bool empty() const;
    void clear();
    
    // �������� �� �������, ������ ������ ��������� ������, ���� ������� ������ ��
    // ��������, ������������� � ignoreChars
    bool emptyIgnore(const String &ignoreChars = " \t") const;
    
    // ����� ������ � �������� � � ������
    Umem length() const; // � ��������
    Umem lengthInBytes(Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const; // � ������

    // ��������� ����� �� ������ ����������
    bool equal(const String &s2) const;
    bool operator==(const String &s2) const;
    bool operator!=(const String &s2) const;

    // ���������� �������������� (<, > � �.�.) ��� ���������. �� ����� ����� ���������
    // �������������� �����
    
    // ��������� ����� ����������� ������
    #ifdef CPPDRG_SUPPORT_STD_STRING
        std::string asString(Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const;
        std::wstring asWString() const;
    #endif
    
    // ����������� ���������� � �����, ��� �� ������ - ��������.
    // �������: true, ���� ������ � false, ���� �������� ��������.
    // � buffer �������� NULL, ����� ������ �����������, ������ �� ������
    bool toBuffer(char *buffer, Umem bufSize) const;
    bool toWBufferBytes(wchar_t *buffer, Umem bufSizeInBytes) const;
    bool toWBufferChars(wchar_t *buffer, Umem bufSizeInChars) const;
    
    // ������ � ��������� ��������
    wchar_t operator[](Umem index) const;
    wchar_t wideChar(Umem index) const;
    char encChar(Umem index, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const;
    
private:
    Addr _data;
};
