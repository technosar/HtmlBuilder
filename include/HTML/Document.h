/**
 * @file    Document.h
 * @ingroup HtmlBuilder
 * @brief   Root Element of the HTML Document Object Model.
 *
 * Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Element.h"

#include <sstream>
#include <string>

/// A simple C++ HTML Generator library.
namespace HTML {

/**
 * @brief Root Element of the HTML Document Object Model.
 *
 *   The Document is a specialized Element with restriction on what can be done on it,
 * since many aspects of the \<html\> root tag are well defined and constrained.
 */
class Document : public Element {
public:
    explicit Document(const char* apTitle) :
        Element(), mHead(*reinterpret_cast<Head*>(&mChildren[0])), mBody(*reinterpret_cast<Body*>(&mChildren[1])) {
        mHead << HTML::Title(apTitle);
    }
    explicit Document(const std::string& aTitle) :
        Element(), mHead(*reinterpret_cast<Head*>(&mChildren[0])), mBody(*reinterpret_cast<Body*>(&mChildren[1])) {
        mHead << HTML::Title(aTitle);
    }
    Document(const char* apTitle, Style&& aStyle) :
        Element(), mHead(*reinterpret_cast<Head*>(&mChildren[0])), mBody(*reinterpret_cast<Body*>(&mChildren[1])) {
        mHead << HTML::Title(apTitle);
        mHead << std::move(aStyle);
    }
    Document(const char* apTitle, const Style& aStyle) :
        Element(), mHead(*reinterpret_cast<Head*>(&mChildren[0])), mBody(*reinterpret_cast<Body*>(&mChildren[1])) {
        mHead << HTML::Title(apTitle);
        mHead << Style(aStyle);
    }

    Element& operator<<(Element&& aElement) {
        mBody << std::move(aElement);
        return mBody;
    }

    Element& head() {
        return mHead;
    }
    Element& body() {
        return mBody;
    }

    void lang(const char* apLang) {
        mHead.addAttribute("lang", apLang);
    }

    friend std::ostream& operator<< (std::ostream& aStream, const Document& aElement);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

private:
    std::ostream& toString(std::ostream& aStream) const {
        aStream << "<!DOCTYPE html>\n";
        Element::toString(aStream);
        return aStream;
    }

private:
    Head& mHead; ///< Reference to the first child Element \<head\>
    Body& mBody; ///< Reference to the second child Element \<body\>
};

inline std::ostream& operator<< (std::ostream& aStream, const Document& aDocument) {
    return aDocument.toString(aStream);
}

} // namespace HTML

