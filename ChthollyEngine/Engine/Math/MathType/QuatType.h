#ifndef _QUAT_TYPE_H_
#define _QUAT_TYPE_H_

#include "VecType.h"
#include "Math/Interface/ICommon/IArray.h"
#include "Math/Interface/IQuaternion/IQuatData.h"
#include "Math/Interface/IQuaternion/IQuatArray.h"
#include "Math/Interface/IQuaternion/IQuatOpt.h"

namespace ktm
{
template<typename T>
struct quat<T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>;
    using Father::Father;
};

using fquat = quat<float>;
using dquat = quat<double>;

}

#endif