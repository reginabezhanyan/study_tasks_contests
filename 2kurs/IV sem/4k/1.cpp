enum { N = 3 };

template<typename T> 
typename T::value_type process(const T &array)
{
    typename T::value_type sum{};
    if(!array.size()) {
        return sum;
    }
    auto itr = array.cend(); 
    --itr;
    for(int i = 0; i < N; ++i) {
        sum += *itr;
        if(itr == array.cbegin()) break; 
        --itr;
        if(itr == array.cbegin()) break; 
        --itr;
    } 
    return sum;
}

