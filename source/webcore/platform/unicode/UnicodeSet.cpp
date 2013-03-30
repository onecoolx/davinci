
#include "UnicodeSet.h"
#include "UnicodeTrie.h"
#include "UnicodeCase.h"
#include "StringCase.h"

#define UNICODESET_HIGH 0x0110000

#define UNICODESET_LOW 0x000000

#define START_EXTRA 16

#define GROW_EXTRA START_EXTRA

#define DEFUALT_CAPACITY 8

#define HINT_KEY_POINTER   (1)
#define HINT_KEY_INTEGER   (0)



static int8_t compareUnicodeString(UHashTok t1, UHashTok t2) {
    const UnicodeString &a = *(const UnicodeString*)t1.pointer;
    const UnicodeString &b = *(const UnicodeString*)t2.pointer;
    return a.compare(b);
}

void UVector::removeAllElements(void) {
    if (deleter != 0) {
        for (int32_t i=0; i<count; ++i) {
            if (elements[i].pointer != 0) {
                (*deleter)(elements[i].pointer);
            }
        }
    }
    count = 0;
}


UVector::~UVector() {
    removeAllElements();
    free(elements);
    elements = 0;
}

void UVector::_init(int32_t initialCapacity, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }
    // Fix bogus initialCapacity values; avoid malloc(0)
    if (initialCapacity < 1) {
        initialCapacity = DEFUALT_CAPACITY;
    }
    elements = (UHashTok *)malloc(sizeof(UHashTok)*initialCapacity);
    if (elements == 0) {
        status = U_MEMORY_ALLOCATION_ERROR;
    } else {
        capacity = initialCapacity;
    }
}


UVector::UVector(UObjectDeleter *d, UKeyComparator *c, UErrorCode &status) :
    count(0),
    capacity(0),
    elements(0),
    deleter(d),
    comparer(c)
{
    _init(DEFUALT_CAPACITY, status);
}

int32_t UVector::indexOf(void* obj, int32_t startIndex) const {
    UHashTok key;
    key.pointer = obj;
    return indexOf(key, startIndex, HINT_KEY_POINTER);
}

int32_t UVector::indexOf(int32_t obj, int32_t startIndex) const {
    UHashTok key;
    key.integer = obj;
    return indexOf(key, startIndex, HINT_KEY_INTEGER);
}


int32_t UVector::indexOf(UHashTok key, int32_t startIndex, int8_t hint) const {
    int32_t i;
    if (comparer != 0) {
        for (i=startIndex; i<count; ++i) {
            if ((*comparer)(key, elements[i])) {
                return i;
            }
        }
    } else {
        for (i=startIndex; i<count; ++i) {
            if (hint & HINT_KEY_POINTER) {
                if (key.pointer == elements[i].pointer) {
                    return i;
                }
            } else {
                if (key.integer == elements[i].integer) {
                    return i;
                }
            }
        }
    }
    return -1;
}

UBool UVector::ensureCapacity(int32_t minimumCapacity, UErrorCode &status) {
    if (capacity >= minimumCapacity) {
        return TRUE;
    } else {
        int32_t newCap = capacity * 2;
        if (newCap < minimumCapacity) {
            newCap = minimumCapacity;
        }
        UHashTok* newElems = (UHashTok *)malloc(sizeof(UHashTok)*newCap);
        if (newElems == 0) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return FALSE;
        }
        memcpy(newElems, elements, sizeof(elements[0]) * count);
        free(elements);
        elements = newElems;
        capacity = newCap;
        return TRUE;
    }
}


void* UVector::orphanElementAt(int32_t index) {
    void* e = 0;
    if (0 <= index && index < count) {
        e = elements[index].pointer;
        for (int32_t i=index; i<count-1; ++i) {
            elements[i] = elements[i+1];
        }
        --count;
    }
    /* else index out of range */
    return e;
}

void UVector::removeElementAt(int32_t index) {
    void* e = orphanElementAt(index);
    if (e != 0 && deleter != 0) {
        (*deleter)(e);
    }
}

void UVector::setSize(int32_t newSize) {
    int32_t i;
    if (newSize < 0) {
        return;
    }
    if (newSize > count) {
        UErrorCode ec = U_ZERO_ERROR;
        if (!ensureCapacity(newSize, ec)) {
            return;
        }
        UHashTok empty;
        empty.pointer = NULL;
        empty.integer = 0;
        for (i=count; i<newSize; ++i) {
            elements[i] = empty;
        }
    } else {
        /* Most efficient to count down */
        for (i=count-1; i>=newSize; --i) {
            removeElementAt(i);
        }
    }
    count = newSize;
}


UBool UVector::operator==(const UVector& other) {
    int32_t i;
    if (count != other.count) return FALSE;
    if (comparer != NULL) {
        // Compare using this object's comparer
        for (i=0; i<count; ++i) {
            if (!(*comparer)(elements[i], other.elements[i])) {
                return FALSE;
            }
        }
    }
    return TRUE;
}


void UVector::assign(const UVector& other, UTokenAssigner *assign, UErrorCode &ec) {
    if (ensureCapacity(other.count, ec)) {
        setSize(other.count);
        for (int32_t i=0; i<other.count; ++i) {
            if (elements[i].pointer != 0 && deleter != 0) {
                (*deleter)(elements[i].pointer);
            }
            (*assign)(&elements[i], &other.elements[i]);
        }
    }
}

void* UVector::elementAt(int32_t index) const {
    return (0 <= index && index < count) ? elements[index].pointer : 0;
}

void UVector::sortedInsert(void* obj, USortComparator *compare, UErrorCode& ec) {
    UHashTok tok;
    tok.pointer = obj;
    sortedInsert(tok, compare, ec);
}

void UVector::sortedInsert(UHashTok tok, USortComparator *compare, UErrorCode& ec) {
    int32_t min = 0, max = count;
    while (min != max) {
        int32_t probe = (min + max) / 2;
        int8_t c = (*compare)(elements[probe], tok);
        if (c > 0) {
            max = probe;
        } else {
            min = probe + 1;
        }
    }
    if (ensureCapacity(count + 1, ec)) {
        for (int32_t i=count; i>min; --i) {
            elements[i] = elements[i-1];
        }
        elements[min] = tok;
        ++count;
    }
}

/**********************************************************************************/
/**********************************************************************************/
/*************************** UnicodeString code start *****************************/
/**********************************************************************************/
/**********************************************************************************/

UnicodeString::UnicodeString()
  : fLength(0),
    fCapacity(US_STACKBUF_SIZE),
    fArray(fStackBuffer),
    fFlags(kShortString)
{}


static UMtxAtomicFn  *pIncFn = NULL;
static UMtxAtomicFn  *pDecFn = NULL;
static const void *gIncDecContext  = NULL;

int32_t umtx_atomic_dec(int32_t *p) {
    int32_t retVal;
    if (pDecFn) {
        retVal = (*pDecFn)(gIncDecContext, p);
    } else {
        retVal = --(*p);
    }
    return retVal;
}

int32_t umtx_atomic_inc(int32_t *p)  {
    int32_t retVal;
    if (pIncFn) {
        retVal = (*pIncFn)(gIncDecContext, p);
    } else {
        retVal = ++(*p);
    }
    return retVal;
}


int32_t UnicodeString::removeRef()
{ return umtx_atomic_dec((int32_t *)fArray - 1);}


void UnicodeString::releaseArray() {
  if((fFlags & kRefCounted) && removeRef() == 0) {
    free((int32_t *)fArray - 1);
  }
}


UnicodeString::~UnicodeString()
{
  releaseArray();
}

inline UChar UnicodeString::doCharAt(int32_t offset) const
{
  if((uint32_t)offset < (uint32_t)fLength) {
    return fArray[offset];
  } else {
    return kInvalidUChar;
  }
}


inline UChar UnicodeString::charAt(int32_t offset) const
{ return doCharAt(offset); }


inline USChar32 UnicodeString::char32At(int32_t offset) const
{
  if((uint32_t)offset < (uint32_t)fLength) {
    USChar32 c;
    U16_GET(fArray, 0, offset, fLength, c);
    return c;
  } else {
    return kInvalidUChar;
  }
}



void UnicodeString::unBogus() {
  if(fFlags & kIsBogus) {
    fArray = fStackBuffer;
    fLength = 0;
    fCapacity = US_STACKBUF_SIZE;
    fFlags = kShortString;
  }
}


inline UBool UnicodeString::truncate(int32_t targetLength)
{
  if(isBogus() && targetLength == 0) {
    unBogus();
    return FALSE;
  } else if((uint32_t)targetLength < (uint32_t)fLength) {
    fLength = targetLength;
    return TRUE;
  } else {
    return FALSE;
  }
}

void UnicodeString::setToBogus()
{
  releaseArray();

  fArray = 0;
  fCapacity = fLength = 0;
  fFlags = kIsBogus;
}

void UnicodeString::addRef()
{  umtx_atomic_inc((int32_t *)fArray - 1);}



UBool UnicodeString::allocate(int32_t capacity) {
  if(capacity <= US_STACKBUF_SIZE) {
    fArray = fStackBuffer;
    fCapacity = US_STACKBUF_SIZE;
    fFlags = kShortString;
  } else {
    int32_t words = (int32_t)(((sizeof(int32_t) + capacity * U_SIZEOF_UCHAR + 15) & ~15) >> 2);
    int32_t *array = (int32_t*) malloc( sizeof(int32_t) * words );
    if(array != 0) {
      *array++ = 1;

      fArray = (UChar *)array;
      fCapacity = (int32_t)((words - 1) * (sizeof(int32_t) / U_SIZEOF_UCHAR));
      fFlags = kLongString;
    } else {
      fLength = 0;
      fCapacity = 0;
      fFlags = kIsBogus;
      return FALSE;
    }
  }
  return TRUE;
}


UnicodeString &
UnicodeString::copyFrom(const UnicodeString &src, UBool fastCopy) {
  if(this == 0 || this == &src) {
    return *this;
  }

  if(&src == 0 || src.isBogus()) {
    setToBogus();
    return *this;
  }

  releaseArray();

  fLength = src.fLength;
  if(fLength == 0) {
    fArray = fStackBuffer;
    fCapacity = US_STACKBUF_SIZE;
    fFlags = kShortString;
    return *this;
  }

  switch(src.fFlags) {
  case kShortString:
    fArray = fStackBuffer;
    fCapacity = US_STACKBUF_SIZE;
    fFlags = kShortString;
    memcpy(fStackBuffer, src.fArray, fLength * U_SIZEOF_UCHAR);
    break;
  case kLongString:
    ((UnicodeString &)src).addRef();
    fArray = src.fArray;
    fCapacity = src.fCapacity;
    fFlags = src.fFlags;
    break;
  case kReadonlyAlias:
    if(fastCopy) {
      fArray = src.fArray;
      fCapacity = src.fCapacity;
      fFlags = src.fFlags;
      break;
    }
  case kWritableAlias:
    if(allocate(fLength)) {
      memcpy(fArray, src.fArray, fLength * U_SIZEOF_UCHAR);
      break;
    }
  default:
    fArray = 0;
    fLength = 0;
    fCapacity = 0;
    fFlags = kIsBogus;
    break;
  }

  return *this;
}

inline UBool
UnicodeString::operator== (const UnicodeString& text) const
{
  if(isBogus()) {
    return text.isBogus();
  } else {
    return
      !text.isBogus() &&
      fLength == text.fLength &&
      doCompare(0, fLength, text, 0, text.fLength) == 0;
  }
}


UnicodeString &
UnicodeString::operator=(const UnicodeString &src) {
  return copyFrom(src);
}


UnicodeString::UnicodeString(const UnicodeString& that):
    fLength(0),
    fCapacity(US_STACKBUF_SIZE),
    fArray(fStackBuffer),
    fFlags(kShortString)
{
  copyFrom(that);
}

UnicodeString::UnicodeString(UChar ch)
  : fLength(1),
    fCapacity(US_STACKBUF_SIZE),
    fArray(fStackBuffer),
    fFlags(kShortString)
{
  fStackBuffer[0] = ch;
}

UnicodeString::UnicodeString(USChar32 ch)
  : fLength(1),
    fCapacity(US_STACKBUF_SIZE),
    fArray(fStackBuffer),
    fFlags(kShortString)
{
  int32_t i = 0;
  UBool isError = FALSE;
  U16_APPEND(fStackBuffer, i, US_STACKBUF_SIZE, ch, isError);
  fLength = i;
}


int32_t
UnicodeString::refCount() const 
{ 
//    umtx_lock(NULL);
    // Note: without the lock to force a memory barrier, we might see a very
    //       stale value on some multi-processor systems.
    int32_t  count = *((int32_t *)fArray - 1);
//    umtx_unlock(NULL);
    return count;
 }


// need to copy areas that may overlap
static
inline void
us_arrayCopy(const UChar *src, int32_t srcStart,
         UChar *dst, int32_t dstStart, int32_t count)
{
  if(count>0) {
    memmove(dst+dstStart, src+srcStart, (size_t)(count*sizeof(*src)));
  }
}


UBool
UnicodeString::cloneArrayIfNeeded(int32_t newCapacity,
                                  int32_t growCapacity,
                                  UBool doCopyArray,
                                  int32_t **pBufferToDelete,
                                  UBool forceClone) {
  if(newCapacity == -1) {
    newCapacity = fCapacity;
  }

  if((fFlags&(kOpenGetBuffer|kIsBogus))!=0) {
    return FALSE;
  }

  if(forceClone ||
     (fFlags & kBufferIsReadonly) ||
     (fFlags & kRefCounted && refCount() > 1) ||
     (newCapacity > fCapacity)
  ) {
    UChar *array = fArray;
    uint16_t flags = fFlags;

    if(growCapacity == -1) {
      growCapacity = newCapacity;
    } else if(newCapacity <= US_STACKBUF_SIZE && growCapacity > US_STACKBUF_SIZE) {
      growCapacity = US_STACKBUF_SIZE;
    }

    if(allocate(growCapacity) ||
       newCapacity < growCapacity && allocate(newCapacity)
    ) {
      if(doCopyArray) {
        if(fCapacity < fLength) {
          fLength = fCapacity;
        }
        us_arrayCopy(array, 0, fArray, 0, fLength);
      } else {
        fLength = 0;
      }

      if(flags & kRefCounted) {
        int32_t *pRefCount = ((int32_t *)array - 1);
        if(umtx_atomic_dec(pRefCount) == 0) {
          if(pBufferToDelete == 0) {
            free(pRefCount);
          } else {
            *pBufferToDelete = pRefCount;
          }
        }
      }
    } else {
      fArray = array;
      fFlags = flags;
      setToBogus();
      return FALSE;
    }
  }
  return TRUE;
}




UnicodeString&
UnicodeString::doReplace(int32_t start,
             int32_t length,
             const UChar *srcChars,
             int32_t srcStart,
             int32_t srcLength)
{
  if(isBogus()) {
    return *this;
  }

  if(srcChars == 0) {
    srcStart = srcLength = 0;
  } else if(srcLength < 0) {
    srcLength = u_strlen(srcChars + srcStart);
  }

  int32_t *bufferToDelete = 0;

  UChar *oldArray = fArray;
  int32_t oldLength = fLength;

  pinIndices(start, length);

  int32_t newSize = oldLength - length + srcLength;

  if(!cloneArrayIfNeeded(newSize, newSize + (newSize >> 2) + kGrowSize,
                         FALSE, &bufferToDelete)
  ) {
    return *this;
  }

  if(fArray != oldArray) {
    us_arrayCopy(oldArray, 0, fArray, 0, start);
    us_arrayCopy(oldArray, start + length,
                 fArray, start + srcLength,
                 oldLength - (start + length));
  } else if(length != srcLength) {
    us_arrayCopy(oldArray, start + length,
                 fArray, start + srcLength,
                 oldLength - (start + length));
  }

  us_arrayCopy(srcChars, srcStart, getArrayStart(), start, srcLength);

  fLength = newSize;

  if (bufferToDelete) {
    free(bufferToDelete);
  }

  return *this;
}


UnicodeString::UnicodeString(const UChar *text)
  : fLength(0),
    fCapacity(US_STACKBUF_SIZE),
    fArray(fStackBuffer),
    fFlags(kShortString)
{
  doReplace(0, 0, text, 0, -1);
}



void uhash_deleteUnicodeString(void *obj) {
    
    delete (UnicodeString*) obj;
}

UBool uhash_compareUnicodeString(const UHashTok key1, const UHashTok key2) {
    
    const UnicodeString *str1 = (const UnicodeString*) key1.pointer;
    const UnicodeString *str2 = (const UnicodeString*) key2.pointer;
    if (str1 == str2) {
        return TRUE;
    }
    if (str1 == NULL || str2 == NULL) {
        return FALSE;
    }
    return *str1 == *str2;
}

static inline USChar32 pinCodePoint(USChar32& c) {
    if (c < UNICODESET_LOW) {
        c = UNICODESET_LOW;
    } else if (c > (UNICODESET_HIGH-1)) {
        c = (UNICODESET_HIGH-1);
    }
    return c;
}

UBool UnicodeSet::allocateStrings() {
    UErrorCode ec = U_ZERO_ERROR;
    strings = new UVector(uhash_deleteUnicodeString,
                          uhash_compareUnicodeString, ec);
    if (U_FAILURE(ec)) {
        delete strings;
        strings = NULL;
        return FALSE;
    }
    return TRUE;
}


void UnicodeSet::ensureBufferCapacity(int32_t newLen) {
    if (buffer != NULL && newLen <= bufferCapacity)
        return;
    if (buffer) {
        free(buffer);
    }
    bufferCapacity = newLen + GROW_EXTRA;
    buffer = (USChar32*) malloc(sizeof(USChar32) * bufferCapacity);
}


void UnicodeSet::swapBuffers(void) {
    USChar32* temp = list;
    list = buffer;
    buffer = temp;

    int32_t c = capacity;
    capacity = bufferCapacity;
    bufferCapacity = c;
}


void UnicodeSet::exclusiveOr(const USChar32* other, int32_t otherLen, int8_t polarity) {
    ensureBufferCapacity(len + otherLen);
    int32_t i = 0, j = 0, k = 0;
    USChar32 a = list[i++];
    USChar32 b;
    if (polarity == 1 || polarity == 2) {
        b = UNICODESET_LOW;
        if (other[j] == UNICODESET_LOW) { // skip base if already LOW
            ++j;
            b = other[j];
        }
    } else {
        b = other[j++];
    }
    for (;;) {
        if (a < b) {
            buffer[k++] = a;
            a = list[i++];
        } else if (b < a) {
            buffer[k++] = b;
            b = other[j++];
        } else if (a != UNICODESET_HIGH) { // at this point, a == b
            a = list[i++];
            b = other[j++];
        } else { // DONE!
            buffer[k++] = UNICODESET_HIGH;
            len = k;
            break;
        }
    }
    swapBuffers();
    pat.truncate(0);
}


UnicodeSet& UnicodeSet::complement(USChar32 start, USChar32 end) {
    if (pinCodePoint(start) <= pinCodePoint(end)) {
        USChar32 range[3] = { start, end+1, UNICODESET_HIGH };
        exclusiveOr(range, 2, 0);
    }
    pat.truncate(0);
    return *this;
}


UnicodeSet::UnicodeSet() :
    len(1), capacity(1 + START_EXTRA), bufferCapacity(0),
    list(0), buffer(0), strings(0)
{
    list = (USChar32*) malloc(sizeof(USChar32) * capacity);
    if(list!=NULL){
        list[0] = UNICODESET_HIGH;
    }
    allocateStrings();
}

UnicodeSet::UnicodeSet(USChar32 start, USChar32 end) :
    len(1), capacity(1 + START_EXTRA), bufferCapacity(0),
    list(0), buffer(0), strings(0)
{
    list = (USChar32*) malloc(sizeof(USChar32) * capacity);
    if(list!=NULL){
        list[0] = UNICODESET_HIGH;
    }
    allocateStrings();
    complement(start, end);
}

UnicodeSet::UnicodeSet(const UnicodeSet& o) :
    len(0), capacity(o.len + GROW_EXTRA), bufferCapacity(0),
    list(0), buffer(0), strings(0)
{
    list = (USChar32*) malloc(sizeof(USChar32) * capacity);
    if(list!=NULL){
        allocateStrings();
        *this = o;
    }
}

UnicodeSet::~UnicodeSet() {
    free(list);
    if (buffer) {
        free(buffer);
    }
    delete strings;
}


void UnicodeSet::ensureCapacity(int32_t newLen) {
    if (newLen <= capacity)
        return;
    capacity = newLen + GROW_EXTRA;
    USChar32* temp = (USChar32*) malloc(sizeof(USChar32) * capacity);
    memcpy(temp, list, len*sizeof(USChar32));
    free(list);
    list = temp;
}


static void cloneUnicodeString(UHashTok *dst, UHashTok *src) {
    dst->pointer = new UnicodeString(*(UnicodeString*)src->pointer);
}


UnicodeSet& UnicodeSet::operator=(const UnicodeSet& o) {
    ensureCapacity(o.len);
    len = o.len;
    memcpy(list, o.list, len*sizeof(USChar32));
    UErrorCode ec = U_ZERO_ERROR;
    strings->assign(*o.strings, cloneUnicodeString, ec);
    pat = o.pat;
    return *this;
}

inline UBool UnicodeSet::operator!=(const UnicodeSet& o) const {
    return !operator==(o);
}

UBool UnicodeSet::operator==(const UnicodeSet& o) const {
    if (len != o.len) return FALSE;
    for (int32_t i = 0; i < len; ++i) {
        if (list[i] != o.list[i]) return FALSE;
    }
    if (*strings != *o.strings) return FALSE;
    return TRUE;
}


UnicodeSet& UnicodeSet::add(USChar32 start, USChar32 end) {
    if (pinCodePoint(start) < pinCodePoint(end)) {
        USChar32 range[3] = { start, end+1, UNICODESET_HIGH };
        add(range, 2, 0);
    } else if (start == end) {
        add(start);
    }
    return *this;
}


void UnicodeSet::_add(const UnicodeString& s) {
    UnicodeString* t = new UnicodeString(s);
    UErrorCode ec = U_ZERO_ERROR;
    strings->sortedInsert(t, compareUnicodeString, ec);
}

UnicodeSet& UnicodeSet::add(USChar32 c) {
    int32_t i = findCodePoint(pinCodePoint(c));
    if ((i & 1) != 0) return *this;
    if (c == list[i]-1) {
        list[i] = c;
        if (c == (UNICODESET_HIGH - 1)) {
            ensureCapacity(len+1);
            list[len++] = UNICODESET_HIGH;
        }
        if (i > 0 && c == list[i-1]) {
            USChar32* dst = list + i - 1;
            USChar32* src = dst + 2;
            USChar32* srclimit = list + len;
            while (src < srclimit) *(dst++) = *(src++);

            len -= 2;
        }
    }

    else if (i > 0 && c == list[i-1]) {
        list[i-1]++;
    }

    else {
         ensureCapacity(len+2);
        USChar32* src = list + len;
        USChar32* dst = src + 2;
        USChar32* srclimit = list + i;
        while (src > srclimit) *(--dst) = *(--src);

        list[i] = c;
        list[i+1] = c+1;
        len += 2;
    }

    pat.truncate(0);
    return *this;
}


static inline USChar32 max(USChar32 a, USChar32 b) {
    return (a > b) ? a : b;
}

void UnicodeSet::add(const USChar32* other, int32_t otherLen, int8_t polarity) {
    ensureBufferCapacity(len + otherLen);
    int32_t i = 0, j = 0, k = 0;
    USChar32 a = list[i++];
    USChar32 b = other[j++];
    for (;;) {
        switch (polarity) {
          case 0:
            if (a < b) {
                if (k > 0 && a <= buffer[k-1]) {
                    a = max(list[i], buffer[--k]);
                } else {
                    buffer[k++] = a;
                    a = list[i];
                }
                i++;
                polarity ^= 1;
            } else if (b < a) {
                if (k > 0 && b <= buffer[k-1]) {
                    b = max(other[j], buffer[--k]);
                } else {
                    buffer[k++] = b;
                    b = other[j];
                }
                j++;
                polarity ^= 2;
            } else {
                if (a == UNICODESET_HIGH) goto loop_end;
                if (k > 0 && a <= buffer[k-1]) {
                    a = max(list[i], buffer[--k]);
                } else {
                    buffer[k++] = a;
                    a = list[i];
                }
                i++;
                polarity ^= 1;
                b = other[j++];
                polarity ^= 2;
            }
            break;
          case 3:
            if (b <= a) {
                if (a == UNICODESET_HIGH) goto loop_end;
                buffer[k++] = a;
            } else {
                if (b == UNICODESET_HIGH) goto loop_end;
                buffer[k++] = b;
            }
            a = list[i++];
            polarity ^= 1;
            b = other[j++];
            polarity ^= 2;
            break;
          case 1:
            if (a < b) {
                buffer[k++] = a; a = list[i++]; polarity ^= 1;
            } else if (b < a) {
                b = other[j++];
                polarity ^= 2;
            } else {
                if (a == UNICODESET_HIGH) goto loop_end;
                a = list[i++];
                polarity ^= 1;
                b = other[j++];
                polarity ^= 2;
            }
            break;
          case 2:
            if (b < a) {
                buffer[k++] = b;
                b = other[j++];
                polarity ^= 2;
            } else  if (a < b) {
                a = list[i++];
                polarity ^= 1;
            } else {
                if (a == UNICODESET_HIGH) goto loop_end;
                a = list[i++];
                polarity ^= 1;
                b = other[j++];
                polarity ^= 2;
            }
            break;
        }
    }
 loop_end:
    buffer[k++] = UNICODESET_HIGH;
    len = k;
    swapBuffers();
    pat.truncate(0);
}


int32_t UnicodeSet::getSingleCP(const UnicodeString& s) {
    if (s.length() > 2) return -1;
    if (s.length() == 1) return s.charAt(0);

    USChar32 cp = s.char32At(0);
    if (cp > 0xFFFF) {
        return cp;
    }
    return -1;
}


UnicodeSet& UnicodeSet::addAll(const UnicodeSet& c) {
    add(c.list, c.len, 0);

    for (int32_t i=0; i<c.strings->size(); ++i) {
        const UnicodeString* s = (const UnicodeString*)c.strings->elementAt(i);
        if (!strings->contains((void*) s)) {
            _add(*s);
        }
    }
    return *this;
}


UBool UnicodeSet::contains(USChar32 c) const {
    if (c >= UNICODESET_HIGH) { // Don't need to check LOW bound
        return FALSE;
    }
    int32_t i = findCodePoint(c);
    return ((i & 1) != 0); // return true if odd
}


int32_t UnicodeSet::findCodePoint(USChar32 c) const {
    if (c < list[0])
        return 0;
    if (len >= 2 && c >= list[len-2])
        return len-1;
    int32_t lo = 0;
    int32_t hi = len - 1;
    for (;;) {
        int32_t i = (lo + hi) >> 1;
        if (i == lo) {
            break; // Found!
        } else if (c < list[i]) {
            hi = i;
        } else {
            lo = i;
        }
    }
    return hi;
}


UBool UnicodeSet::contains(USChar32 start, USChar32 end) const {
    int32_t i = findCodePoint(start);
    return ((i & 1) != 0 && end < list[i]);
}

UBool UnicodeSet::contains(const UnicodeString& s) const {
    if (s.length() == 0) return FALSE;
    int32_t cp = getSingleCP(s);
    if (cp < 0) {
        return strings->contains((void*) &s);
    } else {
        return contains((USChar32) cp);
    }
}

