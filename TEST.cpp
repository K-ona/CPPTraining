#include <iostream>
using namespace std;

class Human
{
public:
    Human()
    {
        cout << "construct human..." << endl;
        age = 0;
        sex = 0;
    }

    ~Human()///为什么加上析构函数就会运行失败,去掉就行 // win10 cmd g++ thisfile.cpp && a.exe
    {
        cout << "destruct human..." << endl;
    }
    /// 运行报错 无法定位程序输入点__gxx_personality_sj0 于动态链接库 dir/a.exe 上

    void setAge(int a)
    {
        age = a;
    }
    int getAge()
    {
        return age;
    }

    void setSex(int s)
    {
        sex = s;
    }
    int getSex()
    {
        return sex;
    }
private:
    int age;
    int sex; //0 male 1 female
};

int main(int argc, char* argv[])
{
    Human human;
    human.setAge(18);
    human.setSex(0);

    cout << "human:" << human.getAge() << ", " << human.getSex() << endl;
    return 0;
}