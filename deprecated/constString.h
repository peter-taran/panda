

#ifndef CPPDRG_DEFAULT_MB_ENCODING
    #define CPPDRG_DEFAULT_MB_ENCODING Encoding1251()
#endif

// Нередактируемая строка символов. Хранится может в разных кодировках.
class String
{
public:
    ~String();
    String(Uninitialized); // same as String()
    
    // Инициализация пустой строкой
    String();
    
    // Инициализация строками
    // Содержимое НЕ КОПИРУЕТСЯ внутрь String, сохраняется ссылка на исходный объект
    // Если изменится содержимое исходного объекта, изменится и содержимое String
    String(char *str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String(wchar_t *str);
    String(char *str, Umem charCount, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String(wchar_t *str, Umem charCount);
    #ifdef CPPDRG_SUPPORT_STD_STRING
        String(std::string &str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
        String(std::wstring &str);
    #endif
    
    // Содержимое КОПИРУЕТСЯ внутрь String, исходный объект можно уничтожать
    String(const String &str);

    // Копирование String в String
    // Содержимое КОПИРУЕТСЯ внутрь String, исходный объект можно уничтожать
    String& operator=(const String &str);
    String& operator=(const wchar_t *str);
    String& operator=(const std::wstring &str);
    
    // блок методов assign с теми же параметрами, что и в конструкторах
    // Содержимое КОПИРУЕТСЯ внутрь String, исходный объект можно уничтожать
    String& assign(const char *str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String& assign(const wchar_t *str);
    String& assign(const char *str, Umem charCount, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
    String& assign(const wchar_t *str, Umem charCount);
    #ifdef CPPDRG_SUPPORT_STD_STRING
        String& assign(const std::string &str, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING);
        String& assign(const std::wstring &str);
    #endif
    
    // String может владеть и не владеть содержимым. Здесь проверяется, владеет ли
    // и даётся возможность сделать так, чтобы владел
    bool ownContents() const;
    String& makeContentsOwned();

    // Проверка на пустоту и очистка строки
    bool empty() const;
    void clear();
    
    // Проверка на пустоту, причём строка считается пустой, если состоит только из
    // символов, перечисленных в ignoreChars
    bool emptyIgnore(const String &ignoreChars = " \t") const;
    
    // Длина строки в символах и в байтах
    Umem length() const; // в символах
    Umem lengthInBytes(Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const; // в байтах

    // Сравнение строк на точное совпадение
    bool equal(const String &s2) const;
    bool operator==(const String &s2) const;
    bool operator!=(const String &s2) const;

    // Операторов упорядочивания (<, > и т.п.) нет намеренно. Уж очень много вариантов
    // упорядочивания строк
    
    // Получение всего содержимого строки
    #ifdef CPPDRG_SUPPORT_STD_STRING
        std::string asString(Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const;
        std::wstring asWString() const;
    #endif
    
    // Скопировать содержимое в буфер, что не влезло - отрезать.
    // Возврат: true, если влезла и false, если пришлось отрезать.
    // В buffer допустим NULL, тогда просто вычисляется, влезет ли строка
    bool toBuffer(char *buffer, Umem bufSize) const;
    bool toWBufferBytes(wchar_t *buffer, Umem bufSizeInBytes) const;
    bool toWBufferChars(wchar_t *buffer, Umem bufSizeInChars) const;
    
    // Доступ к отдельным символам
    wchar_t operator[](Umem index) const;
    wchar_t wideChar(Umem index) const;
    char encChar(Umem index, Encoding enc = CPPDRG_DEFAULT_MB_ENCODING) const;
    
private:
    Addr _data;
};
