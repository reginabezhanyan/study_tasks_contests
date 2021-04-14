class Figure {
    public:
        Figure() {}
        virtual ~Figure() {}
        virtual double get_square(void) const = 0;
};