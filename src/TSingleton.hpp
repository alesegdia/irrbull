#ifndef __TSINGLETON__
#define __TSINGLETON__

template <class ActualClass>
class TSingleton
{
    public:
        static ActualClass& instance()
        {
            static ActualClass s;
            return s;
        }
        virtual ~TSingleton(){}
    protected:
        TSingleton(){}
    private:
        TSingleton(TSingleton const &);
        TSingleton& operator=(TSingleton const&);
};

#endif
