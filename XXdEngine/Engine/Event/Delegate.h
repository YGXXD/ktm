#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <memory>
#include <sstream>
#include <unordered_map>

#define DECLARE_FUNCTION_DELEGATE(DelegateName, ReturnValueType, ...) typedef xxd::SingleDelegate<ReturnValueType, __VA_ARGS__> (DelegateName);
#define DECLARE_FUNCTION_DELEGATE_NO_PARAMETER(DelegateName, ReturnValueType) typedef xxd::SingleDelegate<ReturnValueType> (DelegateName);

#define DECLARE_FUNCTION_MULTICAST_DELEGATE(DelegateName, ...) typedef xxd::MultiDelegate<__VA_ARGS__> (DelegateName);
#define DECLARE_FUNCTION_MULTICAST_DELEGATE_NO_PARAMETER(DelegateName) typedef xxd::MultiDelegate<> (DelegateName);

namespace xxd
{

class DelegateInterface final
{
public:
    template<typename ReturnT, typename ...ArgsT>
    friend class SingleDelegate;

    template<typename ...ArgsT>
    friend class MultiDelegate;

private:
    template<typename ReturnT, typename ...ArgsT>
    struct IDelegate
    {
        virtual ReturnT operator() (ArgsT... args) = 0;
        virtual ~IDelegate() { };
    };

    // 类成员函数委托模板
    template<class ClassT, typename ReturnT, typename ...ArgsT>
    class ObjFuncDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(ClassT::* FunT) (ArgsT...);

        ObjFuncDelegate() = delete;
        explicit ObjFuncDelegate(ClassT* objPtr, const FunT& objFun) : obj(objPtr), func(objFun) { };

        virtual ReturnT operator() (ArgsT... args) override
        {
            return (obj->*func)(args...);
        }

        ClassT* obj;
        FunT func;
    };

    // 非成员函数委托模板
    template<typename ReturnT, typename ...ArgsT>
    class FuncDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(*FunT) (ArgsT...);

        FuncDelegate() = delete;
        explicit FuncDelegate(FunT fun) : func(fun) { };

        virtual ReturnT operator() (ArgsT... args) override
        {
            return (*func)(args...);
        }

        FunT func;
    };
    
    // 带有安全检测的类成员函数委托模板
    template<class ClassT, typename ReturnT, typename ...ArgsT>
    class ObjFuncSafeDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(ClassT::* FunT) (ArgsT...);

        ObjFuncSafeDelegate() = delete;
        explicit ObjFuncSafeDelegate(const std::shared_ptr<ClassT>& objShared, const FunT& objFun) : obj(objShared), func(objFun) { };
        explicit ObjFuncSafeDelegate(const std::weak_ptr<ClassT>& objWeak, const FunT& objFun) : obj(objWeak), func(objFun) { };

        virtual ReturnT operator() (ArgsT... args) override
        {
            if(!obj.expired())
                return (obj.lock().get()->*func)(args...);
            return ReturnT();
        }
        
        std::weak_ptr<ClassT> obj;
        FunT func;
    };
    
    // Lambda表达式函数委托模版
    template<class LambdaT, typename ReturnT, typename ...ArgsT>
    class LambdaDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        LambdaDelegate() = delete;
        explicit LambdaDelegate(const LambdaT& lambdaFun) : lambda(lambdaFun) { };

        virtual ReturnT operator() (ArgsT... args) override
        {
            return lambda(args...);
        }

        LambdaT lambda;
    };
    
};

template<typename ReturnT, typename ...ArgsT>
class SingleDelegate final
{
public:
    explicit SingleDelegate() = default;
    
    static SingleDelegate CreateFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunT fun);
    
    template<class ClassT>
    static SingleDelegate CreateObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);
    
    template<class ClassT>
    static SingleDelegate CreateSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);
    
    template<class ClassT>
    static SingleDelegate CreateSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);
    
    template<class LambdaT>
    static SingleDelegate CreateLambda(const LambdaT& lambda);
    
    // 绑定全局或静态函数
    void BindFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunT fun);

    // 绑定类成员函数
    template<class ClassT>
    void BindObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);

    // 绑定安全的类成员函数
    template<class ClassT>
    void BindSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);
    
    template<class ClassT>
    void BindSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun);
    
    // 绑定lambda函数
    template<class LambdaT>
    void BindLambda(const LambdaT& lambda);

    // 代理执行
    ReturnT Invoke(ArgsT... args);
    ReturnT operator() (ArgsT... args);
    
    // 解绑函数
    void UnBind();
    
private:
    std::shared_ptr<DelegateInterface::IDelegate<ReturnT, ArgsT...> > dlgtPtr;
};

typedef struct{
    uint32_t tdlgt; // 代理类型
    uint32_t idlgt; // 代理id
    void* pdlgt; // 代理类
    void* bind; // 绑定地址
}DelegateHandle;

template<typename ...ArgsT>
class MultiDelegate final
{
public:
    explicit MultiDelegate() = default;

    // 添加全局或静态函数
    DelegateHandle AddFunction(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunT fun);

    // 添加类成员函数
    template<class ClassT>
    DelegateHandle AddObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);
    
    // 添加安全的类成员函数
    template<class ClassT>
    DelegateHandle AddSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);
    
    template<class ClassT>
    DelegateHandle AddSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);

    // 添加lambda函数
    template<class LambdaT>
    DelegateHandle AddLambda(const LambdaT& lambda);
    
    // 多播代理执行
    void BroadCast(ArgsT... args);
    void operator() (ArgsT... args);
    
    // 根据代理句柄移除
    bool Remove(const DelegateHandle& handle);
    
    // 移除全局或静态函数
    bool Remove(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunT objFun);

    // 移除类成员函数
    template<class ClassT>
    bool Remove(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);
    
    // 移除安全类成员函数
    template<class ClassT>
    bool Remove(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);
    
    template<class ClassT>
    bool Remove(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun);
    
    // 清空代理
    void Clear();
private:
    // 遍历dlgtMap，判断为真才会被移除
    template<class Comp>
    bool Remove(const Comp& rmLambda);
    
    uint32_t dlgtId;
    std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > > dlgtMap;

    // Handle转化为字符串函数
    inline static std::string HandleToString(const DelegateHandle& handle)
    {
        static std::stringstream ss;
        ss << handle.tdlgt << handle.idlgt << handle.pdlgt << handle.bind;
        std::string key = ss.str();
        ss.str("");
        return key;
    };
};

}

template<typename ReturnT, typename ...ArgsT>
inline xxd::SingleDelegate<ReturnT, ArgsT...> xxd::SingleDelegate<ReturnT, ArgsT...>::CreateFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunT fun)
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindFunction(fun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline xxd::SingleDelegate<ReturnT, ArgsT...> xxd::SingleDelegate<ReturnT, ArgsT...>::CreateObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindObject(obj, objFun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline xxd::SingleDelegate<ReturnT, ArgsT...> xxd::SingleDelegate<ReturnT, ArgsT...>::CreateSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindSafeObj(objShared, objFun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline xxd::SingleDelegate<ReturnT, ArgsT...> xxd::SingleDelegate<ReturnT, ArgsT...>::CreateSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindSafeObj(objWeak, objFun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class LambdaT>
inline xxd::SingleDelegate<ReturnT, ArgsT...> xxd::SingleDelegate<ReturnT, ArgsT...>::CreateLambda(const LambdaT& lambda)
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindLambda(lambda);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::BindFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunT fun)
{
    dlgtPtr = std::make_shared<DelegateInterface::FuncDelegate<ReturnT, ArgsT...> >(fun);
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::BindObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    dlgtPtr = std::make_shared<DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...> >(obj, objFun);
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::BindSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    dlgtPtr = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, ReturnT, ArgsT...> >(objShared, objFun);
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::BindSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun)
{
    dlgtPtr = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, ReturnT, ArgsT...> >(objWeak, objFun);
}

template<typename ReturnT, typename ...ArgsT>
template<class LambdaT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::BindLambda(const LambdaT& lambda)
{
    dlgtPtr = std::make_shared<DelegateInterface::LambdaDelegate<LambdaT, ReturnT, ArgsT...> >(lambda);
}

template<typename ReturnT, typename ...ArgsT>
inline ReturnT xxd::SingleDelegate<ReturnT, ArgsT...>::Invoke(ArgsT ...args)
{
    if(dlgtPtr.get())
        return (*dlgtPtr)(args...);
    
    return ReturnT();
}

template<typename ReturnT, typename ...ArgsT>
inline ReturnT xxd::SingleDelegate<ReturnT, ArgsT...>::operator()(ArgsT ...args)
{
    return Invoke(args...);
}

template<typename ReturnT, typename ...ArgsT>
inline void xxd::SingleDelegate<ReturnT, ArgsT...>::UnBind()
{
    dlgtPtr.reset();
}

template<typename ...ArgsT>
inline xxd::DelegateHandle xxd::MultiDelegate<ArgsT...>::AddFunction(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunT fun)
{
    DelegateHandle handle = { 0, dlgtId++, this, (void*)fun };
    dlgtMap[HandleToString(handle)] = std::make_shared<DelegateInterface::FuncDelegate<void, ArgsT...> >(fun);
    
    return handle;
}

template<typename ...ArgsT>
template<class ClassT>
inline xxd::DelegateHandle xxd::MultiDelegate<ArgsT...>::AddObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    DelegateHandle handle = { 0x1, dlgtId++, this, (void*)obj };
    dlgtMap[HandleToString(handle)] = std::make_shared<DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...> >(obj, objFun);
    
    return handle;
}

template<typename ...ArgsT>
template<class ClassT>
inline xxd::DelegateHandle xxd::MultiDelegate<ArgsT...>::AddSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    DelegateHandle handle = { 0x2, dlgtId++, this, (void*)objShared.get() };
    dlgtMap[HandleToString(handle)] = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, void, ArgsT...> >(objShared, objFun);
    
    return handle;
}

template<typename ...ArgsT>
template<class ClassT>
inline xxd::DelegateHandle xxd::MultiDelegate<ArgsT...>::AddSafeObj(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    DelegateHandle handle = { 0x2, dlgtId++, this, (void*)objWeak.lock().get() };
    dlgtMap[HandleToString(handle)] = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, void, ArgsT...> >(objWeak, objFun);
    
    return handle;
}

template<typename ...ArgsT>
template<class LambdaT>
inline xxd::DelegateHandle xxd::MultiDelegate<ArgsT...>::AddLambda(const LambdaT& lambda)
{
    DelegateHandle handle = { 0x4, dlgtId++, this, 0 };
    dlgtMap[HandleToString(handle)] = std::make_shared<DelegateInterface::LambdaDelegate<LambdaT, void, ArgsT...> >(lambda);
    
    return handle;
}

template<typename ...ArgsT>
inline void xxd::MultiDelegate<ArgsT...>::BroadCast(ArgsT ...args)
{
    for (const auto& it : dlgtMap)
    {
        (*(it.second))(args...);
    }
}

template<typename ...ArgsT>
inline void xxd::MultiDelegate<ArgsT...>::operator()(ArgsT ...args)
{
    BroadCast(args...);
}

template<typename ...ArgsT>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(const xxd::DelegateHandle& handle)
{
    std::string key = HandleToString(handle);
    if(dlgtMap.count(key))
    {
        dlgtMap.erase(key);
        return true;
    }
    return false;
}

template<typename ...ArgsT>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunT objFun)
{
    auto rmLambda = [&](const typename std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > >::iterator& it)->bool
    {
        DelegateInterface::IDelegate<void, ArgsT...>* dlgtPtr = (*it).second.get();
        auto flag = dynamic_cast<DelegateInterface::FuncDelegate<void, ArgsT...>*>(dlgtPtr);
        return flag && flag->func == objFun;
    };
    return Remove(rmLambda);
}

template<typename ...ArgsT>
template<class ClassT>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    auto rmLambda = [&](const typename std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > >::iterator& it)->bool
    {
        DelegateInterface::IDelegate<void, ArgsT...>* dlgtPtr = (*it).second.get();
        auto flag = dynamic_cast<DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>*>(dlgtPtr);
        return flag && flag->func == objFun && flag->obj == obj;
    };
    return Remove(rmLambda);
}

template<typename ...ArgsT>
template<class ClassT>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    auto rmLambda = [&](const typename std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > >::iterator& it)->bool
    {
        DelegateInterface::IDelegate<void, ArgsT...>* dlgtPtr = (*it).second.get();
        auto flag = dynamic_cast<DelegateInterface::ObjFuncSafeDelegate<ClassT, void, ArgsT...>*>(dlgtPtr);
        return flag && flag->func == objFun && flag->obj.lock() == objShared;
    };
    return Remove(rmLambda);
}

template<typename ...ArgsT>
template<class ClassT>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(const std::weak_ptr<ClassT>& objWeak, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun)
{
    return !objWeak.expired() ? Remove(objWeak.lock(), objFun) : false;
}

template<typename ...ArgsT>
inline void xxd::MultiDelegate<ArgsT...>::Clear()
{
    //引用计数为0时自动释放对象
    dlgtMap.clear();
}

template<typename ...ArgsT>
template<class Comp>
inline bool xxd::MultiDelegate<ArgsT...>::Remove(const Comp& rmLambda)
{
    std::vector<typename std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > >::iterator> deleteIts;
    
    for (auto it = dlgtMap.begin(); it != dlgtMap.end(); it++)
    {
        if (rmLambda(it))
        {
            deleteIts.push_back(it);
        }
    }
    
    bool rmSuccess = deleteIts.size();
    if(rmSuccess)
    {
        for(const auto& dlgtIt : deleteIts)
            dlgtMap.erase(dlgtIt);
    }
    return rmSuccess;
}

#endif
