# overload-tool
一个用于派发调用的元工具
可以和```std::visit```一起使用。
例如可以使用如下代码
```cpp
#include <iostream>
#include"overload.h"
#include<variant>
#include<string>
void f(int i)
{
    std::cout<< "f(int) "<< i<<"\n";
}
void g(std::string_view s )
{
    std::cout <<"g(std::string_view) " << s<<"\n";
}
int main()
{
    auto ol = Yc::overload{ f,g };
    std::variant<int, std::string> is{};
    is = 123;
    std::visit(ol, is);
    is = "hello";
    std::visit(ol, is);
}
```
运行结果
```
f(int) 123
g(std::string_view) hello

```
