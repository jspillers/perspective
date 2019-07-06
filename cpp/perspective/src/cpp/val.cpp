/******************************************************************************
 *
 * Copyright (c) 2019, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

#ifdef PSP_ENABLE_PYTHON

#include <perspective/first.h>
#include <perspective/val.h>

namespace perspective {
// FIXME: document this so it actually makes sense with context of technical choices
template <typename T>
t_val<T>::t_val(t_val<T>&& v)
    : m_val(std::move(v.m_val)) {}

template <typename T>
t_val<T>::t_val(const t_val<T>& v)
    : m_val(v.m_val) {}

template <typename T>
t_val<T>::t_val(T&& v)
    : m_val(std::move(v)) {}

template <typename T>
t_val<T>::t_val(const T& v)
    : m_val(v) {}

template <typename T>
template <typename F>
t_val<T>::t_val(F&& value)
    : m_val(std::move(value)) {}

template <typename T>
t_val<T>&
t_val<T>::operator=(T&& v) {
    m_val = std::move(v);
    return *this;
}

template <typename T>
t_val<T>&
t_val<T>::operator=(const T& v) {
    m_val = v;
    return *this;
}

template <typename T>
t_val<T>&
t_val<T>::operator=(t_val<T>&& v) {
    m_val = std::move(v.m_val);
    return *this;
}

template <typename T>
t_val<T>&
t_val<T>::operator=(const t_val& v) {
    m_val = v.m_val;
    return *this;
}

template <typename T>
t_val<T>
t_val<T>::array() {
    return t_val(py::list());
}

template <typename T>
t_val<T>
t_val<T>::object() {
    // dict as equivalent of JS object
    return t_val(py::dict());
}

template <typename T>
t_val<T>
t_val<T>::undefined() {
    // empty constructor is `None` object
    return t_val(py::object());
}

template <typename T>
t_val<T>
t_val<T>::null() {
    // `None` is both undefined & null
    return t_val(py::object());
}

template <typename T>
template <typename K>
t_val<T> t_val<T>::operator[](const K& key) const {
    return t_val(m_val[key]);
}

template <typename T>
template <typename... Args>
t_val<T>
t_val<T>::operator()(Args&&... args) const {
    T rval = m_val(std::forward<Args>(args)...);
    return t_val(rval);
}

// TODO: implement call() and as()

template <typename T>
bool
t_val<T>::isNull() const {
    return m_val.is_none();
}

template <typename T>
bool
t_val<T>::isUndefined() const {
    return m_val.is_none();
}

} // namespace perspective

#endif