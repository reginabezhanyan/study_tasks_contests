#ifndef __COMPLEX_STACK_H
#define __COMPLEX_STACK_H

#include <iostream>
#include <new>

namespace numbers {
    class complex_stack
    {
        private:
            size_t size_;
            complex *array;
        public:  
            complex_stack(): size_(0), array(nullptr) { }
            
            complex_stack(const complex_stack &st): size_(st.size_) {
                if(size_ == 0) {
                    return;
                }
                array = static_cast<complex*>(::operator new[](size_ * sizeof(*array)));
                for(size_t i = 0; i < size_; i++) 
                    new(&array[i])complex(st.array[i]);
            }
            
            complex_stack(complex_stack &&st): size_(st.size_), array(st.array) {
                st.size_ = 0;
                st.array = nullptr;
            }
            
            size_t size() const
            {
                return size_;
            }
            
            complex operator +() const
            {
                return array[size_ - 1];
            }
            
            complex_stack operator ~() const
            {
                complex_stack st(*this); 
                st.size_ --;
                st.array[st.size_].~complex();
                return st; 
            }
            
            complex operator [](size_t n) const
            {   
                return array[n];
            }
            
            
            complex_stack &operator =(const complex_stack& st)
            {
                if(this == &st) 
                {
                    return *this;
                }
                for (size_t i = 0; i < size_; i++) {
                    array[i].~complex();
                }
                ::operator delete[](array);
                size_ = st.size_;
                array = static_cast<complex*>(::operator new[](size_ * sizeof(*array)));
                for(size_t i = 0; i < size_; i++)
                    new(&array[i])complex(st.array[i]);
                return *this;
            }   
            
            ~complex_stack()
            {
                for (size_t i = 0; i < size_; i++) {
                    array[i].~complex();
                }
                ::operator delete[](array);
            }
            
            friend complex_stack operator <<(const complex_stack &, const complex &);     
    };
    
    complex_stack operator <<(const complex_stack &st, const complex &s)
    {
        complex_stack tmp;
        tmp.size_ = st.size_ + 1;
        tmp.array = static_cast<complex*>(::operator new[](tmp.size_ * sizeof(*tmp.array)));
        for(size_t i = 0; i < tmp.size_ - 1; i++)
            new(&tmp.array[i])complex(st.array[i]);
        new(&tmp.array[tmp.size_ - 1])complex(s);
        return tmp;
    } 
}
#endif /* __COMPLEX_STACK_H */
