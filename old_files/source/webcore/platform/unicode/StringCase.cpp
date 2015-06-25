
#include  "UChar.h"
#include  "Normalize.h"
#include  "UnicodeCase.h"
#include  "StringCase.h"


int32_t u_terminateUChars(UChar *dest, int32_t destCapacity, int32_t length, UErrorCode *pErrorCode) 
{
    if (pErrorCode!=NULL && U_SUCCESS(*pErrorCode)) {                    
        /* not a public function, so no complete argument checking */                                                                         
        if(length < 0) {                                                  
            /* assume that the caller handles this */                   
        } else if(length<destCapacity) {                                
            /* NUL-terminate the string, the NUL fits */                
            dest[length]=0;                                             
            /* unset the not-terminated warning but leave all others */ 
            if(*pErrorCode==U_STRING_NOT_TERMINATED_WARNING) {          
                *pErrorCode=U_ZERO_ERROR;                               
            }                                                           
        } else if(length==destCapacity) {                               
            /* unable to NUL-terminate, but the string itself fit - set a warning code */ 
            *pErrorCode=U_STRING_NOT_TERMINATED_WARNING;                
        } else /* length>destCapacity */ {                              
            /* even the string itself did not fit - set an error code */ 
            *pErrorCode=U_BUFFER_OVERFLOW_ERROR;                        
        }                                                               
    }
    return length;
}

enum {
    TO_LOWER,
    TO_UPPER,
    TO_TITLE,
    FOLD_CASE
};


int32_t u_strlen(const UChar *s) 
{
    const UChar *t = s;
    while(*t != 0) {
      ++t;
    }
    return t - s;
}


int32_t appendResult(UChar *dest, int32_t destIndex, int32_t destCapacity,
             int32_t result, const UChar *s) 
{
    USChar32 c;
    int32_t length;

    /* decode the result */
    if(result<0) {
        /* (not) original code point */
        c=~result;
        length=-1;
    } else if(result<=UCASE_MAX_STRING_LENGTH) {
        c=U_SENTINEL;
        length=result;
    } else {
        c=result;
        length=-1;
    }

    if(destIndex<destCapacity) {
        if(length<0) {
            UBool isError=FALSE;
            U16_APPEND(dest, destIndex, destCapacity, c, isError);
            if(isError) {
                destIndex+=U16_LENGTH(c);
            }
        } else {
            /* string */
            if((destIndex+length)<=destCapacity) {
                while(length>0) {
                    dest[destIndex++]=*s++;
                    --length;
                }
            } else {
                /* overflow */
                destIndex+=length;
            }
        }
    } else {
        /* preflight */
        if(length<0) {
            destIndex+=U16_LENGTH(c);
        } else {
            destIndex+=length;
        }
    }
    return destIndex;
}


int32_t ustr_foldCase(const UCaseProps *csp, UChar *dest, int32_t destCapacity, 
									const UChar *src, int32_t srcLength, uint32_t options, UErrorCode *pErrorCode) 
{
    int32_t srcIndex, destIndex;

    const UChar *s;
    USChar32 c, c2;

    srcIndex=destIndex=0;
    while(srcIndex<srcLength) {
        U16_NEXT(src, srcIndex, srcLength, c);
        c=ucase_toFullFolding(csp, c, &s, options);
        if((destIndex<destCapacity) && (c<0 ? (c2=~c)<=0xffff : UCASE_MAX_STRING_LENGTH<c && (c2=c)<=0xffff)) {
            dest[destIndex++]=(UChar)c2;
        } else {
            destIndex=appendResult(dest, destIndex, destCapacity, c, s);
        }
    }

    if(destIndex>destCapacity) {
        *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
    }
    return destIndex;
}


static USChar32 utf16_caseContextIterator(void *context, int8_t dir) 
{
    UCaseContext *csc=(UCaseContext *)context;
    USChar32 c;

    if(dir<0) {
        csc->index=csc->cpStart;
        csc->dir=dir;
    } else if(dir>0) {
        csc->index=csc->cpLimit;
        csc->dir=dir;
    } else {
        dir=csc->dir;
    }

    if(dir<0) {
        if(csc->start<csc->index) {
            U16_PREV((const UChar *)csc->p, csc->start, csc->index, c);
            return c;
        }
    } else {
        if(csc->index<csc->limit) {
            U16_NEXT((const UChar *)csc->p, csc->index, csc->limit, c);
            return c;
        }
    }
    return U_SENTINEL;
}

typedef int32_t UCaseMapFull(const UCaseProps *csp, USChar32 c,
             UCaseContextIterator *iter, void *context,
             const UChar **pString,
             const char *locale, int32_t *locCache);

static int32_t _caseMap(const UCaseProps *csp, UCaseMapFull *map, UChar *dest, int32_t destCapacity,
									const UChar *src, UCaseContext *csc, int32_t srcStart, int32_t srcLimit,
									const char *locale, int32_t *locCache, UErrorCode *pErrorCode) 
{
    const UChar *s;
    USChar32 c, c2;
    int32_t srcIndex, destIndex;

    srcIndex=srcStart;
    destIndex=0;
    while(srcIndex<srcLimit) {
        csc->cpStart=srcIndex;
        U16_NEXT(src, srcIndex, srcLimit, c);
        csc->cpLimit=srcIndex;
        c=map(csp, c, utf16_caseContextIterator, csc, &s, locale, locCache);
        if((destIndex<destCapacity) && (c<0 ? (c2=~c)<=0xffff : UCASE_MAX_STRING_LENGTH<c && (c2=c)<=0xffff)) {
            /* fast path version of appendResult() for BMP results */
            dest[destIndex++]=(UChar)c2;
        } else {
            destIndex=appendResult(dest, destIndex, destCapacity, c, s);
        }
    }

    if(destIndex>destCapacity) {
        *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
    }
    return destIndex;
}


static int32_t caseMap(UChar *dest, int32_t destCapacity, const UChar *src, int32_t srcLength,
			UBreakIterator *titleIter, const char *locale,uint32_t options, int32_t toWhichCase,UErrorCode *pErrorCode) 
{
    UChar buffer[300];
    UChar *temp;

    const UCaseProps *csp;

    int32_t destLength;
    UBool ownTitleIter;

    /* check argument values */
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if( destCapacity<0 ||
        (dest==NULL && destCapacity>0) ||
        src==NULL ||
        srcLength<-1
    ) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    csp=ucase_getSingleton(pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }

    if(srcLength==-1) {
        srcLength=u_strlen(src);
    }

    if( dest!=NULL &&
        ((src>=dest && src<(dest+destCapacity)) ||
         (dest>=src && dest<(src+srcLength)))
    ) {
        if(destCapacity<=(sizeof(buffer)/U_SIZEOF_UCHAR)) {
            temp=buffer;
        } else {
            temp=(UChar *)malloc(destCapacity*U_SIZEOF_UCHAR);
            if(temp==NULL) {
                *pErrorCode=U_MEMORY_ALLOCATION_ERROR;
                return 0;
            }
        }
    } else {
        temp=dest;
    }

    ownTitleIter=FALSE;
    destLength=0;

    if(toWhichCase==FOLD_CASE) {
        destLength=ustr_foldCase(csp, temp, destCapacity, src, srcLength,
                                 options, pErrorCode);
    } else {
        UCaseContext csc={ NULL };
        int32_t locCache;

        csc.p=(void *)src;
        csc.limit=srcLength;
        locCache=0;

        if(locale==NULL) {
            locale="";         //temp value may be error,for test
        }

        if(toWhichCase==TO_LOWER) {
            destLength=_caseMap(csp, ucase_toFullLower,
                                temp, destCapacity,
                                src, &csc,
                                0, srcLength,
                                locale, &locCache, pErrorCode);
        } else if(toWhichCase==TO_UPPER) {
            destLength=_caseMap(csp, ucase_toFullUpper,
                                temp, destCapacity,
                                src, &csc,
                                0, srcLength,
                                locale, &locCache, pErrorCode);
        } else{} /* if(toWhichCase==TO_TITLE) */
    }
    if(temp!=dest) {
        if(destLength>0) {
            int32_t copyLength= destLength<=destCapacity ? destLength : destCapacity;
            if(copyLength>0) {
                //uprv_memmove(dest, temp, copyLength*U_SIZEOF_UCHAR);
                memmove(dest, temp, copyLength*U_SIZEOF_UCHAR);
            }
        }
        if(temp!=buffer) {
            //uprv_free(temp);
            free(temp);
        }
    }

    return u_terminateUChars(dest, destCapacity, destLength, pErrorCode);
}

int32_t u_strToLower(UChar *dest, int32_t destCapacity, const UChar *src, int32_t srcLength,
														const char *locale, UErrorCode *pErrorCode) 
{
    return caseMap(dest, destCapacity, src, srcLength, NULL, locale, 0, TO_LOWER, pErrorCode);
}


int32_t u_strToUpper(UChar *dest, int32_t destCapacity, const UChar *src, int32_t srcLength,
														const char *locale, UErrorCode *pErrorCode) 
{
    return caseMap(dest, destCapacity, src, srcLength, NULL, locale, 0, TO_UPPER, pErrorCode);
}

int32_t u_strFoldCase(UChar *dest, int32_t destCapacity, const UChar *src, int32_t srcLength,
														 uint32_t options, UErrorCode *pErrorCode) 
{
    return caseMap(dest, destCapacity, src, srcLength, NULL, NULL, options, FOLD_CASE, pErrorCode);
}

UChar * u_memset(UChar *dest, UChar c, int32_t count) {
    if(count > 0) {
        UChar *ptr = dest;
        UChar *limit = dest + count;

        while (ptr < limit) {
            *(ptr++) = c;
        }
    }
    return dest;
}

struct CmpEquivLevel {
    const UChar *start, *s, *limit;
};
typedef struct CmpEquivLevel CmpEquivLevel;

UChar *u_memcpy(UChar *dest, const UChar *src, int32_t count)
{
    return (UChar *)memcpy(dest, src, count*sizeof(UChar));
}

int32_t u_strcmpFold(const UChar *s1, int32_t length1, const UChar *s2, int32_t length2, 
														uint32_t options, UErrorCode *pErrorCode) 
{
    const UCaseProps *csp;

    const UChar *start1, *start2, *limit1, *limit2;

    const UChar *p;
    int32_t length;

    CmpEquivLevel stack1[2], stack2[2];

    UChar fold1[UCASE_MAX_STRING_LENGTH+1], fold2[UCASE_MAX_STRING_LENGTH+1];

    int32_t level1, level2;

    USChar32 c1, c2, cp1, cp2;

    csp=ucase_getSingleton(pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }

    /* initialize */
    start1=s1;
    if(length1==-1) {
        limit1=NULL;
    } else {
        limit1=s1+length1;
    }

    start2=s2;
    if(length2==-1) {
        limit2=NULL;
    } else {
        limit2=s2+length2;
    }

    level1=level2=0;
    c1=c2=-1;

    for(;;) {

        if(c1<0) {
            for(;;) {
                if(s1==limit1 || ((c1=*s1)==0 && (limit1==NULL || (options&_STRNCMP_STYLE)))) {
                    if(level1==0) {
                       c1=-1;
                        break;
                    }
                } else {
                    ++s1;
                    break;
                }

                do {
                    --level1;
                    start1=stack1[level1].start;
                } while(start1==NULL);
                s1=stack1[level1].s;
                limit1=stack1[level1].limit;
            }
        }

        if(c2<0) {
            for(;;) {
                if(s2==limit2 || ((c2=*s2)==0 && (limit2==NULL || (options&_STRNCMP_STYLE)))) {
                    if(level2==0) {
                        c2=-1;
                        break;
                    }
                } else {
                    ++s2;
                    break;
                }

                do {
                    --level2;
                    start2=stack2[level2].start;
                } while(start2==NULL);
                s2=stack2[level2].s;
                limit2=stack2[level2].limit;
            }
        }

        if(c1==c2) {
            if(c1<0) {
                return 0;   /* c1==c2==-1 indicating end of strings */
            }
            c1=c2=-1;       /* make us fetch new code units */
            	continue;
        } else if(c1<0) {
            return -1;      /* string 1 ends before string 2 */
        } else if(c2<0) {
            return 1;       /* string 2 ends before string 1 */
        }
        cp1=c1;
        if(U_IS_SURROGATE(c1)) {
            UChar c;

            if(U_IS_SURROGATE_LEAD(c1)) {
                if(s1!=limit1 && U16_IS_TRAIL(c=*s1)) {
                    cp1=U16_GET_SUPPLEMENTARY(c1, c);
                }
            } else /* isTrail(c1) */ {
                if(start1<=(s1-2) && U16_IS_LEAD(c=*(s1-2))) {
                    cp1=U16_GET_SUPPLEMENTARY(c, c1);
                }
            }
        }

        cp2=c2;
        if(U_IS_SURROGATE(c2)) {
            UChar c;

            if(U_IS_SURROGATE_LEAD(c2)) {
                if(s2!=limit2 && U16_IS_TRAIL(c=*s2)) {
                    cp2=U16_GET_SUPPLEMENTARY(c2, c);
                }
            } else /* isTrail(c2) */ {
                if(start2<=(s2-2) && U16_IS_LEAD(c=*(s2-2))) {
                    cp2=U16_GET_SUPPLEMENTARY(c, c2);
                }
            }
        }


        if( level1==0 &&
            (length=ucase_toFullFolding(csp, (USChar32)cp1, &p, options))>=0
        ) {
            if(U_IS_SURROGATE(c1)) {
                if(U_IS_SURROGATE_LEAD(c1)) {
                    ++s1;
                } else /* isTrail(c1) */ {
                    --s2;
                    c2=*(s2-1);
                }
            }

            stack1[0].start=start1;
            stack1[0].s=s1;
            stack1[0].limit=limit1;
            ++level1;

            if(length<=UCASE_MAX_STRING_LENGTH) {
                u_memcpy(fold1, p, length);
            } else {
                int32_t i=0;
                U16_APPEND_UNSAFE(fold1, i, length);
                length=i;
            }

            start1=s1=fold1;
            limit1=fold1+length;

            c1=-1;
            continue;
        }

        if( level2==0 &&
            (length=ucase_toFullFolding(csp, (USChar32)cp2, &p, options))>=0
        ) {
            if(U_IS_SURROGATE(c2)) {
                if(U_IS_SURROGATE_LEAD(c2)) {
                    ++s2;
                } else /* isTrail(c2) */ {
                    --s1;
                    c1=*(s1-1);
                }
            }

            stack2[0].start=start2;
            stack2[0].s=s2;
            stack2[0].limit=limit2;
            ++level2;

            if(length<=UCASE_MAX_STRING_LENGTH) {
                u_memcpy(fold2, p, length);
            } else {
                int32_t i=0;
                U16_APPEND_UNSAFE(fold2, i, length);
                length=i;
            }

            start2=s2=fold2;
            limit2=fold2+length;

            c2=-1;
            continue;
        }


        if(c1>=0xd800 && c2>=0xd800 && (options&U_COMPARE_CODE_POINT_ORDER)) {
            if(
                (c1<=0xdbff && s1!=limit1 && U16_IS_TRAIL(*s1)) ||
                (U16_IS_TRAIL(c1) && start1!=(s1-1) && U16_IS_LEAD(*(s1-2)))
            ) {
            } else {
                c1-=0x2800;
            }

            if(
                (c2<=0xdbff && s2!=limit2 && U16_IS_TRAIL(*s2)) ||
                (U16_IS_TRAIL(c2) && start2!=(s2-1) && U16_IS_LEAD(*(s2-2)))
            ) {
            } else {
                c2-=0x2800;
            }
        }
        return c1-c2;
    }
}

int32_t u_memcasecmp(const UChar *s1, const UChar *s2, int32_t length, uint32_t options) 
{
    UErrorCode errorCode=U_ZERO_ERROR;
    return u_strcmpFold(s1, length, s2, length, options|U_COMPARE_IGNORE_CASE, &errorCode);
}




