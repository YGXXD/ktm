#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vector.h"
#include "Math/Interface/ICommon/IArray.h"
#include "Math/Interface/IQuaternion/IQuatData.h"
#include "Math/Interface/IQuaternion/IQuatMake.h"
#include "Math/Interface/IQuaternion/IQuatArray.h"
#include "Math/Interface/IQuaternion/IQuatOpt.h"

namespace ktm
{
template<typename T>
struct quat<T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatMake, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatMake, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>;
    using Father::Father;
};
}

#include "Math/Detail/Quaternion.inl"
#include "Math/Detail/QuaternionSimd.inl"

#endif