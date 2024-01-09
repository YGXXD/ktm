#ifndef _KTM_QUAT_H_
#define _KTM_QUAT_H_

#include "vec.h"
#include "mat.h"
#include "Math/interface/ICommon/IArray.h"
#include "Math/interface/IQuaternion/IQuatData.h"
#include "Math/interface/IQuaternion/IQuatMake.h"
#include "Math/interface/IQuaternion/IQuatArray.h"
#include "Math/interface/IQuaternion/IQuatOpt.h"

namespace ktm
{
template<typename T>
struct quat<T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatMake, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IQuatData, ktm::IQuatMake, ktm::IQuatArray, ktm::IQuatOpt>, quat<T>>;
    using Father::Father;
};
}

#include "Math/detail/Quaternion/QuatOpt.inl"
#include "Math/detail/Quaternion/QuatOptSimd.inl"

#endif