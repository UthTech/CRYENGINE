// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "stdafx.h"
#include "Vca.h"

#if defined(CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE)
	#include "BaseObject.h"
	#include <Logger.h>
#endif  // CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE

namespace CryAudio
{
namespace Impl
{
namespace Fmod
{
//////////////////////////////////////////////////////////////////////////
void CVca::Set(IObject* const pIObject, float const value)
{
	SetGlobally(value);

#if defined(CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE)
	auto const pBaseObject = static_cast<CBaseObject const*>(pIObject);
	float const finalValue = m_multiplier * value + m_shift;
	Cry::Audio::Log(ELogType::Warning, R"(Fmod - VCA "%s" was set to %f on object "%s". Consider setting it globally.)", m_name.c_str(), finalValue, pBaseObject->GetName());
#endif  // CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE
}

//////////////////////////////////////////////////////////////////////////
void CVca::SetGlobally(float const value)
{
#if defined(CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE)
	float const finalValue = m_multiplier * value + m_shift;
	m_pVca->setVolume(finalValue);
	g_vcaValues[m_name] = finalValue;
#else
	m_pVca->setVolume(m_multiplier * value + m_shift);
#endif  // CRY_AUDIO_IMPL_FMOD_USE_PRODUCTION_CODE
}
} // namespace Fmod
} // namespace Impl
} // namespace CryAudio