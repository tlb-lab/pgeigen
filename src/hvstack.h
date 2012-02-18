#define SUM_OR_DYNAMIC(x,y) (x==Eigen::Dynamic || y==Eigen::Dynamic) ? Eigen::Dynamic:(x+y)

template<typename Derived1, typename Derived2>
struct hstack_return 
{
    typedef typename Derived1::Scalar Scalar;
    enum 
    {
        RowsAtCompileTime = Derived1::RowsAtCompileTime,
        ColsAtCompileTime = SUM_OR_DYNAMIC(Derived1::ColsAtCompileTime, Derived2::ColsAtCompileTime),
        Options = Derived1::Flags&Eigen::RowMajorBit ? Eigen::RowMajor : 0,
        MaxRowsAtCompileTime = Derived1::MaxRowsAtCompileTime,
        MaxColsAtCompileTime = SUM_OR_DYNAMIC(Derived1::MaxColsAtCompileTime, Derived2::MaxColsAtCompileTime)
    };
    
    typedef Eigen::Matrix<Scalar,
            RowsAtCompileTime,
            ColsAtCompileTime,
            Options,
            MaxRowsAtCompileTime,
            MaxColsAtCompileTime> type;
};

template<typename Derived1, typename Derived2>
typename hstack_return<Derived1,Derived2>::type
HStack (const Eigen::MatrixBase<Derived1>& lhs, const Eigen::MatrixBase<Derived2>& rhs) 
{
    typename hstack_return<Derived1,Derived2>::type res;
    
    res.resize(lhs.rows(), lhs.cols() + rhs.cols());
    res << lhs, rhs;
    
    return res;
};

template<typename Derived1, typename Derived2>
struct vstack_return 
{
    typedef typename Derived1::Scalar Scalar;
    enum 
    {
        RowsAtCompileTime = SUM_OR_DYNAMIC(Derived1::RowsAtCompileTime, Derived2::RowsAtCompileTime),
        ColsAtCompileTime = Derived1::ColsAtCompileTime,
        Options = Derived1::Flags&Eigen::RowMajorBit ? Eigen::RowMajor : 0,
        MaxRowsAtCompileTime = SUM_OR_DYNAMIC(Derived1::MaxRowsAtCompileTime, Derived2::MaxRowsAtCompileTime),
        MaxColsAtCompileTime = Derived1::MaxColsAtCompileTime
    };
    
    typedef Eigen::Matrix<Scalar,
                RowsAtCompileTime,
                ColsAtCompileTime,
                Options,
                MaxRowsAtCompileTime,
                MaxColsAtCompileTime> type;
};

template<typename Derived1, typename Derived2>
typename vstack_return<Derived1,Derived2>::type
VStack (const Eigen::MatrixBase<Derived1>& lhs, const Eigen::MatrixBase<Derived2>& rhs) 
{
    typename vstack_return<Derived1,Derived2>::type res;
    
    res.resize(lhs.rows() + rhs.rows(), lhs.cols());
    res << lhs, rhs;
    
    return res;
};