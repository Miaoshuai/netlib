/*======================================================
    > File Name: objectFactory.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月13日 星期日 16时28分51秒
 =======================================================*/
#pragma once

#include <list>
#include <iostream>
#include <memory>

template <typename T>
class ObjectPool
{
    public:
        template<typename ...Args>
        ObjectPool(int number,Args ...args)
            :number_(number)
        {
            initObjectPool(args...);
        }

        //获取对象
        T *getObject(void)
        {
            T *objectPtr= objectPool_.front();
            objectPool_.pop_front();
            return objectPtr;
        }

        //归还对象
        void giveBackObject(T *t)
        {
            objectPool_.push_back(t);      
        }

        //销毁所有对象
        ~ObjectPool()
        {
            for(auto x : objectPool_)
            {
                delete x;
            }
        }
    private:
        //初始化对象池
        template <typename ...Args>
        void initObjectPool(Args ...args)
        {
            for(int i = 0; i < number_; i++)
            {
                objectPool_.push_back(new T(args...));
            }
        }

        std::list<T *> objectPool_;
        int number_; 
};


