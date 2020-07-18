///\file

/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2020 John Wellbelove, John Lagerquist

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef ETL_STRING_UTILITIES_INCLUDED
#define ETL_STRING_UTILITIES_INCLUDED

#include "platform.h"
#include "algorithm.h"
#include "enum_type.h"
#include "memory.h"
#include "char_traits.h"

#include <stdint.h>

namespace etl
{
  struct string_pad_direction
  {
    enum enum_type
    {
      LEFT,
      RIGHT,
    };

    ETL_DECLARE_ENUM_TYPE(string_pad_direction, int)
    ETL_ENUM_TYPE(LEFT,  "left")
    ETL_ENUM_TYPE(RIGHT, "right")
    ETL_END_ENUM_TYPE
  };

  template <typename TChar>
  struct whitespace;

  template <>
  struct whitespace<char>
  {
    static const char* value()
    {
      return " \t\n\r\f\v";
    }
  };

  template <>
  struct whitespace<wchar_t>
  {
    static const wchar_t* value()
    {
      return L" \t\n\r\f\v";
    }
  };

  template <>
  struct whitespace<char16_t>
  {
    static const char16_t* value()
    {
      return u" \t\n\r\f\v";
    }
  };

  template <>
  struct whitespace<char32_t>
  {
    static const char32_t* value()
    {
      return U" \t\n\r\f\v";
    }
  };

  //***************************************************************************
  /// trim_from_left
  /// Trim left of trim_characters
  //***************************************************************************
  template <typename TIString>
  void trim_from_left(TIString& s, typename TIString::const_pointer trim_characters)
  {
    size_t position = s.find_first_not_of(trim_characters);
    s.erase(0U, position);
  }

  //***************************************************************************
  /// trim_whitespace_left
  /// Trim left of whitespace
  //***************************************************************************
  template <typename TIString>
  void trim_whitespace_left(TIString& s)
  {
    trim_from_left(s, whitespace<typename TIString::value_type>::value());
  }

  //***************************************************************************
  /// trim_from_view_left
  /// Trim left of trim_characters
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_from_view_left(const TStringView& view, typename TStringView::const_pointer trim_characters)
  {
    size_t first = view.find_first_not_of(trim_characters);

    typename TStringView::const_pointer pbegin = view.data() + view.size();

    if (first != TStringView::npos)
    {
      pbegin = view.data() + first;
    }

    return TStringView(pbegin, etl::distance(pbegin, view.data() + view.size()));
  }

  //***************************************************************************
  /// trim_view_whitespace_left
  /// Trim left of whitespace
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view_whitespace_left(TStringView& s)
  {
    return trim_from_view_left(s, whitespace<typename TStringView::value_type>::value());
  }

  //***************************************************************************
  /// trim_left
  /// Trim left, up to, but not including, delimiters.
  //***************************************************************************
  template <typename TIString>
  void trim_left(TIString& s, typename TIString::const_pointer delimiters)
  {
    size_t p = s.find_first_of(delimiters);

    if (p == TIString::npos)
    {
      s.clear();
    }
    else
    {
      s.erase(0, p);
    }
  }

  //***************************************************************************
  /// trim_view_left
  /// View trim left, up to, but not including, delimiters.
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view_left(const TStringView& view, typename TStringView::const_pointer delimiters)
  {
    size_t first = view.find_first_of(delimiters);

    typename TStringView::const_pointer pbegin = view.data();

    if (first != TStringView::npos)
    {
      pbegin += first;
      return TStringView(pbegin, view.size() - first);
    }
    else
    {
      return TStringView(pbegin, size_t(0U));
    }
  }

  //***************************************************************************
  /// trim_from_right
  /// Trim right of trim_characters
  //***************************************************************************
  template <typename TIString>
  void trim_from_right(TIString& s, typename TIString::const_pointer trim_characters)
  {
    s.erase(s.find_last_not_of(trim_characters) + 1);
  }

  //***************************************************************************
  /// trim_whitespace_right
  /// Trim firght of whitespace
  //***************************************************************************
  template <typename TIString>
  void trim_whitespace_right(TIString& s)
  {
    trim_from_right(s, whitespace<typename TIString::value_type>::value());
  }

  //***************************************************************************
  /// trim_from_view_right
  /// Trim right of trim_characters
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_from_view_right(const TStringView& view, typename TStringView::const_pointer trim_characters)
  {
    size_t last = view.find_last_not_of(trim_characters) + 1;

    typename TStringView::const_pointer pend = view.data();

    if (last != TStringView::npos)
    {
      pend += last;
    }

    return TStringView(view.data(), etl::distance(view.data(), pend));
  }

  //***************************************************************************
  /// trim_view_whitespace_right
  /// Trim right of whitespace
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view_whitespace_right(TStringView& view)
  {
    return trim_from_view_right(view, whitespace<typename TStringView::value_type>::value());
  }

  //***************************************************************************
  /// trim_right
  //***************************************************************************
  template <typename TIString>
  void trim_right(TIString& s, typename TIString::const_pointer delimiters)
  {
    size_t p = s.find_last_of(delimiters);

    if (p == TIString::npos)
    {
      s.clear();
    }
    else
    {
      ++p;

      if (p != s.size())
      {
        s.erase(p);
      }
    }
  }

  //***************************************************************************
  /// trim_view_right
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view_right(const TStringView& view, typename TStringView::const_pointer delimiters)
  {
    size_t last = view.find_last_of(delimiters) + 1;

    typename TStringView::const_pointer pend = view.data();

    if (last != TStringView::npos)
    {
      pend += last;
      return TStringView(view.data(), etl::distance(view.data(), pend));
    }
    else
    {
      return TStringView(view.data(), size_t(0U));
    }
  }

  //***************************************************************************
  /// trim_from
  /// Trim left and right of trim_characters
  //***************************************************************************
  template <typename TIString>
  void trim_from(TIString& s, typename TIString::const_pointer trim_characters)
  {
    trim_from_left(s, trim_characters);
    trim_from_right(s, trim_characters);
  }

  //***************************************************************************
  /// trim_whitespace
  /// Trim both ends of whitespace
  //***************************************************************************
  template <typename TIString>
  void trim_whitespace(TIString& s)
  {
    trim_from(s, whitespace<typename TIString::value_type>::value());
  }

  //***************************************************************************
  /// trim_from_view
  /// Trim left and right of trim_characters
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_from_view(const TStringView& view, typename TStringView::const_pointer trim_characters)
  {
    size_t first = view.find_first_not_of(trim_characters);
    size_t last  = view.find_last_not_of(trim_characters) + 1;

    typename TStringView::const_pointer pbegin = view.data();
    typename TStringView::const_pointer pend   = view.data();

    if (first != TStringView::npos)
    {
      pbegin += first;
    }

    if (last != TStringView::npos)
    {
      pend += last;
    }

    return TStringView(pbegin, etl::distance(pbegin, pend));
  }

  //***************************************************************************
  /// trim_view_whitespace
  /// Trim both ends of whitespace
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view_whitespace(const TStringView& view)
  {
    return trim_from_view(view, whitespace<typename TStringView::value_type>::value());
  }

  //***************************************************************************
  /// trim_delimiters
  /// Trim left and right of trim_characters
  //***************************************************************************
  template <typename TIString>
  void trim(TIString& s, typename TIString::const_pointer delimiters)
  {
    trim_left(s, delimiters);
    trim_right(s, delimiters);
  }

  //***************************************************************************
  /// trim_view
  /// Trim left and right of trim_characters
  //***************************************************************************
  template <typename TStringView>
  TStringView trim_view(const TStringView& view, typename TStringView::const_pointer delimiters)
  {
    size_t first = view.find_first_of(delimiters);
    size_t last  = view.find_last_of(delimiters) + 1;

    typename TStringView::const_pointer pbegin = view.data();
    typename TStringView::const_pointer pend   = view.data();

    if (first != TStringView::npos)
    {
      pbegin += first;
    }

    if (last != TStringView::npos)
    {
      pend += last;
    }

    return TStringView(pbegin, etl::distance(pbegin, pend));
  }

  //***************************************************************************
  /// Get up to the first n characters.
  //***************************************************************************
  template <typename TIString>
  void left_n(TIString& s, size_t n)
  {
    n = (n > s.size()) ? s.size() : n;

    s.erase(s.begin() + n, s.end());
  }

  //***************************************************************************
  /// Get a view of up to the first n characters.
  //***************************************************************************
  template <typename TStringView>
  TStringView left_n_view(const TStringView& view, size_t n)
  {
    n = (n > view.size()) ? view.size() : n;

    return TStringView(etl::addressof(*view.begin()), n);
  }

  //***************************************************************************
  /// Get up to the last n characters.
  //***************************************************************************
  template <typename TIString>
  void right_n(TIString& s, size_t n)
  {
    n = (n > s.size()) ? s.size() : n;

    s.erase(s.begin(), s.end() - n);
  }

  //***************************************************************************
  /// Get a view of up to the last n characters.
  //***************************************************************************
  template <typename TStringView>
  TStringView right_n_view(const TStringView& view, size_t n)
  {
    n = (n > view.size()) ? view.size() : n;

    return TStringView(view.data() + view.size() - n, n);
  }

  //***************************************************************************
  /// reverse
  /// Reverse a string
  //***************************************************************************
  template <typename TIString>
  void reverse(TIString& s)
  {
    etl::reverse(s.begin(), s.end());
  }

  //***************************************************************************
  /// replace_characters
  //***************************************************************************
  template <typename TIString, typename TPair>
  void replace_characters(TIString& s,
                          const TPair* pairsbegin,
                          const TPair* pairsend)
  {
    while (pairsbegin != pairsend)
    {
      etl::replace(s.begin(), s.end(), pairsbegin->first, pairsbegin->second);
      ++pairsbegin;
    }
  }

  //***************************************************************************
  /// replace_strings
  //***************************************************************************
  template <typename TIString, typename TPair>
  void replace_strings(TIString& s,
                        const TPair* pairsbegin,
                        const TPair* pairsend)
  {
    while (pairsbegin != pairsend)
    {
      const typename TIString::value_type* p_old = pairsbegin->first;
      const typename TIString::value_type* p_new = pairsbegin->second;

      size_t position = 0U;

      do
      {
        position = s.find(p_old, position);
        if (position != TIString::npos)
        {
          s.replace(position, etl::strlen(p_old), p_new, etl::strlen(p_new));
          position += etl::strlen(p_new);
        }
      } while (position != TIString::npos);

      ++pairsbegin;
    }
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  template <typename TIterator, typename TPointer>
  TIterator find_first_of(TIterator first, TIterator last, TPointer delimiters)
  {
    TIterator itr(first);

    while (itr != last)
    {
      TPointer pd = delimiters;

      while (*pd != 0)
      {
        if (*itr == *pd)
        {
          return itr;
        }

        ++pd;
      }

      ++itr;
    }

    return last;
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::iterator find_first_of(TIString& s, TPointer delimiters)
  {
    return find_first_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::const_iterator find_first_of(const TIString& s, TPointer delimiters)
  {
    return find_first_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find first not of any of delimiters within the string
  //*********************************************************************
  template <typename TIterator, typename TPointer>
  TIterator find_first_not_of(TIterator first, TIterator last, TPointer delimiters)
  {
    TIterator itr(first);

    while (itr != last)
    {
      TPointer pd = delimiters;

      bool found = false;

      while (*pd != 0)
      {
        if (*itr == *pd)
        {
          found = true;
          break;
        }

        ++pd;
      }

      if (!found)
      {
        return itr;
      }

      ++itr;
    }

    return last;
  }

  //*********************************************************************
  /// Find first not of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::iterator find_first_not_of(TIString& s, TPointer delimiters)
  {
    return find_first_not_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find first not of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::const_iterator find_first_not_of(const TIString& s, TPointer delimiters)
  {
    return find_first_not_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  template <typename TIterator, typename TPointer>
  TIterator find_last_of(TIterator first, TIterator last, TPointer delimiters)
  {
    if (first == last)
    {
      return last;
    }

    TIterator itr(last);
    TIterator end(first);

    do
    {
      --itr;

      TPointer pd = delimiters;

      while (*pd != 0)
      {
        if (*itr == *pd)
        {
          return itr;
        }

        ++pd;
      }
    } while (itr != end);

    return last;
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::iterator find_last_of(TIString& s, TPointer delimiters)
  {
    return find_last_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::const_iterator find_last_of(const TIString& s, TPointer delimiters)
  {
    return find_last_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last not of any of delimiters within the string
  //*********************************************************************
  template <typename TIterator, typename TPointer>
  TIterator find_last_not_of(TIterator first, TIterator last, TPointer delimiters)
  {
    if (first == last)
    {
      return last;
    }

    TIterator itr(last);
    TIterator end(first);

    do
    {
      --itr;

      TPointer pd = delimiters;

      bool found = false;

      while (*pd != 0)
      {
        if (*itr == *pd)
        {
          found = true;
          break;
        }

        ++pd;
      }

      if (!found)
      {
        return itr;
      }
    } while (itr != end);

    return last;
  }

  //*********************************************************************
  /// Find last not of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::iterator find_last_not_of(TIString& s, TPointer delimiters)
  {
    return find_last_not_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last not of any of delimiters within the string
  //*********************************************************************
  template <typename TIString, typename TPointer>
  typename TIString::const_iterator find_last_not_of(const TIString& s, TPointer delimiters)
  {
    return find_last_not_of(s.begin(), s.end(), delimiters);
  }

  //***************************************************************************
  /// get_token
  //***************************************************************************
  template <typename TIString, typename TStringView>
  TStringView get_token(const TIString& s, typename TIString::const_pointer delimiters, const TStringView& last_view)
  {
    size_t position = 0U;

    // Does the last_view have valid data?
    if (last_view.data() != ETL_NULLPTR)
    {
      position = etl::distance(etl::addressof(*s.begin()), addressof(*last_view.begin()) + last_view.size());
    }

    typename TIString::const_iterator first = s.begin() + position;
    typename TIString::const_iterator last;

    // Look for the start of the next token.
    first = find_first_not_of(first, s.end(), delimiters);
    last  = find_first_of(first, s.end(), delimiters);

    size_t view_length = etl::distance(first, last);

    if (view_length != 0)
    {
      return TStringView(etl::addressof(*first), view_length);
    }
    else
    {
      return TStringView();
    }
  }

  //***************************************************************************
  /// pad_left
  //***************************************************************************
  template <typename TIString>
  void pad_left(TIString& s, size_t required_size, typename TIString::value_type pad_char)
  {
    required_size = etl::min(required_size, s.max_size());

    if (required_size > s.size())
    {
      required_size -= s.size();
      s.insert(0U, required_size, pad_char);
    }
  }

  //***************************************************************************
  /// pad_right
  //***************************************************************************
  template <typename TIString>
  void pad_right(TIString& s, size_t required_size, typename TIString::value_type pad_char)
  {
    required_size = etl::min(required_size, s.max_size());

    if (required_size > s.size())
    {
      required_size -= s.size();
      s.insert(s.size(), required_size, pad_char);
    }
  }

  //***************************************************************************
  /// pad
  //***************************************************************************
  template <typename TIString>
  void pad(TIString& s, size_t required_size, string_pad_direction pad_direction, typename TIString::value_type pad_char)
  {
    switch (int(pad_direction))
    {
      case string_pad_direction::LEFT:
      {
        pad_left(s, required_size, pad_char);
        break;
      }

      case string_pad_direction::RIGHT:
      {
        pad_right(s, required_size, pad_char);
        break;
      }

      default:
      {
        break;
      }
    }
  }
}

#endif