
namespace CPPDRG_NS
{
    template<class Item, bool usePtrs>
    struct StorPlcyImpl
    {};
    
    template<class Item>
    struct StorPlcyImpl<Item, false>
    {
        typedef typename boost::remove_const<
                typename boost::remove_reference<Item>::type
                >::type Stor;
        static const Stor get(const Item& item)
        {
            return item;
        }
        template<class Value>
        static Bool equal(Stor item, const Value& value)
        {
            return value == item;
        }
    };
    
    template<class Item>
    struct StorPlcyImpl<Item, true>
    {
        typedef typename boost::add_pointer<
                typename boost::add_const<Item>::type
                >::type Stor;
        static Stor get(const Item& item)
        {
            return &item;
        }
        template<class Value>
        static Bool equal(Stor item, const Value& value)
        {
            return value == *item;
        }
    };
    
    template<class Item>
    struct StorPlcy: StorPlcyImpl<
        Item,
        (sizeof(Item) > sizeof(void*))
        || boost::is_polymorphic<Item>::value
        || !boost::has_trivial_copy<Item>::value
    >
    {};
    
    /*template<Umem size, class StorPlcy, class Item>
    class OneOf
    {
        typedef OneOf<size, StorPlcy, Item> This;
        typedef typename StorPlcy::Stor Stor;

        boost::array<Stor, size> _stor;
    
    public:
        template<class Value>
        Bool operator==(const Value& value) const
        {
            for(int i = 0; i < size; ++i)
                if( StorPlcy::equal(_stor[i], value) )
                    return true;
            return false;
        }

        template<class Value>
        friend Bool operator==(const Value& y, const This& x) { return x == y; }
        
        template<class Value>
        friend Bool operator!=(const Value& y, const This& x) { return !(x == y); }

        template<class Value>
        friend Bool operator!=(const This& y, const Value& x) { return !(y == x); }

        OneOf(
            const Item& item0
        )
        {
            _stor[0] = StorPlcy::get(item0);
        }

        OneOf(
            const Item& item0,
            const Item& item1
        )
        {
            _stor[0] = StorPlcy::get(item0);
            _stor[1] = StorPlcy::get(item1);
        }

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2
        )
        {
            _stor[0] = StorPlcy::get(item0);
            _stor[1] = StorPlcy::get(item1);
            _stor[2] = StorPlcy::get(item2);
        }

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3
        )
        {
            _stor[0] = StorPlcy::get(item0);
            _stor[1] = StorPlcy::get(item1);
            _stor[2] = StorPlcy::get(item2);
            _stor[3] = StorPlcy::get(item3);
        }
    };*/

    template<Umem size, class StorPlcy, class Item>
    class OneOf
    {
        typedef OneOf<size, StorPlcy, Item> This;
        typedef OneOf<size-1, StorPlcy, Item> Next;
        typedef typename StorPlcy::Stor Stor;
        Stor _stor;
        Next _next;

    public:
        template<class Value>
        Bool operator==(const Value& value) const
        {
            if( StorPlcy::equal(_stor, value) )
                return true;
            return _next.operator==(value);
        }
        
        template<class Value>
        friend Bool operator==(const Value& y, const This& x) { return x == y; }
        
        template<class Value>
        friend Bool operator!=(const Value& y, const This& x) { return !(x == y); }

        template<class Value>
        friend Bool operator!=(const This& y, const Value& x) { return !(y == x); }

        OneOf(
            const Item& item0
        ):
            _stor(StorPlcy::get(item0))
        {}

        OneOf(
            const Item& item0,
            const Item& item1
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4,
            const Item& item5
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4,
                  item5)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4,
            const Item& item5,
            const Item& item6
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4,
                  item5,
                  item6)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4,
            const Item& item5,
            const Item& item6,
            const Item& item7
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4,
                  item5,
                  item6,
                  item7)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4,
            const Item& item5,
            const Item& item6,
            const Item& item7,
            const Item& item8
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4,
                  item5,
                  item6,
                  item7,
                  item8)
        {}

        OneOf(
            const Item& item0,
            const Item& item1,
            const Item& item2,
            const Item& item3,
            const Item& item4,
            const Item& item5,
            const Item& item6,
            const Item& item7,
            const Item& item8,
            const Item& item9
        ):
            _stor(StorPlcy::get(item0)),
            _next(item1,
                  item2,
                  item3,
                  item4,
                  item5,
                  item6,
                  item7,
                  item8,
                  item9)
        {}
    };

    template<class StorPlcy, class Item>
    class OneOf<0, StorPlcy, Item>
    {
    public:
        template<class Value>
        Bool operator==(const Value& value) const
        {
            return false;
        }
    };
    
} // namespace CPPDRG_NS


template<class Item>
CPPDRG_NS::OneOf<1, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0
){
    return CPPDRG_NS::OneOf<1, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0);
}

template<class Item>
CPPDRG_NS::OneOf<2, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1
){
    return CPPDRG_NS::OneOf<2, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1);
}

template<class Item>
CPPDRG_NS::OneOf<3, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2
){
    return CPPDRG_NS::OneOf<3, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2);
}

template<class Item>
CPPDRG_NS::OneOf<4, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3
){
    return CPPDRG_NS::OneOf<4, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3);
}

template<class Item>
CPPDRG_NS::OneOf<5, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4
){
    return CPPDRG_NS::OneOf<5, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4);
}

template<class Item>
CPPDRG_NS::OneOf<6, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4,
    const Item &item5
){
    return CPPDRG_NS::OneOf<6, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4,
        item5);
}

template<class Item>
CPPDRG_NS::OneOf<7, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4,
    const Item &item5,
    const Item &item6
){
    return CPPDRG_NS::OneOf<7, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4,
        item5,
        item6);
}

template<class Item>
CPPDRG_NS::OneOf<8, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4,
    const Item &item5,
    const Item &item6,
    const Item &item7
){
    return CPPDRG_NS::OneOf<8, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4,
        item5,
        item6,
        item7);
}

template<class Item>
CPPDRG_NS::OneOf<9, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4,
    const Item &item5,
    const Item &item6,
    const Item &item7,
    const Item &item8
){
    return CPPDRG_NS::OneOf<9, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4,
        item5,
        item6,
        item7,
        item8);
}

template<class Item>
CPPDRG_NS::OneOf<10, CPPDRG_NS::StorPlcy<Item>, Item>
oneof(
    const Item &item0,
    const Item &item1,
    const Item &item2,
    const Item &item3,
    const Item &item4,
    const Item &item5,
    const Item &item6,
    const Item &item7,
    const Item &item8,
    const Item &item9
){
    return CPPDRG_NS::OneOf<10, CPPDRG_NS::StorPlcy<Item>, Item>(
        item0,
        item1,
        item2,
        item3,
        item4,
        item5,
        item6,
        item7,
        item8,
        item9);
}
