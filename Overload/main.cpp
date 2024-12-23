#include <iostream>
#include <vector>

using namespace std;


class Person {
public:
    int a, b;
    Person(int a, int b) : a(a), b(b) {}
    Person operator+(const Person& other) {
        return Person(a - other.a, b - other.b);
    }
};

class Student {
 /*
  * Overloaded ‘operator>>’ must be a binary operator (has 3 parameters)
  * 遇到这个问题一般是在类内编写重载运算符的时候遇到
  * 如果你希望其变为一个友元函数，那么直接在重载运算符的声明前面加上friend关键字
  * 如果你不希望其变为一个友元函数使得可以访问类内成员，那么就将其在类的外部进行声明
  */
    friend int operator+(const Student& a, const Student& b) {
        return a.age+b.age;
    }

    friend int operator*(const Student& a, const Student& b) {
        return a.age*b.age;
    }

    friend int operator++(const Student& a) {
        return a.age+1;
    }

public:
    int age;
    string name;

    Student(int age, string name):age(age),name(name){}

    /*
    * C++ 是如何判断一个operator++函数是前缀自增运算符还是后缀自增运算符？
    * 根据operator++()，()括号中的参数确定的。如果不填参数，就是前缀运算符；如果填入一个虚拟参数(如int)，那就是后缀运算符。是前缀还是后缀和返回值类型是否是引用无关。
     */
    int operator++(int) {
        return age+2;
    }
};

class Hero {
public:
    int level;
    int grade;
    int exp;
    string name;

    Hero(string a,int b,int c,int d):name(a),level(b),grade(c),exp(d){}

    //重载<  vector的sort中会用到///,比较
    bool operator<(const Hero& other) const{
        if(this->level != other.level) return this->level > other.level;
        else if(this->grade != other.grade) return this->grade > other.grade;
        else if(this->exp != other.exp) return this->exp > other.exp;
    }
};

ostream& operator<<(ostream& os, const Hero& a)  {
    os << "Name:" << a.name;
    return os;
}

int main() {
    Person p1(10, 10);
    Person p2(20, 20);
    Person p3 = p1 + p2; // 使用重载的加法运算符
    std::cout << "p3: " << p3.a << ", " << p3.b << std::endl; // 输出: p3: 30, 30

    Student A(12, "xuzhiwei");
    Student B(11, "zhangping");
    int C=A+B;
    int D=A*B;
    cout<< C<<","<<D<<endl;

    Student f(2, "xujingning");

    cout<< ++f << f++ << f.age<<endl;

    Hero a("demonhunter",3,3,3);
    Hero b("guner",1,4,2);
    Hero c("cow",1,5,3);
    vector<Hero> vec;
    vec.push_back(c);
    vec.push_back(b);
    vec.push_back(a);

    sort(vec.begin(),vec.end());

    auto itr=vec.begin();

    for(;itr!=vec.end();++itr) {
        cout << itr->name <<endl;
    }

    cout<<a<<endl;

    return 0;
}
