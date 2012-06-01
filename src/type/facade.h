
#pragma once



namespace Type
{
    // methods, which any facade should has
    struct FacadeBaseMethods:
        boost::noncopyable // because of implementation clones themself through 'clone' method
    {
        // to ensure safe destruction from FacadeImpl
        virtual ~FacadeBaseMethods() {};
        
        // is object wrapper around another?
        virtual Bool wrapper() = 0;
    };

    namespace Impl
    {
        // to put something into _stor before calling real constructor
        // this is essentual when constructor raises exception
        struct StubMethods: FacadeBaseMethods
        {
            virtual Bool wrapper() {return false;}
        };
    }

    template<class Methods_, Memoffs::Raw storageSize_>
    struct FacadeImpl
    {
        // Template parameters
        typedef Methods_ Methods;
        static const Memoffs::Raw storageSize = storageSize_;

        // This type
        typedef FacadeImpl This;

        // Memory to place implementation
        //     _stor.construct<ImplType>(...) constructs implementation object here and
        //     _stor.destruct<ImplType>() destructs implementation object
        mutable Membuff<sizeof(Methods) + storageSize> _stor;

        // constructor leaves memory unitialized for speed
        FacadeImpl():
            _stor(uninitialized)
        {
            _stor.construct<Impl::StubMethods>(); // TODO: overhead?
        }

        // copy constructor calls 'clone' method to clone implementation object
        FacadeImpl(const This& from):
            _stor(uninitialized)
        {
            _stor.construct<Impl::StubMethods>(); // TODO: overhead?
            from->clone(*this);
        }

        // assignment is a pair of destruct and construct
        This& operator=(const This& from)
        {
            _stor.objAt<Methods>().~Methods();
            _stor.construct<Impl::StubMethods>(); // TODO: overhead?
            from->clone(*this);
            return *this;
        }

        ~FacadeImpl()
        {
            _stor.objAt<Methods>(0, dontcheck).~Methods();
        }

        // to access facade implementation through -> operator
        //     _impl->clone(to);
        Methods* operator->() const
        {
            return &_stor.objAt<Methods>();
        }
    };
}

//#define PANDA_DECL_FACADE_IMPLEMENTATION()