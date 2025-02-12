#ifndef __vector_fast_type_h_
#define __vector_fast_type_h_ 1

#include "OVplatform.h"

template<typename T>
struct value2size {
	enum { size = sizeof(T) * 8 };
};
    
class basic_fbit {
public:
	/**
	 * The fast bit
	 */
	union {
	    unsigned char bit : 1;
	};
	/**
	 * Ctor - set the bit to 0
	 */
	basic_fbit() : bit(0) { }
	/**
	 * Ctor - set the bit
	 * @param b The state for this bit
	 */
	basic_fbit(bool b) { bit = b ? 1 : 0; }
	/**
	 * copyble ctor
	 */
	basic_fbit(const basic_fbit& b) { bit = b.bit; }

	basic_fbit& operator = (const basic_fbit& other) {
	    bit = other.bit;
	}
	bool operator == (const basic_fbit& other) {
	    return bit == other.bit;
	}
	bool operator != (const basic_fbit& other) {
	    return bit != other.bit;
	}

	operator bool() { return bit == 1; }
	/**
	 * Flip the bit from 0 to 1 or from 0 to 1
	 */
	void flip() { bit = (bit ==1) ? 0 : 1; }
};

#include <stddef.h>

/**
* Template class for all fast types,
* a fast type can manupaleted bittable
*/
template <size_t Bits, typename TBaseType>
class fast_type {
public:
	using self_type = fast_type<Bits, TBaseType>;
	using value_type = TBaseType;
	using bit_type = fbit;

	/**
	 * The new type
	 */
	union {
	    /** The real value **/
	    value_type Value;
	    /** the value as bits */
	    bit_type bits[Bits];
	};
	/**
	 * Ctor
	 * @param value_type the value for this type
	 * @code
	 * fast_type<int> a(3);
	 * @endcode
	 */
	explicit fast_type(value_type v) : Value(v) {}
	fast_type(const fast_type& c) : Value(c.Value) { }

	/**
	 * Get the count of bits to set to 1
	 * @return The count of bits to set to 1
	 */
	unsigned int count() {
	    unsigned int i;
	    for(int j = 0; j < Bits; j++)
		i += bits[i].bit;
	    return i;
	}
	/**
	 * Get the count of bits to set to 0
	 * @return The count of bits to set to 0
	 */
	unsigned int zeros() {
	    return Bits - count();
	}
	/**
	 * Set the a bit on given position
	 * @param [in] pos The position to set
	 * @param [in] b The bit value to set
	 */
	unsigned int set(size_t pos, bool p) {
	    bits[pos].bit = p ? 1 : 0;
	}
	/**
	 * Get the numbers of bits
	 * @return The numbers of bits
	 */
	size_t size() { return Bits; }

	/**
	 * Operator to get the bit from given positon
	 * @return The bit from given positon
	 */
	value_type& operator [] (const size_t p) {
	    return bits[p];
	}
	/**
	 * Set this fast type value to a new value
	 * @return this
	 */
	self_type& operator = (value_type& v) {
	    Value = v; return *this;
	}

	self_type& operator = (self_type& other) {
	    Value = other.Value; return *this;
	}
	/**
	 * Is the other value with this equel
	 * @return True when equel and false when not
	 */
	bool operator == (self_type& other) {
	    return Value == other.Value;
	}
	/**
	 * Is the other value with this not equel
	 * @return True when not equel and false when not
	 */
	bool operator != (self_type& other) {
	    return Value != other.Value;
	}
	bool operator <= (self_type& other) {
	    return Value <= other.Value;
	}
	bool operator >= (self_type& other) {
	    return Value >= other.Value;
	}
	bool operator < (self_type& other) {
	    return Value < other.Value;
	}
	bool operator > (self_type& other) {
	    return Value > other.Value;
	}

	self_type& operator += (self_type& other) {
	    Value += other.Value; return *this;
	}
	self_type& operator -= (self_type& other) {
	    Value -= other.Value; return *this;
	}
	self_type& operator *= (self_type& other) {
	    Value *= other.Value; return *this;
	}
	self_type& operator &= (self_type& other) {
	    Value &= other.Value; return *this;
	}
	self_type& operator |= (self_type& other) {
	    Value |= other.Value; return *this;
	}
	self_type& operator ^= (self_type& other) {
	    Value ^= other.Value; return *this;
	}
	self_type& operator <<= (self_type& other) {
	    Value <<= other.Value; return *this;
	}
	self_type& operator >>= (self_type& other) {
	    Value >>= other.Value; return *this;
	}
	self_type& operator /= (self_type& other) {
	    Value /= other.Value; return *this;
	}
	self_type& operator += (value_type& v) {
	    Value += v; return *this;
	}
	self_type& operator -= (value_type& v) {
	    Value -= v; return *this;
	}
	self_type& operator *= (value_type& v) {
	    Value *= v; return *this;
	}
	self_type& operator /= (value_type& v) {
	    Value /= v; return *this;
	}
	self_type& operator <<= (value_type& v) {
	    Value <<= v; return *this;
	}
	self_type& operator >>= (value_type& v) {
	    Value >>= v; return *this;
	}
	self_type& operator - ( const self_type& rhs) {
	    return self_type(*this) -= rhs;
	}
	self_type& operator + ( const self_type& rhs) {
	    return self_type(*this) += rhs;
	}
	self_type& operator * ( const self_type& rhs) {
	    return self_type(*this) *= rhs;
	}
	self_type& operator / ( const self_type& rhs) {
	    return self_type(*this) /= rhs;
	}
	self_type& operator << ( const self_type& rhs) {
	    return self_type(*this) <<= rhs;
	}
	self_type& operator >> ( const self_type& rhs) {
	    return self_type(*this) >>= rhs;
	}
	self_type& operator | ( const self_type& rhs) {
	    self_type result = self_type(*this);
	    result.Value |= rhs.Value;
	    return result;
	}
	self_type& operator ^ ( const self_type& rhs) {
	    self_type result = self_type(*this);
	    result.Value ^= rhs.Value;
	    return result;
	}
	self_type& operator & ( const self_type& rhs) {
	    self_type result = self_type(*this);
	    result.Value &= rhs.Value;
	    return result;
	}
	self_type& operator ~ () {
	    self_type result = self_type(*this);
	    result.Value = ~result.Value;
	    return result;
	}

	self_type& operator ++ () {
	    Value++; return *this;
	}
	self_type& operator -- () {
	    Value--; return *this;
	}
	self_type& operator ~ () {
	    Value = ~Value; return *this;
	}
};

#if OPENVECTOR_SUPPORT_INT64 == 1
using ov_fint64_t          = fast_type<value2size<ov_slong_t>::size,       ov_slong_t>;
using ov_fuint64_t         = fast_type<value2size<ov_ulong_t>::size,       ov_ulong_t>;
#endif
#if OPENVECTOR_SUPPORT_FLOAT == 1
using ov_ffloat_t          = fast_type<value2size<ov_float_t>::size,       ov_float_t>;
#endif

#if OPENVECTOR_SUPPORT_DOUBLE == 1
using ov_fdouble_t         = fast_type<value2size<ov_double_t>::size,      ov_double_t>;
#endif

using ov_fsize_t           = fast_type<value2size<size_t>::size,           size_t>;

using ov_fint8_t           = fast_type<value2size<ov_schar_t>::size,       ov_schar_t>;
using ov_fint16_t          = fast_type<value2size<ov_sshort_t>::size,      ov_sshort_t>;
using ov_fint32_t          = fast_type<value2size<ov_sint_t>::size,        ov_sint_t>;

using ov_fuint8_t          = fast_type<value2size<ov_uchar_t>::size,       ov_uchar_t>;
using ov_fuint16_t         = fast_type<value2size<ov_ushort_t>::size,      ov_ushort_t>;
using ov_fuint32_t         = fast_type<value2size<ov_uint_t>::size,        ov_uint_t>;


#endif //__vector_fast_type_h_
