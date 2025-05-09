// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#ifndef PXR_JS_UTILS_H
#define PXR_JS_UTILS_H

/// \file js/utils.h

#include "./api.h"
#include "./value.h"

#include <optional>
#include <string>

namespace pxr {

typedef std::optional<JsValue> JsOptionalValue;

/// Returns the value associated with \p key in the given \p object. If no
/// such key exists, and the supplied default is not supplied, this method
/// returns an uninitialized optional JsValue. Otherwise, the \p 
/// defaultValue is returned.
JS_API
JsOptionalValue JsFindValue(
    const JsObject& object,
    const std::string& key,
    const JsOptionalValue& defaultValue = std::nullopt);

}  // namespace pxr

#endif // PXR_JS_UTILS_H
