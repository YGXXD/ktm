#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include "Chtholly.h"

#define DECLARE_FUNCTION_DELEGATE(DelegateName, ReturnValueType, ...) typedef ktl::SingleDelegate<ReturnValueType, __VA_ARGS__> (DelegateName);
#define DECLARE_FUNCTION_DELEGATE_NO_PARAMETER(DelegateName, ReturnValueType) typedef ktl::SingleDelegate<ReturnValueType> (DelegateName);

#define DECLARE_FUNCTION_MULTICAST_DELEGATE(DelegateName, ...) typedef ktl::MultiDelegate<__VA_ARGS__> (DelegateName);
#define DECLARE_FUNCTION_MULTICAST_DELEGATE_NO_PARAMETER(DelegateName) typedef ktl::MultiDelegate<> (DelegateName);

namespace ktl
{

class DelegateInterface final
{
private:
    template<typename ReturnT, typename ...ArgsT>
    friend class SingleDelegate;

    template<typename ...ArgsT>
    friend class MultiDelegate;

    template<typename ReturnT, typename ...ArgsT>
    struct IDelegate
    {
        virtual ReturnT operator() (ArgsT... args) noexcept = 0;
        virtual ~IDelegate() { };
    };

    // 类成员函数委托模板
    template<class ClassT, typename ReturnT, typename ...ArgsT>
    class ObjFuncDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(ClassT::* FunType) (ArgsT...);

        ObjFuncDelegate() = delete;
        explicit ObjFuncDelegate(ClassT* objPtr, const FunType& objFun) : obj(objPtr), func(objFun) { };

        virtual ReturnT operator() (ArgsT... args) noexcept override 
        {
            return (obj->*func)(args...);
        }

        ClassT* obj;
        FunType func;
    };

    // 非成员函数委托模板
    template<typename ReturnT, typename ...ArgsT>
    class FuncDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(*FunType) (ArgsT...);

        FuncDelegate() = delete;
        explicit FuncDelegate(FunType fun) : func(fun) { };

        virtual ReturnT operator() (ArgsT... args) noexcept override
        {
            return (*func)(args...);
        }

        FunType func;
    };
    
    // 带有安全检测的类成员函数委托模板
    template<class ClassT, typename ReturnT, typename ...ArgsT>
    class ObjFuncSafeDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        typedef ReturnT(ClassT::* FunType) (ArgsT...);

        ObjFuncSafeDelegate() = delete;
        explicit ObjFuncSafeDelegate(const std::shared_ptr<ClassT>& objShared, const FunType& objFun) : obj(objShared), func(objFun) { };

        virtual ReturnT operator() (ArgsT... args) noexcept override
        {
            if(!obj.expired())
                return (obj.lock().get()->*func)(args...);
            return ReturnT();
        }
        
        std::weak_ptr<ClassT> obj;
        FunType func;
    };
    
    // 任意可调用对象委托模版
    template<class AnyFunT, typename ReturnT, typename ...ArgsT>
    class AnyFunDelegate : public IDelegate<ReturnT, ArgsT...>
    {
    public:
        AnyFunDelegate() = delete;
        explicit AnyFunDelegate(AnyFunT&& fun) : func(fun) { };

        virtual ReturnT operator() (ArgsT... args) noexcept override
        {
            return func(args...);
        }

        std::decay_t<AnyFunT> func;
    };
    
};

template<typename ReturnT, typename ...ArgsT>
class SingleDelegate final
{
public:
    explicit SingleDelegate() = default;
    
    static CHTHOLLY_INLINE SingleDelegate<ReturnT, ArgsT...> CreateFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunType fun) noexcept;
    
    template<class ClassT>
    static CHTHOLLY_INLINE SingleDelegate<ReturnT, ArgsT...> CreateObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept;
    
    template<class ClassT>
    static CHTHOLLY_INLINE SingleDelegate<ReturnT, ArgsT...> CreateSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept;
    
    template<class AnyFunT>
    static CHTHOLLY_INLINE SingleDelegate<ReturnT, ArgsT...> CreateAnyFunc(AnyFunT&& func) noexcept;
    
    // 绑定全局或静态函数
    CHTHOLLY_INLINE void BindFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunType fun) noexcept;

    // 绑定类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE void BindObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept;

    // 绑定安全的类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE void BindSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept;
    
    // 绑定任意可调用对象
    template<class AnyFunT>
    CHTHOLLY_INLINE std::enable_if_t<!std::is_same_v<std::decay_t<AnyFunT>, SingleDelegate<ReturnT, ArgsT...>>> BindAnyFunc(AnyFunT&& func) noexcept;

    // 代理执行
    CHTHOLLY_INLINE ReturnT Invoke(ArgsT... args) noexcept;
    CHTHOLLY_INLINE ReturnT operator() (ArgsT... args) noexcept;
    
    // 解绑函数
    CHTHOLLY_INLINE void UnBind() noexcept;
    
private:
    std::shared_ptr<DelegateInterface::IDelegate<ReturnT, ArgsT...> > dlgtPtr;
};

struct DelegateHandle
{
private:
    template<typename ...ArgsT>
    friend class MultiDelegate;

    CHTHOLLY_INLINE DelegateHandle(uint32_t t, uint32_t i, void* p, void* b) : tdlgt(t), idlgt(i), pdlgt(p), bind(b) { }

    // Handle转化为字符串函数
    CHTHOLLY_INLINE std::string ToString() const noexcept
    {
        static std::stringstream ss;
        ss << tdlgt << idlgt << pdlgt << bind;
        std::string key = ss.str();
        ss.str("");
        return key;
    };

    uint32_t tdlgt; // 代理类型
    uint32_t idlgt; // 代理id
    void* pdlgt; // 代理类
    void* bind; // 绑定地址
};

template<typename ...ArgsT>
class MultiDelegate final
{
public:
    explicit MultiDelegate() = default;

    // 添加全局或静态函数
    CHTHOLLY_INLINE DelegateHandle AddFunction(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunType fun) noexcept;

    // 添加类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE DelegateHandle AddObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept;
    
    // 添加安全的类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE DelegateHandle AddSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept;
    
    // 添加任意可调用对象
    template<class AnyFunT>
    CHTHOLLY_INLINE std::enable_if_t<!std::is_same_v<std::decay_t<AnyFunT>, MultiDelegate<void, ArgsT...>>, DelegateHandle> AddAnyFunc(AnyFunT&& func) noexcept;
    
    // 多播代理执行
    void BroadCast(ArgsT... args) noexcept;
    CHTHOLLY_INLINE void operator() (ArgsT... args) noexcept;
    
    // 根据代理句柄移除
    CHTHOLLY_INLINE bool Remove(const DelegateHandle& handle) noexcept;
    
    // 移除全局或静态函数
    CHTHOLLY_INLINE bool Remove(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunType objFun) noexcept;

    // 移除类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE bool Remove(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept;
    
    // 移除安全类成员函数
    template<class ClassT>
    CHTHOLLY_INLINE bool Remove(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept;
    
    // 清空代理
    CHTHOLLY_INLINE void Clear() noexcept;
private:
    // 遍历dlgtMap，判断为真才会被移除
    template<class Comp>
    bool Remove(const Comp& rmLambda) noexcept;
    
    uint32_t dlgtId;
    std::unordered_map<std::string, std::shared_ptr<DelegateInterface::IDelegate<void, ArgsT...> > > dlgtMap;
};

}

template<typename ReturnT, typename ...ArgsT>
CHTHOLLY_INLINE ktl::SingleDelegate<ReturnT, ArgsT...> ktl::SingleDelegate<ReturnT, ArgsT...>::CreateFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunType fun) noexcept
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindFunction(fun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE ktl::SingleDelegate<ReturnT, ArgsT...> ktl::SingleDelegate<ReturnT, ArgsT...>::CreateObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindObject(obj, objFun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE ktl::SingleDelegate<ReturnT, ArgsT...> ktl::SingleDelegate<ReturnT, ArgsT...>::CreateSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindSafeObj(objShared, objFun);
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
template<class AnyFunT>
CHTHOLLY_INLINE ktl::SingleDelegate<ReturnT, ArgsT...> ktl::SingleDelegate<ReturnT, ArgsT...>::CreateAnyFunc(AnyFunT&& func) noexcept
{
    SingleDelegate<ReturnT, ArgsT...> dlgt;
    dlgt.BindAnyFunc(std::forward<AnyFunT>(func));
    return dlgt;
}

template<typename ReturnT, typename ...ArgsT>
CHTHOLLY_INLINE void ktl::SingleDelegate<ReturnT, ArgsT...>::BindFunction(typename DelegateInterface::FuncDelegate<ReturnT, ArgsT...>::FunType fun) noexcept
{
    dlgtPtr = std::make_shared<DelegateInterface::FuncDelegate<ReturnT, ArgsT...> >(fun);
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE void ktl::SingleDelegate<ReturnT, ArgsT...>::BindObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept
{
    dlgtPtr = std::make_shared<DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...> >(obj, objFun);
}

template<typename ReturnT, typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE void ktl::SingleDelegate<ReturnT, ArgsT...>::BindSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, ReturnT, ArgsT...>::FunT& objFun) noexcept
{
    dlgtPtr = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, ReturnT, ArgsT...> >(objShared, objFun);
}

template<typename ReturnT, typename ...ArgsT>
template<class AnyFunT>
CHTHOLLY_INLINE std::enable_if_t<!std::is_same_v<std::decay_t<AnyFunT>, ktl::SingleDelegate<ReturnT, ArgsT...>>> ktl::SingleDelegate<ReturnT, ArgsT...>::BindAnyFunc(AnyFunT&& func) noexcept
{
    dlgtPtr = std::make_shared<DelegateInterface::AnyFunDelegate<AnyFunT, ReturnT, ArgsT...> >(std::forward<AnyFunT>(func));
}

template<typename ReturnT, typename ...ArgsT>
CHTHOLLY_INLINE ReturnT ktl::SingleDelegate<ReturnT, ArgsT...>::Invoke(ArgsT ...args) noexcept
{
    return dlgtPtr.get() ? (*dlgtPtr)(args...) : ReturnT();
}

template<typename ReturnT, typename ...ArgsT>
CHTHOLLY_INLINE ReturnT ktl::SingleDelegate<ReturnT, ArgsT...>::operator()(ArgsT ...args) noexcept
{
    return Invoke(args...);
}

template<typename ReturnT, typename ...ArgsT>
CHTHOLLY_INLINE void ktl::SingleDelegate<ReturnT, ArgsT...>::UnBind() noexcept
{
    dlgtPtr.reset();
}

template<typename ...ArgsT>
CHTHOLLY_INLINE ktl::DelegateHandle ktl::MultiDelegate<ArgsT...>::AddFunction(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunType fun) noexcept
{
    DelegateHandle handle(0, dlgtId++, this, reinterpret_cast<void*>(fun));
    dlgtMap[handle.ToString()] = std::make_shared<DelegateInterface::FuncDelegate<void, ArgsT...> >(fun);
    
    return handle;
}

template<typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE ktl::DelegateHandle ktl::MultiDelegate<ArgsT...>::AddObject(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept
{
    DelegateHandle handle(0x1, dlgtId++, this, reinterpret_cast<void*>(obj));
    dlgtMap[handle.ToString()] = std::make_shared<DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...> >(obj, objFun);
    
    return handle;
}

template<typename ...ArgsT>
template<class ClassT>
CHTHOLLY_INLINE ktl::DelegateHandle ktl::MultiDelegate<ArgsT...>::AddSafeObj(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept
{
    DelegateHandle handle(0x2, dlgtId++, this, reinterpret_cast<void*>(objShared.get()));
    dlgtMap[handle.ToString()] = std::make_shared<DelegateInterface::ObjFuncSafeDelegate<ClassT, void, ArgsT...> >(objShared, objFun);
    
    return handle;
}

template<typename ...ArgsT>
template<class AnyFunT>
CHTHOLLY_INLINE std::enable_if_t<!std::is_same_v<std::decay_t<AnyFunT>, ktl::MultiDelegate<void, ArgsT...>>, ktl::DelegateHandle> ktl::MultiDelegate<ArgsT...>::AddAnyFunc(AnyFunT&& func) noexcept
{
    DelegateHandle handle(0x4, dlgtId++, this, 0);
    dlgtMap[handle.ToString()] = std::make_shared<DelegateInterface::AnyFunDelegate<AnyFunT, void, ArgsT...> >(std::forward<AnyFunT>(func));
    
    return handle;
}

template<typename ...ArgsT>
CHTHOLLY_INLINE void ktl::MultiDelegate<ArgsT...>::BroadCast(ArgsT ...args) noexcept
{
    for (const auto& it : dlgtMap)
    {
        (*(it.second))(args...);
    }
}

template<typename ...ArgsT>
CHTHOLLY_INLINE void ktl::MultiDelegate<ArgsT...>::operator()(ArgsT ...args) noexcept
{
    BroadCast(args...);
}

template<typename ...ArgsT>
CHTHOLLY_INLINE bool ktl::MultiDelegate<ArgsT...>::Remove(const ktl::DelegateHandle& handle) noexcept
{
    std::string key = handle.ToString();
    return dlgtMap.erase(key);
}

template<typename ...ArgsT>
CHTHOLLY_INLINE bool ktl::MultiDelegate<ArgsT...>::Remove(typename DelegateInterface::FuncDelegate<void, ArgsT...>::FunType objFun) noexcept
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
CHTHOLLY_INLINE bool ktl::MultiDelegate<ArgsT...>::Remove(ClassT* obj, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept
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
CHTHOLLY_INLINE bool ktl::MultiDelegate<ArgsT...>::Remove(const std::shared_ptr<ClassT>& objShared, const typename DelegateInterface::ObjFuncDelegate<ClassT, void, ArgsT...>::FunT& objFun) noexcept
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
CHTHOLLY_INLINE void ktl::MultiDelegate<ArgsT...>::Clear() noexcept
{
    //引用计数为0时自动释放对象
    dlgtMap.clear();
}

template<typename ...ArgsT>
template<class Comp>
bool ktl::MultiDelegate<ArgsT...>::Remove(const Comp& rmLambda) noexcept
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