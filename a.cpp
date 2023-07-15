#include <iostream>
#include <vector>

class A
{
    public:
        int   val;
        A(int c)
        {
            val = c;
        }
};

class CLA
{
    public:
        std::vector<A>  vect1;
        std::vector<A>  vect2;
        void add(A &arg)
        {
            vect1.push_back(arg);
            vect2.push_back(arg);
        }
};

int main()
{
    A   x(12);
    A   y(13);
    A   z(14);
    A   x1(12);
    A   y1(13);
    A   z1(14);
    A   x2(12);
    A   y2(13);
    A   z2(14);
    CLA obj;
    obj.add(x);
    obj.add(y);
    obj.add(z);
    obj.add(x1);
    obj.add(y1);
    obj.add(z1);
    obj.add(x2);
    obj.add(y2);
    obj.add(z2);
    std::vector<A>::iterator it = obj.vect1.begin();
    obj.vect1.erase(it + 2 + 6);
    obj.vect1.erase(it + 1 + 6);
    obj.vect1.erase(it + 6);
    obj.vect1.erase(it + 2  + 3);
    obj.vect1.erase(it + 1  + 3);
    obj.vect1.erase(it + 3);
    obj.vect1.erase(it + 2);
    obj.vect1.erase(it + 1);
    obj.vect1.erase(it);
    for(std::vector<A>::iterator beg = obj.vect2.begin(); beg != obj.vect2.end(); beg++)
        std::cout << "-> " << beg->val<< std::endl;
}
