//
//  main.cpp
//  Test
//
//  Created by zrma on 2016. 10. 13..
//  Copyright © 2016년 zrma. All rights reserved.
//

#include <iostream>

void LoopTestFunc()
{
    int total = 0;
    
    for(auto i = 0; i < 10000000; ++i)
    {
        if( i % 2 == 0)
        {
            total++;
        }
    }
    
    std::cout << "total : " << total << std::endl;
}

void SwitchTestFunc()
{
    srand (static_cast<unsigned int>( time(NULL) ));
    int array[2] = {0, };
    
    for(auto i = 0; i < 10000000; ++i)
    {
        auto r = rand() % 2;
        auto b = r % 2;
        
        switch (b)
        {
            case 0:
                array[0]++;
                break;
                
            default:
                array[1]++;
                break;
        }
    }
    
    std::cout << array[0] << " " << array[1] << std::endl;
}

void IfTestFunc()
{
    srand (static_cast<unsigned int>( time(NULL) ));
    int array[2] = {0, };
    
    for(auto i = 0; i < 10000000; ++i)
    {
        auto r = rand() % 2;
        auto b = r % 2;
        
        if( b == 0)
        {
            array[0]++;
        }
        else
        {
            array[1]++;
        }
    }
    
    std::cout << array[0] << " " << array[1] << std::endl;
}

int TestA()
{
    return 1;
}

int TestB()
{
    return 1;
}

int(*GFunc[2])(void) = { TestA, TestB };

void FuncPtrTestFunc()
{
    
    
    int a = 0;
    int b = 0;
    
    for(auto i = 0; i < 10000000; ++i)
    {
        a += GFunc[0]();
        b += GFunc[1]();
    }
    
    std::cout << a << " " << b << std::endl;
}

void FuncRunTestFunc()
{
    int a = 0;
    int b = 0;
    
    for(auto i = 0; i < 10000000; ++i)
    {
        a += TestA();
        b += TestB();
    }
    
    std::cout << a << " " << b << std::endl;
}

int main(int argc, const char * argv[])
{
    LoopTestFunc();
    // SwitchTestFunc();
    // FuncPtrTestFunc();
        
    // IfTestFunc();
    // FuncRunTestFunc();
    
    return 0;
}
