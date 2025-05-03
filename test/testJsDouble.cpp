// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

///
/// \file testenv/testJsDouble.cpp

#include <pxr/js/pxr.h>
#include <pxr/js/json.h>
#include <pxr/tf/diagnosticLite.h>

#include <iostream>
#include <sstream>

JS_NAMESPACE_USING_DIRECTIVE

void TestStreamInterface(const double d)
{
    JsValue v(d);
    std::stringstream sstr;
    JsWriteToStream(v, sstr);
    std::cout << sstr.str() << std::endl;
    JsValue v2 = JsParseStream(sstr);
    TF_AXIOM(v2.IsReal());
    TF_AXIOM(v2.GetReal() == d);
}

void TestWriterInterface(const double d)
{
    std::stringstream sstr;
    JsWriter writer(sstr);
    writer.WriteValue(d);
    std::cout << sstr.str() << std::endl;
    JsValue v2 = JsParseStream(sstr);
    TF_AXIOM(v2.IsReal());
    TF_AXIOM(v2.GetReal() == d);
}

int main(int argc, char const *argv[])
{
    const double d = 0.42745098039215684;
    TestStreamInterface(d);
    TestWriterInterface(d);
}