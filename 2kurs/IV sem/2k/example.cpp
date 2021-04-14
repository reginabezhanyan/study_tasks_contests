class CMyStack
{
public:
    CMyStack();
    ~CMyStack();
    void Push(int d);
    int Pop();
    bool isEmpty();
    void Print();
    
private:
    struct Node
    {
        int d;
        Node *p;
    };
 
    Node *top;
};
 
CMyStack::CMyStack():top(NULL)
{
    
}
 
void CMyStack::Push(int d)
{
    Node *pv = new Node;
    pv->d = d;
    pv->p = top;
    top = pv;
}
 
int CMyStack::Pop()
{
    if (isEmpty())
    {
        return -1;
    }
    int temp = top->d;
    Node *pv = top;
    top = top->p;
    delete pv;
    return temp;
}
 
 
bool CMyStack::isEmpty()
{
    return top ? false : true;
}
 
void CMyStack::Print()
{
    while (top)
    {
        std::cout << Pop() << ' ';
    }
 
    std::cout << std::endl;
}
 
CMyStack::~CMyStack()
{
    while (top)
    {
        Node *pv = top;
        top = top->p;
        delete pv;
    }
 
}
 
void emptyStack(CMyStack & stack);
 
int main()
{
    CMyStack TrainBase, OneTrain, TwoTrain;
    std::ifstream in("trains.txt", std::ios::in);
    if (!in)
    {
        std::cout << "Cannot open file 'trais.txt' for reading" << std::endl;
        return 1;
    }
 
 
    while (!in.eof())
    {
        int pr;
        in >> pr;
        TrainBase.Push(pr);
    }
 
    while (!TrainBase.isEmpty())
    {
        int pr = TrainBase.Pop();
        switch (pr)
        {
            case 1:
                OneTrain.Push(pr);
                break;
            case 2:
                TwoTrain.Push(pr);
                break;
        }
    }
 
    OneTrain.Print();
    TwoTrain.Print();
    
    _getch();
    return 0;
}
 
void emptyStack(CMyStack & stack)
{
    if (stack.isEmpty())
    {
        std::cout << "Stack is empty" << std::endl;
    }
    else
    {
        std::cout << "Stack is not empty" << std::endl;
    }
}




        class complex_stack
    {
        public:
            complex_stack();
            ~complex_stack();
            void Push(complex x);
            complex Pop(); 
            bool isEmpty();
        private:
            struct Node
            {
                complex x;
                Node *p;
            }
            
            Node *top;
    };
    
    complex_stack::complex_stack():top(NULL)
    {
    }
    
    void complex_stack::Push(complex x)
    {
        Node *pv = new Node;
        pv->x = x;
        pv->p = top;
        top = pv;
    }
    
    complex complex_stack::Pop()
    {
        if (isEmpty())
        {
            return -1;
        }
        complex temp = top->x;
        Node *pv = top;
        top = top->p;
        delete pv;
        return temp;
    }
 
    bool complex_stack::isEmpty()
    {
        return top ? false : true;
    }
    
    complex_stack::~complex_stack()
    {
        while (top)
        {
            Node *pv = top;
            top = top->p;
            delete pv;
        }
    }