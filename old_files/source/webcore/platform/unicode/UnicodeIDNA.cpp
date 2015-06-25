
#include  "UChar.h"
#include  "UnicodeGlobal.h"
#include  "Normalize.h"
#include  "UnicodeIDNA.h"
#include  "StringCase.h"


#define MAX_STACK_BUFFER_SIZE 300

/* Punycode parameters for Bootstring */
#define BASE            36
#define TMIN            1
#define TMAX            26
#define SKEW            38
#define DAMP            700
#define INITIAL_BIAS    72
#define INITIAL_N       0x80

/* "Basic" Unicode/ASCII code points */
#define _HYPHEN         0X2d
#define HYPHEN          0x002d
#define DELIMITER       _HYPHEN

#define _ZERO_          0X30
#define _NINE           0x39

#define _SMALL_A        0X61
#define _SMALL_Z        0X7a

#define _CAPITAL_A      0X41
#define _CAPITAL_Z      0X5a

#define IS_BASIC(c) ((c)<0x80)
#define IS_BASIC_UPPERCASE(c) (_CAPITAL_A<=(c) && (c)<=_CAPITAL_Z)

#define MAX_CP_COUNT    200

/* The Max length of the labels should not be more than 64 */
#define MAX_LABEL_BUFFER_SIZE 100
#define MAX_LABEL_LENGTH 63

static const UChar ACE_PREFIX[] ={ 0x0078,0x006E,0x002d,0x002d } ;
#define ACE_PREFIX_LENGTH 4

#define CAPITAL_A        0x0041
#define CAPITAL_Z        0x005A
#define LOWER_CASE_DELTA 0x0020
#define FULL_STOP        0x002E


#include  "UnicodeIDNA_data.cpp"


//find wether the UNICODE codepoint is in the UIDNADB struct array
//parameters:
//result: 1  exist  ;0   not exist
static int  FindInCodeareaArray(const UIDNADB*  codeareap, int  arraylength, unsigned int codepoint)
{
    int min,max,tmp;
    
    min =0;
    max =arraylength -1;
    
    if(codepoint >codeareap[max].endcode || codepoint <codeareap[min].startcode)
        return 0;
        
    while(1)
    {
        if(codepoint >codeareap[min].endcode)
        {
            if(max  >min +1)
            {
                tmp =min +(max -min)/2;
                if(codepoint <codeareap[tmp].startcode)
                {
                    max =tmp;
                }
                else if(codepoint >codeareap[tmp].endcode)
                {
                    min =tmp;
                }
                else
                {
                    if(codepoint >=codeareap[tmp].startcode && codepoint <=codeareap[tmp].endcode)
                    {
                        return 1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                if((codepoint >=codeareap[min].startcode && codepoint <=codeareap[min].endcode) ||
                   (codepoint >=codeareap[max].startcode && codepoint <=codeareap[max].endcode))
                {
                    return 1;
                }
                else
                {
                    break;
                }
            }
        }
        else if(codepoint >=codeareap[min].startcode)
        {
            return 1;
        }
        else
        {
            break;
        }
    }
    
    return 0;
}



//find wether the UNICODE codepoint is in the ONEMAPONE struct array
//parameters:
//result:-1   not exist; else return the index of the array that the codepoint in the map table.
static int  FindInMapOnetable(const ONEMAPONE*  codeareap, int  arraylength, unsigned int codepoint)
{
    int min,max,tmp;
    
    min =0;
    max =arraylength -1;
    
    if(codepoint <codeareap[min].origincode || codepoint >codeareap[max].origincode)
        return -1;
        
    while(1)
    {
        if(codepoint >codeareap[min].origincode)
        {
            if(max >min +1)
            {
                tmp =min +(max -min)/2;
                if(codepoint ==codeareap[tmp].origincode)
                {
                    return tmp;
                }
                else if(codepoint >codeareap[tmp].origincode)
                {
                    min =tmp;
                }
                else
                {
                    max =tmp;
                }
            }
            else if(codepoint ==codeareap[min].origincode)
            {
                return min;
            }
            else if(codepoint ==codeareap[max].origincode)
            {
                return max;
            }
            else
            {
                break;
            }
        }
        else if(codepoint ==codeareap[min].origincode)
        {
            return min;
        }
        else
        {
            break;
        }
    }
    
    return -1;
}



//find wether the UNICODE codepoint is in the ONEMAPTWO struct array
//parameters:
//result:-1   not exist; else return the index of the array that the codepoint in the map table.
static int  FindInMapTwotable(const ONEMAPTWO*  codeareap, int  arraylength, unsigned int codepoint)
{
    int min,max,tmp;
    
    min =0;
    max =arraylength -1;
    
    if(codepoint <codeareap[min].origincode || codepoint >codeareap[max].origincode)
        return -1;
        
    while(1)
    {
        if(codepoint >codeareap[min].origincode)
        {
            if(max >min +1)
            {
                tmp =min +(max -min)/2;
                if(codepoint ==codeareap[tmp].origincode)
                {
                    return tmp;
                }
                else if(codepoint >codeareap[tmp].origincode)
                {
                    min =tmp;
                }
                else
                {
                    max =tmp;
                }
            }
            else if(codepoint ==codeareap[min].origincode)
            {
                return min;
            }
            else if(codepoint ==codeareap[max].origincode)
            {
                return max;
            }
            else
            {
                break;
            }
        }
        else if(codepoint ==codeareap[min].origincode)
        {
            return min;
        }
        else
        {
            break;
        }
    }
    
    return -1;
}



//find wether the UNICODE codepoint is in the ONEMAPTHREE struct array
//parameters:
//result:-1   not exist; else return the index of the array that the codepoint in the map table.
static int  FindInMapThreetable(const ONEMAPTHREE*  codeareap, int  arraylength, unsigned int codepoint)
{
    int min,max,tmp;
    
    min =0;
    max =arraylength -1;
    
    if(codepoint <codeareap[min].origincode || codepoint >codeareap[max].origincode)
        return -1;
        
    while(1)
    {
        if(codepoint >codeareap[min].origincode)
        {
            if(max >min +1)
            {
                tmp =min +(max -min)/2;
                if(codepoint ==codeareap[tmp].origincode)
                {
                    return tmp;
                }
                else if(codepoint >codeareap[tmp].origincode)
                {
                    min =tmp;
                }
                else
                {
                    max =tmp;
                }
            }
            else if(codepoint ==codeareap[min].origincode)
            {
                return min;
            }
            else if(codepoint ==codeareap[max].origincode)
            {
                return max;
            }
            else
            {
                break;
            }
        }
        else if(codepoint ==codeareap[min].origincode)
        {
            return min;
        }
        else
        {
            break;
        }
    }
    
    return -1;
}



//To find wether the UNICODE codepoint is a unsignedcodepoint
//parameters:
//result:0   is not a unsigned codepoint; 1 is a unsigned codepoint.
static int IsUnsignedCodepoint(unsigned int codepoint)
{
    return FindInCodeareaArray(unsignedCodepoints,UNSIGNEDCODEPOINT_NUM,codepoint);
}



//To find wether the UNICODE codepoint is maped to nothing, if the result is 1,the codepoint will be ommited from the 
//string for IDNA TO ASCII transcode
//parameters:
//result:0   is not map to nothing; 1 is map to nothing.
static int  IsMapedToNothing(unsigned int codepoint)
{
    return FindInCodeareaArray(MapNothing,MAPNOTHING_NUM,codepoint);
}


//To find wether the UNICODE codepoint is a prohibited character , if the result is 1,the IDNA TO ASCII transcode will
//return an error
//parameters:
//result:0   is not a prohibited character; 1 is a prohibited character.
static  int  IsProhibited(unsigned int codepoint)
{
    return FindInCodeareaArray(Prohibited,PROHIBITED,codepoint);
}


//To find wether the UNICODE codepoint 's bidirectional property is R or AL , if the result is 1,the codepoint 
//bidirectional property is R or AL
//parameters:
//result:0   is not a R or AL character; 1 is a R or AL character.
static int  IsBidiRandAL(unsigned int codepoint)
{
    return FindInCodeareaArray(Bidi_RandAL,BIDIRAL,codepoint);
}



//To find wether the UNICODE codepoint 's bidirectional property is L , if the result is 1,the codepoint 
//bidirectional property is L
//parameters:
//result:0   is not a L character; 1 is a L character.
static int  IsBidiL(unsigned int codepoint)
{
    return FindInCodeareaArray(Bidi_L,BIDIL,codepoint);
}



//get the map code points for the code points in the string specified by parameter src
//parameters:
//src :   source string to be mapped   ;   srcLength:   the source string length
//dest :  buffer to store the mapped string    ; destCapacity:  destination buffer length
//options:  the map action's optional selection   ;status :  buffer stores the error code
static int usprep_map( const UChar* src, int srcLength,UChar* dest, int destCapacity,int options,UErrorCode* status)
{
    int     destIndex=0;
    int     srcIndex;
    char    allowUnassigned;
//     short   value;
    int     index;
    USChar32 ch;

    // no error checking the caller check for error and arguments
    // no string length check the caller finds out the string length

    allowUnassigned = (char) ((options & USPREP_ALLOW_UNASSIGNED)>0);
    for(srcIndex=0;srcIndex<srcLength;)
    {
        U16_NEXT(src,srcIndex,srcLength,ch);

        // check if the source codepoint is unassigned
        if(IsUnsignedCodepoint(ch) && allowUnassigned == FALSE)
        {
            *status = U_STRINGPREP_UNASSIGNED_ERROR;
            return 0;
        }
        else if(IsMapedToNothing(ch))
        {
            continue;
        }
        else
        {
            if((index =FindInMapOnetable(MapOne,MAPONE,ch)) >=0)
            {
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapOne[index].mapcode;
                }
                destIndex++; /* for pre-flighting */
                continue;
            }
            else if((index =FindInMapTwotable(MapTwo,MAPTWO,ch)) >=0)
            {
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapTwo[index].mapcode1;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapTwo[index].mapcode2;
                }
                destIndex++; /* for pre-flighting */
                continue;
            }
            else if((index =FindInMapThreetable(MapThree,MAPTHREE,ch)) >=0)
            {
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapThree[index].mapcode1;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapThree[index].mapcode2;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapThree[index].mapcode3;
                }
                destIndex++; /* for pre-flighting */
                continue;
            }
            else if(index ==MapFour[0].origincode)
            {
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapFour[index].mapcode1;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapFour[index].mapcode2;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapFour[index].mapcode3;
                }
                destIndex++; /* for pre-flighting */
                
                /* copy mapping to destination */
                if(destIndex < destCapacity  )
                {
                    dest[destIndex] = MapFour[index].mapcode4;
                }
                destIndex++; /* for pre-flighting */
                
                continue;
            }
        }
        //copy the code point into destination
        if(ch <= 0xFFFF)
        {
            if(destIndex < destCapacity )
            {
                dest[destIndex] = (UChar)ch;
            }
            destIndex++;
        }
        else
        {
            if(destIndex+1 < destCapacity )
            {
                dest[destIndex]   = U16_LEAD(ch);
                dest[destIndex+1] = U16_TRAIL(ch);
            }
            destIndex +=2;
        }
    }
        
    return u_terminateUChars(dest, destCapacity, destIndex, status);
}




static int usprep_normalize(const UChar* src, int srcLength, UChar* dest, int destCapacity, UErrorCode* status )
{
    /*
     * Option UNORM_BEFORE_PRI_29:
     *
     * IDNA as interpreted by IETF members (see unicode mailing list 2004H1)
     * requires strict adherence to Unicode 3.2 normalization,
     * including buggy composition from before fixing Public Review Issue #29.
     * Note that this results in some valid but nonsensical text to be
     * either corrupted or rejected, depending on the text.
     * See http://www.unicode.org/review/resolved-pri.html#pri29
     * See unorm.cpp and cnormtst.c
     */
    return unorm_normalize(
        src, srcLength,
        UNORM_NFKC, 0x20|UNORM_BEFORE_PRI_29,
        dest, destCapacity,
        status);
}




static int usprep_prepare(const UChar* src, int srcLength, UChar* dest, int destCapacity, int options, UErrorCode* status )
{
    UChar b1Stack[MAX_STACK_BUFFER_SIZE], b2Stack[MAX_STACK_BUFFER_SIZE];
    UChar *b1 = b1Stack, *b2 = b2Stack;
    int32_t b1Len, b2Len=0, \
            b1Capacity = MAX_STACK_BUFFER_SIZE , \
            b2Capacity = MAX_STACK_BUFFER_SIZE;
//     uint16_t result;
    int32_t b2Index = 0;
    UCharDirection direction=U_CHAR_DIRECTION_COUNT, firstCharDir=U_CHAR_DIRECTION_COUNT;
    UBool leftToRight=FALSE, rightToLeft=FALSE;
    USChar32 ch;
    //int32_t rtlPos =-1, ltrPos =-1;
    
    
    // check error status
    if(status == NULL || U_FAILURE(*status))
    {
        return 0;
    }
    
    //check arguments
    if(src==NULL || srcLength<-1 || (dest==NULL && destCapacity!=0)) 
    {
        *status=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    //get the string length
    if(srcLength == -1)
    {
        srcLength = u_strlen(src);
    }
    // map
    b1Len = usprep_map(src, srcLength, b1, b1Capacity, options, status);

    if(*status == U_BUFFER_OVERFLOW_ERROR)
    {
        // redo processing of string
        /* we do not have enough room so grow the buffer*/
        b1 = (UChar*)malloc(b1Len * U_SIZEOF_UCHAR);
        if(b1==NULL)
        {
            *status = U_MEMORY_ALLOCATION_ERROR;
            goto CLEANUP;
        }

        *status = U_ZERO_ERROR; // reset error
        
        b1Len = usprep_map(src, srcLength, b1, b1Len, options, status);
    }

    // normalize
    //if(profile->doNFKC == TRUE){
    b2Len = usprep_normalize(b1,b1Len, b2,b2Capacity,status);
    
    if(*status == U_BUFFER_OVERFLOW_ERROR)
    {
        // redo processing of string
        /* we do not have enough room so grow the buffer*/
        b2 = (UChar*) malloc(b2Len * U_SIZEOF_UCHAR);
        if(b2==NULL)
        {
            *status = U_MEMORY_ALLOCATION_ERROR;
            goto CLEANUP;
        }

        *status = U_ZERO_ERROR; // reset error
    
        b2Len = usprep_normalize(b1,b1Len, b2,b2Len,status);
    }    

    if(U_FAILURE(*status))
    {
        goto CLEANUP;
    }
    
    // Prohibit and checkBiDi in one pass
    for(b2Index=0; b2Index<b2Len;)
    {
        
        ch = 0;

        U16_NEXT(b2, b2Index, b2Len, ch);

        //UTRIE_GET16(&profile->sprepTrie,ch,result);
        
        //type = getValues(result, value, isIndex);

        if( IsProhibited(ch))
        {
            *status = U_STRINGPREP_PROHIBITED_ERROR;
            //uprv_syntaxError(b1, b2Index-U16_LENGTH(ch), b2Len, parseError);
            goto CLEANUP;
        }

        //if(profile->checkBiDi) {
        //direction = ubidi_getClass(profile->bdp, ch);
        if(IsBidiRandAL(ch))
        {
            rightToLeft = TRUE;
            direction =U_RIGHT_TO_LEFT;
            if(firstCharDir == U_CHAR_DIRECTION_COUNT)
            {
                firstCharDir =U_RIGHT_TO_LEFT;
            }
        }
        else if(IsBidiL(ch))
        {
            leftToRight = TRUE;
            direction =U_LEFT_TO_RIGHT;
            if(firstCharDir == U_CHAR_DIRECTION_COUNT)
            {
                firstCharDir =U_LEFT_TO_RIGHT;
            }
        }
        else
        {
            direction =U_CHAR_DIRECTION_COUNT;
        }
        /*if(firstCharDir == U_CHAR_DIRECTION_COUNT)
        {
            firstCharDir = direction;
        }
        if(direction == U_LEFT_TO_RIGHT)
        {
            leftToRight = TRUE;
            //ltrPos = b2Index-1;
        }
        if(direction == U_RIGHT_TO_LEFT || direction == U_RIGHT_TO_LEFT_ARABIC)
        {
            rightToLeft = TRUE;
            //rtlPos = b2Index-1;
        }*/
        //}
    }           
    //if(profile->checkBiDi == TRUE){
        // satisfy 2
        if( leftToRight == TRUE && rightToLeft == TRUE)
        {
            *status = U_STRINGPREP_CHECK_BIDI_ERROR;
            //uprv_syntaxError(b2,(rtlPos>ltrPos) ? rtlPos : ltrPos, b2Len, parseError);
            goto CLEANUP;
        }

        //satisfy 3
        if( rightToLeft == TRUE && 
            !((firstCharDir == U_RIGHT_TO_LEFT || firstCharDir == U_RIGHT_TO_LEFT_ARABIC) &&
              (direction == U_RIGHT_TO_LEFT || direction == U_RIGHT_TO_LEFT_ARABIC))
           )
        {
            *status = U_STRINGPREP_CHECK_BIDI_ERROR;
            //uprv_syntaxError(b2, rtlPos, b2Len, parseError);
            return FALSE;
        }
    //}
    if(b2Len>0 && b2Len <= destCapacity)
    {
        memmove(dest,b2, b2Len*U_SIZEOF_UCHAR);
    }

CLEANUP:
    if(b1!=b1Stack){
        free(b1);
        b1=NULL;
    }

    if(b2!=b1Stack && b2!=b2Stack && b2!=b1 /* b1 should not be freed twice */)
    {
        free(b2);
        b2=NULL;
    }
    return u_terminateUChars(dest, destCapacity, b2Len, status);
}




static char asciiCaseMap(char b, char uppercase) 
{
    if(uppercase) 
    {
        if(_SMALL_A<=b && b<=_SMALL_Z) 
        {
            b-=(_SMALL_A-_CAPITAL_A);
        }
    } else 
    {
        if(_CAPITAL_A<=b && b<=_CAPITAL_Z) 
        {
            b+=(_SMALL_A-_CAPITAL_A);
        }
    }
    return b;
}


/*
 * digitToBasic() returns the basic code point whose value
 * (when used for representing integers) is d, which must be in the
 * range 0 to BASE-1. The lowercase form is used unless the uppercase flag is
 * nonzero, in which case the uppercase form is used.
 */
static char digitToBasic(int32_t digit, char uppercase) 
{
    /*  0..25 map to ASCII a..z or A..Z */
    /* 26..35 map to ASCII 0..9         */
    if(digit<26) 
    {
        if(uppercase) 
        {
            return (char)(_CAPITAL_A+digit);
        } 
        else 
        {
            return (char)(_SMALL_A+digit);
        }
    } 
    else 
    {
        return (char)((_ZERO_-26)+digit);
    }
}



/* Bias adaptation function. */
static int adaptBias(int delta, int length, char firstTime) 
{
    int count;

    if(firstTime) 
    {
        delta/=DAMP;
    } 
    else 
    {
        delta/=2;
    }

    delta+=delta/length;
    for(count=0; delta>((BASE-TMIN)*TMAX)/2; count+=BASE) 
    {
        delta/=(BASE-TMIN);
    }

    return count+(((BASE-TMIN+1)*delta)/(delta+SKEW));
}


static int u_strToPunycode(const UChar *src, int srcLength, UChar *dest, int destCapacity,
                const char *caseFlags,
                UErrorCode *pErrorCode) 
{

    int cpBuffer[MAX_CP_COUNT];
    int n, delta, handledCPCount, basicLength, destLength, bias, j, m, q, k, t, srcCPCount;
    UChar c, c2;

    /* argument checking */
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) 
    {
        return 0;
    }

    if(src==NULL || srcLength<-1 || (dest==NULL && destCapacity!=0)) 
    {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    /*
     * Handle the basic code points and
     * convert extended ones to UTF-32 in cpBuffer (caseFlag in sign bit):
     */
    srcCPCount=destLength=0;
    if(srcLength==-1) 
    {
        /* NUL-terminated input */
        for(j=0; /* no condition */; ++j) 
        {
            if((c=src[j])==0) 
            {
                break;
            }
            if(srcCPCount==MAX_CP_COUNT) 
            {
                /* too many input code points */
                *pErrorCode=U_INDEX_OUTOFBOUNDS_ERROR;
                return 0;
            }
            if(IS_BASIC(c)) 
            {
                cpBuffer[srcCPCount++]=0;
                if(destLength<destCapacity) 
                {
                    dest[destLength]=
                        caseFlags!=NULL ?
                            asciiCaseMap((char)c, caseFlags[j]) :
                            (char)c;
                }
                ++destLength;
            } 
            else 
            {
                n=(caseFlags!=NULL && caseFlags[j])<<31L;
                if(UTF_IS_SINGLE(c)) 
                {
                    n|=c;
                } 
                else if(UTF_IS_LEAD(c) && UTF_IS_TRAIL(c2=src[j+1])) 
                {
                    ++j;
                    n|=(int32_t)UTF16_GET_PAIR_VALUE(c, c2);
                } 
                else 
                {
                    /* error: unmatched surrogate */
                    *pErrorCode=U_INVALID_CHAR_FOUND;
                    return 0;
                }
                cpBuffer[srcCPCount++]=n;
            }
        }
    } 
    else 
    {
        /* length-specified input */
        for(j=0; j<srcLength; ++j) 
        {
            if(srcCPCount==MAX_CP_COUNT) 
            {
                /* too many input code points */
                *pErrorCode=U_INDEX_OUTOFBOUNDS_ERROR;
                return 0;
            }
            c=src[j];
            if(IS_BASIC(c)) 
            {
                if(destLength<destCapacity) 
                {
                    cpBuffer[srcCPCount++]=0;
                    dest[destLength]=
                        caseFlags!=NULL ?
                            asciiCaseMap((char)c, caseFlags[j]) :
                            (char)c;
                }
                ++destLength;
            } 
            else 
            {
                n=(caseFlags!=NULL && caseFlags[j])<<31L;
                if(UTF_IS_SINGLE(c)) 
                {
                    n|=c;
                } 
                else if(UTF_IS_LEAD(c) && (j+1)<srcLength && UTF_IS_TRAIL(c2=src[j+1])) 
                {
                    ++j;
                    n|=(int32_t)UTF16_GET_PAIR_VALUE(c, c2);
                } 
                else 
                {
                    /* error: unmatched surrogate */
                    *pErrorCode=U_INVALID_CHAR_FOUND;
                    return 0;
                }
                cpBuffer[srcCPCount++]=n;
            }
        }
    }

    /* Finish the basic string - if it is not empty - with a delimiter. */
    basicLength=destLength;
    if(basicLength>0) 
    {
        if(destLength<destCapacity) 
        {
            dest[destLength]=DELIMITER;
        }
        ++destLength;
    }

    /*
     * handledCPCount is the number of code points that have been handled
     * basicLength is the number of basic code points
     * destLength is the number of chars that have been output
     */

    /* Initialize the state: */
    n=INITIAL_N;
    delta=0;
    bias=INITIAL_BIAS;

    /* Main encoding loop: */
    for(handledCPCount=basicLength; handledCPCount<srcCPCount; /* no op */) 
    {
        /*
         * All non-basic code points < n have been handled already.
         * Find the next larger one:
         */
        for(m=0x7fffffff, j=0; j<srcCPCount; ++j) 
        {
            q=cpBuffer[j]&0x7fffffff; /* remove case flag from the sign bit */
            if(n<=q && q<m) 
            {
                m=q;
            }
        }

        /*
         * Increase delta enough to advance the decoder's
         * <n,i> state to <m,0>, but guard against overflow:
         */
        if(m-n>(0x7fffffff-MAX_CP_COUNT-delta)/(handledCPCount+1)) 
        {
            *pErrorCode=U_INTERNAL_PROGRAM_ERROR;
            return 0;
        }
        delta+=(m-n)*(handledCPCount+1);
        n=m;

        /* Encode a sequence of same code points n */
        for(j=0; j<srcCPCount; ++j) 
        {
            q=cpBuffer[j]&0x7fffffff; /* remove case flag from the sign bit */
            if(q<n) 
            {
                ++delta;
            } 
            else if(q==n) 
            {
                /* Represent delta as a generalized variable-length integer: */
                for(q=delta, k=BASE; /* no condition */; k+=BASE) 
                {

                    /** RAM: comment out the old code for conformance with draft-ietf-idn-punycode-03.txt   

                    t=k-bias;
                    if(t<TMIN) {
                        t=TMIN;
                    } else if(t>TMAX) {
                        t=TMAX;
                    }
                    */
                    
                    t=k-bias;
                    if(t<TMIN) 
                    {
                        t=TMIN;
                    } 
                    else if(k>=(bias+TMAX)) 
                    {
                        t=TMAX;
                    }

                    if(q<t) 
                    {
                        break;
                    }

                    if(destLength<destCapacity) 
                    {
                        dest[destLength++]=digitToBasic(t+(q-t)%(BASE-t), 0);
                    }
                    q=(q-t)/(BASE-t);
                }

                if(destLength<destCapacity) 
                {
                    dest[destLength++]=digitToBasic(q, (UBool)(cpBuffer[j]<0));
                }
                bias=adaptBias(delta, handledCPCount+1, (UBool)(handledCPCount==basicLength));
                delta=0;
                ++handledCPCount;
            }
        }

        ++delta;
        ++n;
    }

    return u_terminateUChars(dest, destCapacity, destLength, pErrorCode);
}




static char isLDHChar(UChar ch)
{
    // high runner case
    if(ch>0x007A)
    {
        return 0;
    }
    //[\\u002D \\u0030-\\u0039 \\u0041-\\u005A \\u0061-\\u007A]
    if( (ch==0x002D) || 
        (0x0030 <= ch && ch <= 0x0039) ||
        (0x0041 <= ch && ch <= 0x005A) ||
        (0x0061 <= ch && ch <= 0x007A)
      )
    {
        return 1;
    }
    
    return 0;
}



static UChar toASCIILower(UChar ch)
{
    if(CAPITAL_A <= ch && ch <= CAPITAL_Z)
    {
        return ch + LOWER_CASE_DELTA;
    }
    return ch;
}

static char startsWithPrefix(const UChar* src , int srcLength)
{
    int i,startsWithPrefix = 1;

    if(srcLength < ACE_PREFIX_LENGTH)
    {
        return 0;
    }

    for(i=0; i< ACE_PREFIX_LENGTH; i++)
    {
        if(toASCIILower(src[i]) != ACE_PREFIX[i])
        {
            startsWithPrefix = 0;
        }
    }
    return startsWithPrefix;
}


static int _internal_toASCII(const UChar* src, int srcLength, 
                  UChar* dest, int destCapacity,
                  int options,
                  //UStringPrepProfile* nameprep,
                  //UParseError* parseError,
                  UErrorCode* status)
{

    UChar b1Stack[MAX_LABEL_BUFFER_SIZE], b2Stack[MAX_LABEL_BUFFER_SIZE];
    //initialize pointers to stack buffers
    UChar  *b1 = b1Stack, *b2 = b2Stack;
    int b1Len=0, b2Len, 
            b1Capacity = MAX_LABEL_BUFFER_SIZE, 
            b2Capacity = MAX_LABEL_BUFFER_SIZE ,
            reqLength=0;

    int namePrepOptions = ((options & UIDNA_ALLOW_UNASSIGNED) != 0) ? USPREP_ALLOW_UNASSIGNED: 0;
    char* caseFlags = NULL;
    
    // the source contains all ascii codepoints
    char srcIsASCII  = 1;
    // assume the source contains all LDH codepoints
    char srcIsLDH = 1; 

    int j=0;

    //get the options
    char useSTD3ASCIIRules = (char)((options & UIDNA_USE_STD3_RULES) != 0);

    int failPos = -1;
    
    if(srcLength == -1)
    {
        srcLength = u_strlen(src);
    }
    
    // step 1 
    for( j=0;j<srcLength;j++)
    {
        if(src[j] > 0x7F)
        {
            srcIsASCII = 0;
        }
        b1[b1Len++] = src[j];
    }
    
    // step 2 is performed only if the source contains non ASCII
    if(srcIsASCII == 0)
    {
        
        // step 2    
        b1Len = usprep_prepare(src, srcLength, b1, b1Capacity, namePrepOptions, status);

        if(*status == U_BUFFER_OVERFLOW_ERROR)
        {
            // redo processing of string
            // we do not have enough room so grow the buffer
            b1 = (UChar*) malloc(b1Len * U_SIZEOF_UCHAR);
            if(b1==NULL)
            {
                *status = U_MEMORY_ALLOCATION_ERROR;
                goto CLEANUP;
            }

            *status = U_ZERO_ERROR; // reset error
            
            b1Len = usprep_prepare(src, srcLength, b1, b1Len, namePrepOptions, status);
        }
    }
    // error bail out
    if(U_FAILURE(*status))
    {
        goto CLEANUP;
    }
    if(b1Len == 0)
    {
        *status = U_IDNA_ZERO_LENGTH_LABEL_ERROR;
        goto CLEANUP;
    }

    // for step 3 & 4
    srcIsASCII = 1;
    for( j=0;j<b1Len;j++)
    {
        // check if output of usprep_prepare is all ASCII 
        if(b1[j] > 0x7F){
            srcIsASCII = 0;
        }else if(isLDHChar(b1[j])==0){  // if the char is in ASCII range verify that it is an LDH character
            srcIsLDH = 0;
            failPos = j;
        }
    }
    if(useSTD3ASCIIRules == 1)
    {
        // verify 3a and 3b
        // 3(a) Verify the absence of non-LDH ASCII code points; that is, the
        //  absence of 0..2C, 2E..2F, 3A..40, 5B..60, and 7B..7F.
        // 3(b) Verify the absence of leading and trailing hyphen-minus; that
        //  is, the absence of U+002D at the beginning and end of the
        //  sequence.
        if( srcIsLDH == 0 /* source at this point should not contain anyLDH characters */
            || b1[0] ==  HYPHEN || b1[b1Len-1] == HYPHEN)
        {
            *status = U_IDNA_STD3_ASCII_RULES_ERROR;

            /* populate the parseError struct */
            if(srcIsLDH==0)
            {
                // failPos is always set the index of failure
                //uprv_syntaxError(b1,failPos, b1Len,parseError);
            }
            else if(b1[0] == HYPHEN)
            {
                // fail position is 0 
                //uprv_syntaxError(b1,0,b1Len,parseError);
            }
            else
            {
                // the last index in the source is always length-1
                //uprv_syntaxError(b1, (b1Len>0) ? b1Len-1 : b1Len, b1Len,parseError);
            }

            goto CLEANUP;
        }
    }
    // Step 4: if the source is ASCII then proceed to step 8
    if(srcIsASCII)
    {
        if(b1Len <= destCapacity)
        {
            memmove(dest, b1, b1Len * U_SIZEOF_UCHAR);
            reqLength = b1Len;
        }
        else
        {
            reqLength = b1Len;
            goto CLEANUP;
        }
    }
    else
    {
        // step 5 : verify the sequence does not begin with ACE prefix
        if(!startsWithPrefix(b1,b1Len))
        {

            //step 6: encode the sequence with punycode

            // do not preserve the case flags for now!
            // TODO: Preserve the case while implementing the RFE
            // caseFlags = (UBool*) malloc(b1Len * sizeof(UBool));
            // uprv_memset(caseFlags,TRUE,b1Len);

            b2Len = u_strToPunycode(b1,b1Len,b2,b2Capacity,caseFlags, status);

            if(*status == U_BUFFER_OVERFLOW_ERROR)
            {
                // redo processing of string
                /* we do not have enough room so grow the buffer*/
                b2 = (UChar*) malloc(b2Len * U_SIZEOF_UCHAR); 
                if(b2 == NULL)
                {
                    *status = U_MEMORY_ALLOCATION_ERROR;
                    goto CLEANUP;
                }

                *status = U_ZERO_ERROR; // reset error
                
                b2Len = u_strToPunycode(b1,b1Len,b2,b2Len,caseFlags, status);
            }
            //error bail out
            if(U_FAILURE(*status))
            {
                goto CLEANUP;
            }
            // TODO : Reconsider while implementing the case preserve RFE
            // convert all codepoints to lower case ASCII
            // toASCIILower(b2,b2Len);
            reqLength = b2Len+ACE_PREFIX_LENGTH;

            if(reqLength > destCapacity)
            {
                *status = U_BUFFER_OVERFLOW_ERROR;
                goto CLEANUP;
            }
            //Step 7: prepend the ACE prefix
            memcpy(dest,ACE_PREFIX,ACE_PREFIX_LENGTH * U_SIZEOF_UCHAR);
            //Step 6: copy the contents in b2 into dest
            memcpy(dest+ACE_PREFIX_LENGTH, b2, b2Len * U_SIZEOF_UCHAR);
        }
        else
        {
            *status = U_IDNA_ACE_PREFIX_ERROR; 
            //position of failure is 0
            //uprv_syntaxError(b1,0,b1Len,parseError);
            goto CLEANUP;
        }
    }
    // step 8: verify the length of lable
    if(reqLength > MAX_LABEL_LENGTH)
    {
        *status = U_IDNA_LABEL_TOO_LONG_ERROR;
    }

CLEANUP:
    if(b1 != b1Stack)
    {
        free(b1);
    }
    if(b2 != b2Stack)
    {
        free(b2);
    }
    //free(caseFlags);
    
    return u_terminateUChars(dest, destCapacity, reqLength, status);
}




/**
 * Ascertain if the given code point is a label separator as 
 * defined by the IDNA RFC
 * 
 * @param ch The code point to be ascertained
 * @return true if the char is a label separator
 * @stable ICU 2.8
 */
static char isLabelSeparator(UChar ch)
{
    switch(ch)
    {
        case 0x002e:
        case 0x3002:
        case 0xFF0E:
        case 0xFF61:
            return 1;
        default:
            return 0;           
    }
}

// returns the length of the label excluding the separator
// if *limit == separator then the length returned does not include 
// the separtor.
static int getNextSeparator(UChar *src,int srcLength,UChar **limit, char *done)
{
    if(srcLength == -1)
    {
        int i;
        for(i=0 ; ;i++)
        {
            if(src[i] == 0)
            {
                *limit = src + i; // point to null
                *done = 1;
                return i;
            }
            if(isLabelSeparator(src[i]))
            {
                *limit = src + (i+1); // go past the delimiter
                return i;
            }
        }
    }
    else
    {
        int i;
        for(i=0;i<srcLength;i++)
        {
            if(isLabelSeparator(src[i]))
            {
                *limit = src + (i+1); // go past the delimiter
                return i;
            }
        }
        // we have not found the delimiter
        // if(i==srcLength)
        *limit = src+srcLength;
        *done = 1;

        return i;
    }
}



int uidna_IDNToASCII(  const UChar *src, int srcLength,
                   UChar* dest, int destCapacity,
                   int options,
                   //UParseError *parseError,
                   UErrorCode *status)
{

    int reqLength = 0;
    char done = 0;
	UChar *delimiter = 0;
	UChar *labelStart = 0;
	UChar *currentDest = 0;
	int remainingLen = 0;
	int remainingDestCapacity = 0;
	int labelLen = 0, labelReqLength = 0;

    if(status == NULL || U_FAILURE(*status))
    {
        return 0;
    }
    if((src==NULL) || (srcLength < -1) || (destCapacity<0) || (!dest && destCapacity > 0))
    {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    //UStringPrepProfile* nameprep = usprep_open(NULL, DATA_FILE_NAME, status);
    
    if(U_FAILURE(*status))
    {
        return 0;
    }

    //initialize pointers 
    delimiter = (UChar*)src;
    labelStart = (UChar*)src;
    currentDest = (UChar*) dest;
    remainingLen = srcLength;
    remainingDestCapacity = destCapacity;

    for(;;)
    {
        labelLen = getNextSeparator(labelStart,remainingLen, &delimiter,&done);
        labelReqLength = 0;
        if(!(labelLen==0 && done))
        {// make sure this is not a root label separator.
        
            labelReqLength = _internal_toASCII( labelStart, labelLen, 
                                                currentDest, remainingDestCapacity, 
                                                options, status);
    
            if(*status == U_BUFFER_OVERFLOW_ERROR)
            {
                *status = U_ZERO_ERROR; // reset error
                remainingDestCapacity = 0;
            }
        }

    
        if(U_FAILURE(*status))
        {
            break;
        }
        
        reqLength +=labelReqLength;
        // adjust the destination pointer
        if(labelReqLength < remainingDestCapacity)
        {
            currentDest = currentDest + labelReqLength;
            remainingDestCapacity -= labelReqLength;
        }
        else
        {
            // should never occur
            remainingDestCapacity = 0;
        }
        if(done == TRUE)
        {
            break;
        }

        // add the label separator
        if(remainingDestCapacity > 0)
        {
            *currentDest++ = FULL_STOP;
            remainingDestCapacity--;
        }
        reqLength++;           

        labelStart = delimiter;
        if(remainingLen >0 )
        {
            remainingLen = (int)(srcLength - (delimiter - src));
        }

    }
    //usprep_close(nameprep);
    return u_terminateUChars(dest, destCapacity, reqLength, status);
}





