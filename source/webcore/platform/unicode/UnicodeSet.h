
#ifndef _UnicodeSet_h
#define _UnicodeSet_h

#include "UChar.h"
#include "UnicodeGlobal.h"
#include "UnicodeTrie.h"

typedef union {
    void*   pointer;
    int32_t integer;
} UHashTok;

typedef int8_t USortComparator(UHashTok tok1, UHashTok tok2);

typedef int32_t UMtxAtomicFn(const void *context, int32_t *p);


enum UMatchDegree {
    U_MISMATCH,
    U_PARTIAL_MATCH,
    U_MATCH
};

typedef UBool UKeyComparator(const UHashTok key1, const UHashTok key2);

typedef void UObjectDeleter(void* obj);

typedef void UTokenAssigner(UHashTok *dst, UHashTok *src);

class UVector
{
private:
    int32_t count;

    int32_t capacity;

    UHashTok* elements;

    UObjectDeleter *deleter;

    UKeyComparator *comparer;

public:
    UVector(UObjectDeleter *d, UKeyComparator *c, UErrorCode &status);

    virtual ~UVector();

    UBool operator==(const UVector& other);

    inline UBool operator!=(const UVector& other);

    void sortedInsert(void* obj, USortComparator *compare, UErrorCode& ec);

    void* elementAt(int32_t index) const;

    int32_t size(void) const;

    void setSize(int32_t newSize);

    void* orphanElementAt(int32_t index);

    int32_t indexOf(void* obj, int32_t startIndex = 0) const;

    int32_t indexOf(int32_t obj, int32_t startIndex = 0) const;

    UBool contains(void* obj) const;

    UBool contains(int32_t obj) const;

    void assign(const UVector& other, UTokenAssigner *assign, UErrorCode &ec);

    void removeElementAt(int32_t index);

    UBool ensureCapacity(int32_t minimumCapacity, UErrorCode &status);

    void removeAllElements();
private:
    void _init(int32_t initialCapacity, UErrorCode &status);

    int32_t indexOf(UHashTok key, int32_t startIndex = 0, int8_t hint = 0) const;

   void sortedInsert(UHashTok tok, USortComparator *compare, UErrorCode& ec);

};

inline UBool UVector::contains(void* obj) const {
    return indexOf(obj) >= 0;
}

inline UBool UVector::contains(int32_t obj) const {
    return indexOf(obj) >= 0;
}

inline UBool UVector::operator!=(const UVector& other) {
    return !operator==(other);
}


inline int32_t UVector::size(void) const {
    return count;
}



class UnicodeString
{
public:

  enum EInvariant {
    kInvariant
  };

  inline int32_t length(void) const;
  inline UBool isBogus(void) const;
  inline UBool operator== (const UnicodeString& text) const;
  inline UBool operator!= (const UnicodeString& text) const;
  inline UBool operator> (const UnicodeString& text) const;
  inline UBool operator< (const UnicodeString& text) const;
  inline UBool operator>= (const UnicodeString& text) const;
  inline UBool operator<= (const UnicodeString& text) const;
  UnicodeString &operator=(const UnicodeString &srcText);
  inline  UnicodeString& operator+= (UChar ch);
  inline  UnicodeString& operator+= (USChar32 ch);
  inline UnicodeString& operator+= (const UnicodeString& srcText);

  void setToBogus();
  inline int8_t compare(const UnicodeString& text) const;
  UnicodeString();
  UnicodeString(int32_t capacity, USChar32 c, int32_t count);
  UnicodeString(UChar ch);
  UnicodeString(USChar32 ch);
  UnicodeString(const UChar *text);

  UnicodeString(const UnicodeString& that);

  virtual ~UnicodeString();

  inline UChar charAt(int32_t offset) const;
  inline USChar32 char32At(int32_t offset) const;
  inline UBool truncate(int32_t targetLength);

private:

  inline int8_t
  doCompare(int32_t start,
           int32_t length,
           const UnicodeString& srcText,
           int32_t srcStart,
           int32_t srcLength) const;

  UBool cloneArrayIfNeeded(int32_t newCapacity = -1,
                            int32_t growCapacity = -1,
                            UBool doCopyArray = TRUE,
                            int32_t **pBufferToDelete = 0,
                            UBool forceClone = FALSE);

  int32_t removeRef(void);
  void addRef(void);
  int32_t refCount(void) const;
  // constants
  enum {
    US_STACKBUF_SIZE=7, // Size of stack buffer for small strings
    kInvalidUChar=0xffff, // invalid UChar index
    kGrowSize=128, // grow size for this buffer
    kInvalidHashCode=0, // invalid hash code
    kEmptyHashCode=1, // hash code for empty string

    // bit flag values for fFlags
    kIsBogus=1,         // this string is bogus, i.e., not valid or NULL
    kUsingStackBuffer=2,// fArray==fStackBuffer
    kRefCounted=4,      // there is a refCount field before the characters in fArray
    kBufferIsReadonly=8,// do not write to this buffer
    kOpenGetBuffer=16,  // getBuffer(minCapacity) was called (is "open"),
                        // and releaseBuffer(newLength) must be called

    kShortString=kUsingStackBuffer,
    kLongString=kRefCounted,
    kReadonlyAlias=kBufferIsReadonly,
    kWritableAlias=0
  };


   inline UChar doCharAt(int32_t offset)  const;

  void releaseArray(void);

  UnicodeString& doReplace(int32_t start,
               int32_t length,
               const UChar *srcChars,
               int32_t srcStart,
               int32_t srcLength);

  inline UChar* getArrayStart(void);
  inline const UChar* getArrayStart(void) const;

   void unBogus();

  UBool allocate(int32_t capacity);

  inline void pinIndices(int32_t& start,
                         int32_t& length) const;
  UnicodeString &copyFrom(const UnicodeString &src, UBool fastCopy=FALSE);

  //friend class StringCharacterIterator;   //changed by malin 07-03-28
  //friend class StringThreadTest;


  int32_t   fLength;        // number of characters in fArray
  int32_t   fCapacity;      // sizeof fArray
  UChar     *fArray;        // the Unicode data
  uint16_t  fFlags;         // bit flags: see constants above
  UChar     fStackBuffer [ US_STACKBUF_SIZE ]; // buffer for small strings

};

inline UBool
UnicodeString::isBogus() const
{ return (UBool)(fFlags & kIsBogus); }


inline UChar*
UnicodeString::getArrayStart()
{ return fArray; }

inline const UChar*
UnicodeString::getArrayStart() const
{ return fArray; }


inline void
UnicodeString::pinIndices(int32_t& start,
                          int32_t& _length) const
{
  if(start < 0) {
    start = 0;
  } else if(start > fLength) {
    start = fLength;
  }
  if(_length < 0) {
    _length = 0;
  } else if(_length > (fLength - start)) {
    _length = (fLength - start);
  }
}

inline int8_t
UnicodeString::compare(const UnicodeString& text) const
{ return doCompare(0, fLength, text, 0, text.fLength); }

inline int8_t
UnicodeString::doCompare(int32_t start,
              int32_t length,
              const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength) const
{
  if(srcText.isBogus()) {
    return (int8_t)!isBogus(); // 0 if both are bogus, 1 otherwise
  } else {
    srcText.pinIndices(srcStart, srcLength);
    return doCompare(start, length, srcText.fArray, srcStart, srcLength);
  }
}

inline int32_t
UnicodeString::length() const
{ return fLength; }


class SymbolTable {
public:
    enum { SYMBOL_REF = 0x0024 /*$*/ };
    virtual ~SymbolTable();
};


class UnicodeSet
{
    int32_t len; // length of list used; 0 <= len <= capacity
    int32_t capacity; // capacity of list
    int32_t bufferCapacity; // capacity of buffer
    USChar32* list; // MUST be terminated with HIGH
    USChar32* buffer; // internal buffer, may be NULL

    UVector* strings; // maintained in sorted order
    UnicodeString pat;

public:

    enum {
        MIN_VALUE = 0,
        MAX_VALUE = 0x10ffff
    };

public:

    UnicodeSet();

    UnicodeSet(USChar32 start, USChar32 end);

    UnicodeSet(const UnicodeString& pattern,
               UErrorCode& status);

    UnicodeSet(const UnicodeString& pattern,
               uint32_t options,
               const SymbolTable* symbols,
               UErrorCode& status);

    UnicodeSet(const UnicodeSet& o);

    virtual ~UnicodeSet();
    UnicodeSet& operator=(const UnicodeSet& o);

    virtual UBool operator==(const UnicodeSet& o) const;

    UBool operator!=(const UnicodeSet& o) const;

    virtual UBool contains(USChar32 c) const;

    virtual UBool contains(USChar32 start, USChar32 end) const;

    UBool contains(const UnicodeString& s) const;
    virtual UnicodeSet& complement(USChar32 start, USChar32 end);
	
    virtual UnicodeSet& add(USChar32 start, USChar32 end);
    UnicodeSet& add(USChar32 c);
    virtual UnicodeSet& addAll(const UnicodeSet& c);

    UnicodeSet& addAll(const UnicodeString& s);
private:

    int32_t findCodePoint(USChar32 c) const;

private:
    static int32_t getSingleCP(const UnicodeString& s);

    void _add(const UnicodeString& s);


    void ensureCapacity(int32_t newLen);
    void ensureBufferCapacity(int32_t newLen);
	void swapBuffers(void);
    UBool allocateStrings();
    void exclusiveOr(const USChar32* other, int32_t otherLen, int8_t polarity);

    void add(const USChar32* other, int32_t otherLen, int8_t polarity);
};

#endif
