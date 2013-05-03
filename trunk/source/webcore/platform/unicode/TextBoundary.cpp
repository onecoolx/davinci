
#include <string.h>
#include "TextBoundary.h"

typedef struct {
    unsigned int   startcode;
    unsigned int   endcode;
}CODEAREA;

typedef enum {
    DIRECT_BRK,
    INDIRECT_BRK,       
    COMBINING_INDIRECT_BRK,     
    COMBINING_PROHIBITED_BRK,   
    PROHIBITED_BRK,
    EXPLICIT_BRK,
    HANGUL_SPACE_BRK,
}BREAKACTION;


typedef struct {
    unsigned int   startcode;
    unsigned int   endcode;
    BREAKCLASS     LBKclass;
}LINEBREAKCLASS_DB;

#include  "char_break_data.cpp"
#include  "word_break_data.cpp"
#include  "line_break_data.cpp"


//find wether the UNICODE codepoint is in the CODEAREA struct array
//parameters:
//result: 1  exist  ;0   not exist
static int FindInCodeareaArray(const CODEAREA*  codeareap, int  arraylength, unsigned int codepoint)
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


//find wether the UNICODE codepoint is in the UCHAR array
//parameters:
//result: 1  exist  ;0   not exist
static int FindInNormalArray(const UChar* codeareap, int  arraylength, unsigned int codepoint)
{
    int min,max,tmp;
    
    min =0;
    max =arraylength -1;
    
    if(codepoint <codeareap[min] || codepoint >codeareap[max])
        return 0;
        
    while(1)
    {
        if(codepoint >codeareap[min])
        {
            if(max >min +1)
            {
                tmp =min +(max -min)/2;
                if(codepoint ==codeareap[tmp])
                {
                    return 1;
                }
                else if(codepoint >codeareap[tmp])
                {
                    min =tmp;
                }
                else
                {
                    max =tmp;
                }
            }
            else if(codepoint ==codeareap[min] || codepoint ==codeareap[max])
            {
                return 1;
            }
            else
            {
                break;
            }
        }
        else if(codepoint ==codeareap[min])
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



/**********************************************************************************************************************/
/************************************private APIs about grapheme cluster **********************************************/


//test if the codepoint is a control type grapheme cluster
static int Is_ControlType(unsigned int codepoint)
{
    if(FindInCodeareaArray(C_controlBoundary,CONTROLBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


//test if the codepoint is a extend type grapheme cluster
static int Is_ExtendType(unsigned int codepoint)
{
    if(FindInCodeareaArray(C_extendBoundary,EXTENDBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


//test if the codepoint is a LV type grapheme cluster
static int Is_LVType(unsigned int codepoint)
{
    if(FindInNormalArray(C_LVBoundary,LVBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}



//get the type of the specific codepoint
//parameter: codepoint  Uniocde code point.
static CHARS_TYPE  GetType_GraphemeCluster(unsigned int codepoint)
{
    if(codepoint >0x10FFFF)
        return c_ERROR_TYPE;
        
    if(codepoint ==C_CRBoundary[0])
    {
        return CR;
    }
    else if(codepoint ==C_LFBoundary[0])
    {
        return LF;
    }
    else if(codepoint >=C_VBoundary[0].startcode && codepoint <=C_VBoundary[0].endcode)
    {
        return V;
    }
    else if(codepoint >=C_TBoundary[0].startcode && codepoint <=C_TBoundary[0].endcode)
    {
        return T;
    }
    else if((codepoint >=C_LBoundary[0].startcode && codepoint <=C_LBoundary[0].endcode) ||
            (codepoint >=C_LBoundary[1].startcode && codepoint <=C_LBoundary[1].endcode))
    {
        return L;
    }
    else if(Is_ControlType(codepoint))
    {
        return CONTROL;
    }
    else if(Is_ExtendType(codepoint))
    {
        return EXTEND;
    }
    else if(Is_LVType(codepoint))
    {
        return LV;
    }
    else if(codepoint >=C_LVTBoundary[0].startcode && codepoint <=C_LVTBoundary[0].endcode)
    {
        return LVT;
    }

    return c_TYPE_ANY;
}


/*********************************************************************************************************************/
/**************************************public API  about grapheme cluster ********************************************/

static int utf16_len_first_char (const UChar* mstr, int len)
{
    if (mstr[0] < 0xD800 || mstr[0] > 0xDFFF)
        return 1;

    if (mstr[0] >= 0xD800 && mstr[0] <= 0xDBFF) 
    {
        if (len < 2)
            return 0;
        if (mstr[1] < 0xDC00 || mstr[1] > 0xDFFF)
            return 0;
    }

    return 2;
}


static unsigned int utf16_conv_to_uc32 (const UChar* mchar)
{
    unsigned int wc;

    wc = mchar[0];
    wc <<= 10;
    wc |= (mchar[1] & 0x03FF);
    wc += 0x10000;

    return wc;
}


int FirstCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index;
    CHARS_TYPE   ch_type;
    
    if (!text || !pCBKinfo)
        return -1;
        
    pCBKinfo->current =-1;
    pCBKinfo->char_type =c_ERROR_TYPE;
    index =0;
    while(index <textlength)
    {
        ch_len =utf16_len_first_char(mchar+index,textlength - index);
        
        wc =mchar[index];
        if(ch_len >1)
        {
            wc =utf16_conv_to_uc32(mchar+index);
        }
        
        ch_type =GetType_GraphemeCluster(wc);
        /*if(EXTEND ==ch_type)
        {
            index +=ch_len;
        }
        else
        {*/
            pCBKinfo->current =index;
            pCBKinfo->char_type =ch_type;
            return index;
        //}
    }
    
    return -1;
}


int NextCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index;
    CHARS_TYPE   ch_type;
    
    if(NULL ==text || NULL ==pCBKinfo)
        return -1;
        
    index =pCBKinfo->current;
    if(0 ==pCBKinfo->current && 0 ==pCBKinfo->char_type)
    {
        pCBKinfo->current =-1;
        pCBKinfo->char_type =c_ERROR_TYPE;

        return FirstCharsBreak(mchar,textlength,pCBKinfo);
    }
    
    while(index <textlength)
    {
        //to get the next grapheme cluster index
        ch_len =utf16_len_first_char(mchar+index,textlength - index);
        index += ch_len;
        if(index >=textlength)
        {
            return -1;   //there is no more grapheme cluster in the text
        }
        
        //get code value
        ch_len =utf16_len_first_char(mchar+index,textlength - index);
        
        wc =mchar[index];
        if(ch_len >1)
        {
            wc =utf16_conv_to_uc32(mchar+index);
        }
        
        //get Grapheme cluster type
        ch_type =GetType_GraphemeCluster(wc);
        
        //Do not break before extending characters
        if(EXTEND ==ch_type)
        {
            if(LF ==pCBKinfo->char_type || CR ==pCBKinfo->char_type || 
               (CONTROL ==pCBKinfo->char_type && 0x0001 ==mchar[index -1]))    //??????CONTROL???XTEND??????X0001????????????
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                return index;
            }
            
            pCBKinfo->current =index;
            pCBKinfo->char_type =ch_type;
            
            continue;
        }
        
        //if it is the beginning of the text then return the index of the first valid grapheme cluster
        if(c_ERROR_TYPE ==pCBKinfo->char_type)
        {
            pCBKinfo->current =index;
            pCBKinfo->char_type =ch_type;
            
            return index;
        }
        
        //just wether there is boundary
        switch(pCBKinfo->char_type)
        {
            case c_ERROR_TYPE:
                break;
            case  CR:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                if(LF !=ch_type)
                {
                    return index;
                }
            }
            break;
            case  LF:
            case  CONTROL:
            case  EXTEND:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                return index;
            }
            case  L:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                if(L !=ch_type && V !=ch_type && LV !=ch_type && LVT !=ch_type)
                {
                    return index;
                }
            }
            break;
            case  V:
            case  LV:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                if(V !=ch_type && T !=ch_type)
                {
                    return index;
                }
            }
            break;
            case  T:
            case  LVT:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                if(T !=ch_type)
                {
                    return index;
                }
            }
            break;
            case  c_TYPE_ANY:
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                return index;
            }
        }
    }
    
    return -1;
}


int PreviousCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int index;
    CHARS_TYPE   ch_type;
    
    if(NULL ==text || NULL ==pCBKinfo)
        return -1;
        
    index =pCBKinfo->current;
    if(0 ==pCBKinfo->current && 0 ==pCBKinfo->char_type)
    {
        pCBKinfo->current =-1;
        pCBKinfo->char_type =c_ERROR_TYPE;
    }
    
    if(0 ==index && c_ERROR_TYPE ==pCBKinfo->char_type)
    {
        memset(pCBKinfo,0,sizeof(CHARS_BREAK));
        return NextCharsBreak(text,textlength,pCBKinfo);
    }
    else if(0 ==index && c_ERROR_TYPE !=pCBKinfo->char_type)
    {
        return index;
    }
    else
    {
        while(index >0)
        {
            if(mchar[index -1] <0xD800 || mchar[index -1] >0xDFFF)
            {
                //get code value
               index -=1;
                wc =mchar[index];
                
                //get Grapheme cluster type
                ch_type =GetType_GraphemeCluster(wc);
                if(EXTEND ==ch_type)
                {
                    if(0 ==index)
                    {
                        return -1;   //there first boundary is the current ,the index:0 is not the first boundary
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =EXTEND;
                        
                        //Do not break before extending characters,so we continue
                        continue;
                    }
                }
                else
                {
                    pCBKinfo->current =index;
                    pCBKinfo->char_type =ch_type;
                    
                    return index;
                }
            }
            else if(index >1 && (mchar[index -1] >=0xDC00 && mchar[index -1] <=0xDFFF) && 
                    (mchar[index -2] >=0xD800 && mchar[index -2] <=0xDBFF))
            {
                //get code value
                index -=2;
                wc =utf16_conv_to_uc32(mchar+index);
                
                //get Grapheme cluster type
                ch_type =GetType_GraphemeCluster(wc);
                
                if(EXTEND ==ch_type)
                {
                    if(0 ==index)
                    {
                        return -1;   //there first boundary is the current ,the index:0 is not the first boundary
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =EXTEND;
                        
                        //Do not break before extending characters,so we continue
                        continue;
                    }
                }
                else
                {
                    pCBKinfo->current =index;
                    pCBKinfo->char_type =ch_type;
                    
                    return index;
                }
            }
            else
            {
                return -1;    //there is an error,the codepoint value is invalid
            }
        }
    }
    
    return -1;
}


static CHARS_TYPE getpreviousgraphemeclustertype(const UChar* text, int textlength, int* index)
{
    const UChar* mchar = text;
    unsigned int wc;
    
    if(*index <1 || NULL ==text)
        return c_ERROR_TYPE;
        
    (*index) -=1;
    if(mchar[*index] <0xD800 || mchar[*index] >0xDFFF)
    {
        wc =mchar[*index];
    }
    else if(mchar[*index] >=0xDC00 && mchar[*index] <=0xDFFF)
    {
        if(*index <1)
        {
            return c_ERROR_TYPE;
        }
        *index -=1;
        wc =utf16_conv_to_uc32(mchar+*index);
    }
    else
    {
        return c_ERROR_TYPE;
    }    
    
    return GetType_GraphemeCluster(wc);
}


int PrecedingCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo, int offset)
{
    const UChar* mchar = text;
    unsigned int wc;
    int index,seindex;
    CHARS_TYPE   ch_type,previous_type;
    
    if(NULL ==text || NULL ==pCBKinfo)
        return -1;
        
    index =offset -1;

    if(index <0)
        return -1;
    if(0 ==index)
        return 0;    //the beginning is a starter
    if(index >=textlength)
        index =textlength -1;
        
    if(0 ==pCBKinfo->current && 0 ==pCBKinfo->char_type)
    {
        pCBKinfo->current =-1;
        pCBKinfo->char_type =c_ERROR_TYPE;
    }
        
    while(index >=0)
    {
        if(mchar[index] <0xD800 || mchar[index] >0xDFFF)
        {
            wc =mchar[index];
        }
        else if(mchar[index] >=0xDC00 && mchar[index] <=0xDFFF)
        {
            if(index <1)
            {
                return -1;    //error
            }
            index -=1;
            wc =utf16_conv_to_uc32(mchar+index);
        }
        else if((index+1) <textlength && mchar[index] >=0xD800 && mchar[index] <=0xDBFF &&
                mchar[index+1] >=0xDC00 && mchar[index+1] <=0xDFFF)
        {
            wc =utf16_conv_to_uc32(mchar+index);
        }
        else
        {
            return -1;
        }
        
        //get Grapheme cluster type
        ch_type =GetType_GraphemeCluster(wc);
        
        if(EXTEND ==ch_type)
        {
            if(index <1)
                return -1;        //error
                
            if(0x000a ==mchar[index-1] || 0x000d ==mchar[index -1] || 0x0001 ==mchar[index -1])
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                return index;
            }
            index -=1;
            
            continue;
        }
        else
        {
            switch(ch_type)
            {
                case  c_ERROR_TYPE:
                case  EXTEND:
                    break;
                case  CR:
                case  CONTROL:
                case  c_TYPE_ANY:
                {
                    pCBKinfo->current =index;
                    pCBKinfo->char_type =ch_type;
                    
                    return index;
                }
                case  LF:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =LF;
                            return 0;
                        }
        
                        return -1;
                    }
                    else if(CR !=previous_type)
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                    else
                    {
                        pCBKinfo->current =seindex;
                        pCBKinfo->char_type =CR;

                        index =seindex -1;
                        if(index <0)
                            return 0;        //already reach the beginning of the text ,it is the start
                        continue;
                    }
                }
                break;
                case  L:
                case  LV:
                case  LVT:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;
                        }

                        return -1;
                    }
                    else if(L !=previous_type)
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                    else
                    {
                        pCBKinfo->current =seindex;
                        pCBKinfo->char_type =L;
                        
                        index =seindex -1;
                        if(index <0)        //the beginning is a starter
                            return 0;
                        continue;
                    }
                }
                break;
                case  V:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;
                        }

                        return -1;
                    }
                    else if(L ==previous_type || V ==previous_type || LV ==previous_type)
                    {
                        pCBKinfo->current =seindex;
                        pCBKinfo->char_type =previous_type;
                        
                        index =seindex -1;
                        if(index <0)        //the beginning is a starter
                            return 0;
                        continue;
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                }
                break;
                case  T:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;
                        }

                        return -1;
                    }
                    else if(T ==previous_type || V ==previous_type || LV ==previous_type || LVT ==previous_type)
                    {
                        pCBKinfo->current =seindex;
                        pCBKinfo->char_type =previous_type;

                        index =seindex -1;
                        if(index <0)        //the beginning is a starter
                            return 0;
                        continue;
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                }
            }
        }
    }
    
    return -1;
}


int FollowingCharsBreak(const UChar* text, int textlength, CHARS_BREAK* pCBKinfo, int offset)
{
    const UChar* mchar = text;
    unsigned int wc;
    int index,seindex,ch_len;
    CHARS_TYPE   ch_type, previous_type;
    
    if(NULL ==text || NULL ==pCBKinfo)
        return -1;
        
    index =offset <0?0:offset +1;
    if(index >=textlength)
        return -1;
        
    if(0 ==pCBKinfo->current && 0 ==pCBKinfo->char_type)
    {
        pCBKinfo->current =-1;
        pCBKinfo->char_type =c_ERROR_TYPE;
    }
    
    while(index <textlength)
    {
        if(mchar[index] <0xD800 || mchar[index] >0xDFFF)
        {
            wc =mchar[index];
            ch_len =1;
        }
        else if(mchar[index] >=0xDC00 && mchar[index] <=0xDFFF)
        {
            if(index +1<textlength)
            {
                index +=1;
                continue;
            }
            
            return -1;    //this is the end of text, here is no boundary after the offset
        }
        else if((index +1)<textlength && mchar[index] >=0xD800 && mchar[index] <=0xDBFF &&
                mchar[index+1] >=0xDC00 && mchar[index+1] <=0xDFFF)
        {
            wc =utf16_conv_to_uc32(mchar+index);
            ch_len =2;
        }
        else
        {
            return -1;     //error
        }
        
        //get Grapheme cluster type
        ch_type =GetType_GraphemeCluster(wc);
        
        if(EXTEND ==ch_type)
        {
            if(0x000a ==mchar[index -1] || 0x000d ==mchar[index -1] || 0x0001 ==mchar[index -1])
            {
                pCBKinfo->current =index;
                pCBKinfo->char_type =ch_type;
                
                return index;
            }
            if(index +ch_len>=textlength)
                return -1;        //
            index +=ch_len;
            
            continue;
        }
        else
        {
            switch(ch_type)
            {
                case c_ERROR_TYPE:
                case EXTEND:
                    break;
                case  CR:
                case  CONTROL:
                case  c_TYPE_ANY:
                {
                    pCBKinfo->current =index;
                    pCBKinfo->char_type =ch_type;
                    
                    return index;
                }
                case  LF:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =LF;
                            return 0;         
                        }
                        return -1;       //error
                    }
                    else if(CR !=previous_type)
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                    else
                    {
                        if(index +ch_len>=textlength)
                            return -1;        //there is no boundary after the offset
                        index +=ch_len;
                        
                        continue;
                    }
                }
                break;
                case  L:
                case  LV:
                case  LVT:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;         
                        }
                        return -1;       //error
                    }
                    else if(L !=previous_type)
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                    else
                    {
                        if(index +ch_len>=textlength)
                            return -1;        //there is no boundary after the offset
                        index +=ch_len;
                        
                        continue;
                    }
                }
                break;
                case  V:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;         
                        }
                        return -1;       //error
                    }
                    else if(L ==previous_type || V ==previous_type || LV ==previous_type)
                    {
                        if(index +ch_len>=textlength)
                            return -1;        //there is no boundary after the offset
                        index +=ch_len;
                        
                        continue;
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                }
                break;
                case  T:
                {
                    seindex =index;
                    previous_type =getpreviousgraphemeclustertype(mchar,textlength,&seindex);
                    if(c_ERROR_TYPE ==previous_type)
                    {
                        if(0 ==index)
                        {
                            pCBKinfo->current =index;
                            pCBKinfo->char_type =ch_type;
                            return 0;         
                        }
                        return -1;       //error
                    }
                    else if(T ==previous_type || V ==previous_type || LV ==previous_type || LVT ==previous_type)
                    {
                        if(index +ch_len>=textlength)
                            return -1;        //there is no boundary after the offset
                        index +=ch_len; 
                        continue;
                    }
                    else
                    {
                        pCBKinfo->current =index;
                        pCBKinfo->char_type =ch_type;

                        return index;
                    }
                }
            }
        }
    }
    
    return -1;
}



/*********************************************************************************************************************/
/**************************************private API  about word ********************************************************/

static int Is_FormatType(unsigned int codepoint)
{
    if(FindInCodeareaArray(W_FormatBoundary,FORMATBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_KatakanaType(unsigned int codepoint)
{
    if(FindInCodeareaArray(W_KatakanaBoundary,KATAKANABOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_AletterType(unsigned int codepoint)
{
    if(FindInCodeareaArray(W_ALetterBoundary,ALETTERBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_MidletterType(unsigned int codepoint)
{
    if(FindInNormalArray(W_MidLetterBoundary,MIDLETTERBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_MidnumType(unsigned int codepoint)
{
    if(FindInNormalArray(W_MidNumBoundary,MIDNUMBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_NumericType(unsigned int codepoint)
{
    if(FindInCodeareaArray(W_NumericBoundary,NUMERICBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}


static int Is_ExtendnumletType(unsigned int codepoint)
{
    if(FindInNormalArray(W_ExtendNumLetBoundary,EXTENDNUMLETBOUNDARY_NUM,codepoint))
    {
        return 1;
    }
    
    return 0;
}



//get the type of the specific codepoint, which used for word boundary
//parameter: codepoint  Uniocde code point.
static WORD_TYPE  GetType_word(unsigned int codepoint)
{
    if(codepoint >0x10FFFF)
        return w_ERROR_TYPE;
        
    if(Is_AletterType(codepoint))
    {
        return ALETTER;
    }
    else if(Is_MidletterType(codepoint))
    {
        return MIDLETTER;
    }
    else if(Is_NumericType(codepoint))
    {
        return NUMERIC;
    }
    else if(Is_ExtendnumletType(codepoint))
    {
        return EXTENDNUMLET;
    }
    else if(Is_MidnumType(codepoint))
    {
        return MIDNUM;
    }
    else if(Is_KatakanaType(codepoint))
    {
        return KATAKANA;
    }
    else if(Is_FormatType(codepoint))
    {
        return FORMAT;
    }
    
    return w_TYPE_ANY;
}


/*********************************************************************************************************************/
/**************************************public API  about word ********************************************************/

int FirstWordBreak(const UChar* text, int textlength, WORD_BREAK* pwordinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index;
    WORD_TYPE   ch_type;
    CHARS_BREAK   graphemecluster;
    
    if(NULL ==text || NULL ==pwordinfo)
        return -1;
        
    index =FirstCharsBreak(mchar,textlength,&graphemecluster);
    if(-1 ==index)
        return -1;  //error
    ch_len =utf16_len_first_char(mchar+index,textlength - index);
    
    wc =mchar[index];
    if(ch_len >1)
    {
        wc =utf16_conv_to_uc32(mchar+index);
    }
    
    ch_type =GetType_word(wc);
    
    pwordinfo->current =index;
    pwordinfo->word_type = ch_type;
    
    return index;
}


static WORD_TYPE  getnextchar_wordtype(const UChar* text, int textlength, int offset, int* index_back)
{
    const UChar* mchar = text;
    unsigned int wc;
    int sech_len,seindex;
    CHARS_BREAK   graphemecluster;
    
    seindex =FollowingCharsBreak(mchar,textlength,&graphemecluster,offset);
    if(-1 == seindex)
    {
        return w_ERROR_TYPE;
    }
    else
    {
        //get the char type behind the index
        sech_len =utf16_len_first_char(mchar+seindex,textlength - seindex);

        wc =mchar[seindex];
        if(sech_len >1)
        {
            wc =utf16_conv_to_uc32(mchar+seindex);
        }
        
        *index_back =seindex;
        return GetType_word(wc);
    }
    
    return w_ERROR_TYPE;
}


static WORD_TYPE  getpreviouschar_wordtype(const UChar* text, int textlength, int offset, int* index_back)
{
    const UChar* mchar = text;
    unsigned int wc;
    int sech_len,seindex;
    CHARS_BREAK   graphemecluster;
    
    seindex =PrecedingCharsBreak(mchar,textlength,&graphemecluster,offset);
    if(-1 == seindex)
    {
        return w_ERROR_TYPE;
    }
    else
    {
        //get the char type behind the index
        sech_len =utf16_len_first_char(mchar+seindex,textlength - seindex);

        wc =mchar[seindex];
        if(sech_len >1)
        {
            wc =utf16_conv_to_uc32(mchar+seindex);
        }

        *index_back =seindex;
        return GetType_word(wc);
    }
    
    return w_ERROR_TYPE;
}


int NextWordBreak(const UChar* text, int textlength, WORD_BREAK* pwordinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index,seindex,thindex;
    WORD_TYPE   ch_type,tmp_type;
    CHARS_BREAK   graphemecluster;
    
    if(NULL ==text || NULL ==pwordinfo)
        return -1;
        

    index =pwordinfo->current;

    if(index+1 ==textlength)
    {
        pwordinfo->current = textlength;
        return textlength;    //will reach the end of text so return the textlength
    }

    if(0 ==pwordinfo->current && 0 ==pwordinfo->word_type)
    {
        pwordinfo->current =-1;
        pwordinfo->word_type =w_ERROR_TYPE;
        
        return FirstWordBreak(mchar,textlength,pwordinfo);
    }
    else if(0 !=pwordinfo->current && (pwordinfo->word_type <FORMAT || pwordinfo->word_type >w_TYPE_ANY))
    {
        return -1;       //error
    }
    if(index <0)
    {
        return FirstWordBreak(mchar,textlength,pwordinfo);
    }

    if(index+1 > textlength)
        return -1;    //already reach the end of text
        
    while(index <textlength)
    {
        if((index+1) == textlength) 
        {
            pwordinfo->current =textlength;
            return textlength;
        }
        if(0x0085 ==mchar[index] && 0x0300 ==mchar[index +1])
        {
            pwordinfo->current =index +1;
            pwordinfo->word_type =w_TYPE_ANY;
            
            return index +1;
        }
        memset(&graphemecluster,0,sizeof(CHARS_BREAK));
        index =FollowingCharsBreak(mchar,textlength,&graphemecluster,index);
        if(-1 ==index)
        {
            return -1;        //error
        }
            
        ch_len =utf16_len_first_char(mchar+index,textlength - index);
    
        wc =mchar[index];
        if(ch_len >1)
        {
            wc =utf16_conv_to_uc32(mchar+index);
        }
        
        ch_type =GetType_word(wc);
        
        if(FORMAT ==ch_type)
        {
            if(0x000a ==mchar[index  -1] || 0x000d ==mchar[index -1] || 0x0085 ==mchar[index -1])
            {
                pwordinfo->current =index;
                pwordinfo->word_type =ch_type;
                
                return index;
            }
            if(index +ch_len<textlength)
            {
                continue;
            }
            else
            {
                return -1;   //there is no more boundary
            }
        }
        else
        {
            switch(pwordinfo->word_type)
            {
                case w_ERROR_TYPE:
                {
                    return -1;
                }
                case FORMAT:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;

                    return index;
                }
                case  ALETTER:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;
                    
                    if(ALETTER ==ch_type || NUMERIC ==ch_type || EXTENDNUMLET ==ch_type)
                    {
                        continue;
                    }
                    else if(MIDLETTER ==ch_type)
                    {
                        tmp_type =getnextchar_wordtype(mchar,textlength,index,&seindex);
                        if(ALETTER ==tmp_type)
                        {
                            pwordinfo->current =seindex;
                            pwordinfo->word_type =ALETTER;
                            index =seindex;
                            
                            continue;
                        }
                        else if(FORMAT ==tmp_type)
                        {
                            thindex =seindex;
                            if(ALETTER ==getnextchar_wordtype(mchar,textlength,thindex,&seindex))
                            {
                                pwordinfo->current =seindex;
                                pwordinfo->word_type =ALETTER;
                                index =seindex;
                                
                                continue;
                            }
                            else
                            {
                                return index;
                            }
                        }
                        else
                        {
                            return index;
                        }
                    }
                    else
                    {
                        return index;
                    }
                }
                break;
                case  NUMERIC:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;
                    
                    if(NUMERIC ==ch_type || ALETTER ==ch_type || EXTENDNUMLET ==ch_type)
                    {
                        continue;
                    }
                    else if(MIDNUM ==ch_type)
                    {
                        tmp_type =getnextchar_wordtype(mchar,textlength,index,&seindex);
                        if(NUMERIC ==tmp_type)
                        {
                            pwordinfo->current =seindex;
                            pwordinfo->word_type =NUMERIC;
                            index =seindex;
                            
                            continue;
                        }
                        else if(FORMAT ==tmp_type)
                        {
                            thindex =seindex;
                            if(NUMERIC ==getnextchar_wordtype(mchar,textlength,thindex,&seindex))
                            {
                                pwordinfo->current =seindex;
                                pwordinfo->word_type =NUMERIC;
                                index =seindex;
                                
                                continue;
                            }
                            else
                            {
                                return index;
                            }
                        }
                        else
                        {
                            return index;
                        }
                    }
                    else
                    {
                        return index;
                    }
                }
                break;
                case  MIDLETTER:
                {
                    if(ALETTER ==ch_type)
                    {
                        tmp_type =getpreviouschar_wordtype(mchar,textlength,pwordinfo->current,&seindex);
                        if(ALETTER ==tmp_type)
                        {
                            pwordinfo->current =index;
                            pwordinfo->word_type =ch_type;

                            continue;
                        }
                        else if(FORMAT ==tmp_type)
                        {
                            thindex =seindex;
                            if(ALETTER ==getpreviouschar_wordtype(mchar,textlength,thindex,&seindex))
                            {
                                pwordinfo->current =index;
                                pwordinfo->word_type =ch_type;
    
                                continue;
                            }
                            else
                            {
                                pwordinfo->current =index;
                                pwordinfo->word_type =ch_type;
    
                                return index;
                            }
                        }
                        else
                        {
                            pwordinfo->current =index;
                            pwordinfo->word_type =ch_type;

                            return index;
                        }
                    }
                    else
                    {
                        pwordinfo->current =index;
                        pwordinfo->word_type =ch_type;

                        return index;
                    }
                }
                break;
                case  MIDNUM:
                { 
                    if(NUMERIC ==ch_type)
                    {
                        tmp_type =getpreviouschar_wordtype(mchar,textlength,pwordinfo->current,&seindex);
                        if(NUMERIC ==tmp_type)
                        {
                            pwordinfo->current =index;
                            pwordinfo->word_type =ch_type;

                            continue;
                        }
                        else if(FORMAT ==tmp_type)
                        {
                            thindex =seindex;
                            if(NUMERIC ==getpreviouschar_wordtype(mchar,textlength,thindex,&seindex))
                            {
                                pwordinfo->current =index;
                                pwordinfo->word_type =ch_type;
    
                                continue;
                            }
                            else
                            {
                                pwordinfo->current =index;
                                pwordinfo->word_type =ch_type;
    
                                return index;
                            }
                        }
                        else
                        {
                            pwordinfo->current =index;
                            pwordinfo->word_type =ch_type;

                            return index;
                        }
                    }
                    else
                    {
                        pwordinfo->current =index;
                        pwordinfo->word_type =ch_type;

                        return index;
                    }
                }
                break;
                case  KATAKANA:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;
                    
                    if(KATAKANA ==ch_type || EXTENDNUMLET ==ch_type)
                    {
                        continue;
                    }
                    else
                    {
                        return index;
                    }
                }
                break;
                case  EXTENDNUMLET:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;
                    
                    if(KATAKANA ==ch_type || EXTENDNUMLET ==ch_type || ALETTER ==ch_type || NUMERIC ==ch_type)
                    {
                        continue;
                    }
                    else
                    {
                        return index;
                    }
                }
                break;
                case  w_TYPE_ANY:
                {
                    pwordinfo->current =index;
                    pwordinfo->word_type =ch_type;
                    
                    return index;
                }
            }
        }
    }
    return -1;    
}


#define   MAX_CCH     1

// Define some short-cuts for the table
#define oo DIRECT_BRK               // '_' break allowed
#define SS INDIRECT_BRK             // '%' only break across space (aka 'indirect break' below)
#define cc COMBINING_INDIRECT_BRK   // '#' indirect break for combining marks
#define CC COMBINING_PROHIBITED_BRK // '@' indirect break for combining marks
#define XX PROHIBITED_BRK           // '^' no break allowed_BRK
#define xS HANGUL_SPACE_BRK         // break allowed, except when spaces are used with Hangul (not used)

// Line Break Pair Table corresponding to Table 2 of UAX#14, Version 5.0.0 
// plus Korean Syllable Block extensions - for details see that document

static BREAKACTION brkPairs[][JT+1]=
{   //                ---     'after'  class  ------
    //      1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21   22  23  24  25  26  
    //     OP, CL, QU, GL, NS, EX, SY, IS, PR, PO, NU, AL, ID, IN, HY, BA, BB, B2, ZW, CM, WJ,  H2, H3, JL, JV, JT, = after class
    /*OP*/ {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, CC, XX,  XX, XX, XX, XX, XX}, // OP open
    /*CL*/ {oo, XX, SS, SS, XX, XX, XX, XX, SS, SS, SS, SS, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // CL close
    /*QU*/ {XX, XX, SS, SS, SS, XX, XX, XX, SS, SS, SS, SS, SS, SS, SS, SS, SS, SS, XX, cc, XX,  SS, SS, SS, SS, SS}, // QU quotation
    /*GL*/ {SS, XX, SS, SS, SS, XX, XX, XX, SS, SS, SS, SS, SS, SS, SS, SS, SS, SS, XX, cc, XX,  SS, SS, SS, SS, SS}, // GL glue
    /*NS*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, oo, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // NS no-start
    /*EX*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, oo, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // EX exclamation/interrogation
    /*SY*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // SY Syntax (slash)
    /*IS*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, SS, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // IS infix (numeric) separator
    /*PR*/ {SS, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, SS, SS, oo, SS, SS, oo, oo, XX, cc, XX,  SS, SS, SS, SS, SS}, // PR prefix
    /*PO*/ {SS, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, SS, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // NU numeric
    /*NU*/ {SS, XX, SS, SS, SS, XX, XX, XX, SS, SS, SS, SS, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // AL alphabetic
    /*AL*/ {SS, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, SS, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // AL alphabetic
    /*ID*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // ID ideograph (atomic)
    /*IN*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // IN inseparable
#ifdef v500
// Version 5.0.0
    /*HY*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // HY hyphens and spaces
    /*BA*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, oo, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // BA break after 
#else
// Version 5.0.1
    /*HY*/ {oo, XX, SS, oo, SS, XX, XX, XX, oo, oo, SS, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // HY hyphens and spaces
    /*BA*/ {oo, XX, SS, oo, SS, XX, XX, XX, oo, oo, oo, oo, oo, oo, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // BA break after 
#endif
    /*BB*/ {SS, XX, SS, SS, SS, XX, XX, XX, SS, SS, SS, SS, SS, SS, SS, SS, SS, SS, XX, cc, XX,  SS, SS, SS, SS, SS}, // BB break before 
    /*B2*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, oo, oo, oo, oo, SS, SS, oo, XX, XX, cc, XX,  oo, oo, oo, oo, oo}, // B2 break either side, but not pair
    /*ZW*/ {oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, oo, XX, oo, oo,  oo, oo, oo, oo, oo}, // ZW zero width space
    /*CM*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, oo, SS, SS, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, oo}, // CM combining mark
    /*WJ*/ {SS, XX, SS, SS, SS, XX, XX, XX, SS, SS, SS, SS, SS, SS, SS, SS, SS, SS, XX, cc, XX,  SS, SS, SS, SS, SS}, // WJ word joiner
                                                                                                
    /*H2*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, SS, SS}, // Hangul 2 Jamo syllable
    /*H3*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, SS}, // Hangul 3 Jamo syllable
    /*JL*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  SS, SS, SS, SS, oo}, // Jamo Leading Consonant
    /*JV*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, SS, SS}, // Jamo Vowel
    /*JT*/ {oo, XX, SS, SS, SS, XX, XX, XX, oo, SS, oo, oo, oo, SS, SS, SS, oo, oo, XX, cc, XX,  oo, oo, oo, oo, SS}, // Jamo Trailing Consonant
    
};


/*
find the line break property of the UNICODE point specified by parameter codepoint in the area between the 
startpos parameter end endpos parameter.
*/
static BREAKCLASS FindinDB(int startpos, int endpos, unsigned int codepoint)
{
    int min,max,tmp;
    
    if(startpos ==endpos)
    {
        if(codepoint >=class_data[startpos].startcode && 
           codepoint <=class_data[startpos].endcode)
        {
            return class_data[startpos].LBKclass;
        }
        else
        {
            return FXX;
        }
    }
    
    min =startpos;
    max =endpos;
    if(codepoint <class_data[min].startcode || codepoint >class_data[max].endcode)
        return FXX;
        
    while(1)
    {
        if(codepoint >class_data[min].endcode)
        {
            if(max >min +1)
            {
                tmp =min + (max -min)/2;
                if(codepoint <class_data[tmp].startcode)
                {
                    max =tmp;
                }
                else if(codepoint >class_data[tmp].endcode)
                {
                    min =tmp;
                }
                else
                {
                    if(codepoint >=class_data[tmp].startcode && codepoint <=class_data[tmp].endcode)
                    {
                        return class_data[tmp].LBKclass;
                    }
                    else
                    {
                        return FXX;
                    }
                }
            }
            else
            {
                if(codepoint >=class_data[max].startcode && codepoint <=class_data[max].endcode)
                {
                    return class_data[max].LBKclass;
                }
                else
                {
                    return FXX;
                }
            }
        }
        else if(codepoint >=class_data[min].startcode)
        {
            return class_data[min].LBKclass;
        }
        else
        {
            return FXX;
        }
    }
}


/*
return the line break property of the UNICODE code specified by codepoint.
this function can find four languages's UNICODE code's line break property.the four language is:chinese, english, korean,
japanese.For default we look up chinese first ,if in all chinese language Unicode code return XX, than the function will 
to look up in the four languages area, namely , the all database.
*/
static  BREAKCLASS  classifyofCodePoint(unsigned int codepoint)
{
    BREAKCLASS  bkClass;
    
    bkClass =FindinDB(CHINESE_START1,CHINESE_END1,codepoint);    //first look up chinese area
    
    if(XX ==bkClass)
    {
        bkClass =FindinDB(CHINESE_START2,CHINESE_END2,codepoint);    //second look up high chinese area
        if(XX ==bkClass)
        {
            bkClass =FindinDB(0,BREAKDATA_NUM,codepoint);      //look up all the database
        }
    }
    
    return bkClass;
}


// placeholder function for complex break analysis
// cls - last resolved line break class (this is !SA)
// pcls - pointer to array of line breaking classes with pcls[0] == SA (input)
// pbrk - pointer to array of line breaking opportunities (output)
//
static int findComplexBreak(BREAKCLASS cls, BREAKCLASS *pcls, BREAKACTION *pbrk, int cch)
{
    int ich;
    
    if (!cch)
        return 0;

    for (ich = 1; ich < cch; ich++) {

        // .. do complex break analysis here
        // and report any break opportunities in pbrk ..

        pbrk[ich-1] = PROHIBITED_BRK; // by default: no break

        if (pcls[ich] != SA)
                break;
    }
    return ich;
}

// handle spaces separately, all others by table
// pcls - pointer to array of line breaking classes (input)
// pbrk - pointer to array of line break opportunities (output)
// cch - number of elements in the arrays (count of characters) (input)
// ich - current index into the arrays (variable) (returned value)
// cls - current resolved line break class for 'before' character (variable)
// fLEGACY_CM  - whether Keep SP CM together, true: keep them together, false  no
static int findLineBrk(BREAKCLASS *pcls, BREAKACTION *pbrk, int cch, int fLEGACY_CM)
{
    int ich;
    BREAKACTION brk;
    BREAKCLASS cls;
    
    if (cch <= 0) 
        return 0;

    cls = pcls[0];

    // handle case where input starts with an L_LF
    if (cls == L_LF)
        cls = BK;

    // treat NL like BK
    if (cls == NL)
         cls = BK;

    // treat SP at start of input as if it followed WJ
    if (cls == SP)
         cls = WJ;

    // loop over all pairs in the string up to a hard break or CRLF pair
    for (ich = 1; (ich < cch) && (cls != BK) && (cls != L_CR || pcls[ich] == L_LF); ich++) {

        // handle spaces explicitly
        if (pcls[ich] == SP) {
            pbrk[ich-1] = PROHIBITED_BRK;   // apply rule LB 7: ?SP
            continue;                       // do not update cls
        }

        if (pcls[ich] == BK || pcls[ich] == NL || pcls[ich] == L_LF) {
            pbrk[ich-1] = PROHIBITED_BRK;
            cls = BK;
            continue;
        }

        if (pcls[ich] == L_CR) {
            pbrk[ich-1] = PROHIBITED_BRK;
            cls = L_CR;
            continue;
        }

        // handle complex scripts in a separate function
        if (cls == SA || pcls[ich] == SA) {
            ich += findComplexBreak(cls, &pcls[ich-1], &pbrk[ich-1], cch - (ich-1));
            if (ich < cch)
                cls = pcls[ich];
            continue;
        }

        // lookup pair table information in brkPairs[before, after];
        brk = brkPairs[cls][pcls[ich]];

        pbrk[ich-1] = brk;                              // save break action in output array

        if (brk == INDIRECT_BRK) {                      // resolve indirect break
            if (pcls[ich - 1] == SP)                    // if context is A SP * B
                pbrk[ich-1] = INDIRECT_BRK;             //       break opportunity
            else                                        // else
                pbrk[ich-1] = PROHIBITED_BRK;           //       no break opportunity
        } 
        else if (brk == COMBINING_PROHIBITED_BRK) {   // this is the case OP SP* CM
            pbrk[ich-1] = COMBINING_PROHIBITED_BRK;     // no break allowed
            if (pcls[ich-1] != SP)
                continue;                               // apply rule 9: X CM* -> X
        } 
        else if (brk == COMBINING_INDIRECT_BRK) {     // resolve combining mark break
            pbrk[ich-1] = PROHIBITED_BRK;               // don't break before CM
            if (pcls[ich-1] == SP) {
                if (!fLEGACY_CM)                        // new: SP is not a base
                    pbrk[ich-1] = COMBINING_INDIRECT_BRK;    // apply rule SP ?
                else {
                    pbrk[ich-1] = PROHIBITED_BRK;       // legacy: keep SP CM together
                    if (ich > 1)
                        pbrk[ich-2] = ((pcls[ich - 2] == SP) ? INDIRECT_BRK : DIRECT_BRK);
                }
            }
            else                                      // apply rule 9: X CM * -> X
                continue;                               // don't update cls
        }
        cls = pcls[ich];                                // save cls of current character
    }
    // always break at the end
    pbrk[ich-1] = EXPLICIT_BRK;
    return ich;
}

/*********************************************************************************************************/
/*******************************************below: public function***************************************/
/*
To find the first line break of the text,this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   LINE_BREAK* pLBKinfo:   return the property of the line break
   
BE CAREFUL:  should break before the position returned by this function
             return -1 for error
*/
int FirstLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index,len,i,breakpos,processed,j;
    LINE_BREAK   lbclsmg[MAX_CCH];
    BREAKACTION   lbrks[MAX_CCH];
    BREAKCLASS    lbcls[MAX_CCH];

    if (NULL ==text || NULL ==pLBKinfo)
        return -1;

    processed = 0;
    while (1) {
        memset(lbclsmg,0,sizeof(LINE_BREAK)*MAX_CCH);
        memset(lbcls,0,sizeof(BREAKCLASS)*MAX_CCH);
        memset(lbrks,0,sizeof(BREAKACTION)*MAX_CCH);

        len = MAX_CCH > (textlength -processed)?(textlength -processed):MAX_CCH;
        for (i=0,index=processed; i<len && index<textlength; i++) {
            ch_len = utf16_len_first_char(mchar+index,textlength - index);
            wc = mchar[index];
            if (ch_len >1) {
                /* if the character is expressed by surrogate, we combine the two surrogate
                 * into original UNICODE codepoint. before getting the character's line break
                 * property.This is different from the UAX #14,which get the line break property
                 * of the two surrogates respectively.The reason we get the UNICODE codepoint's line
                 * break property other than the surrogate's line break property is some chinese is
                 * expressed by surrogate, and chinese can make line break between randomly two of it.
                 * If according to the UAX #14,you will find there is no line break between two chinese.
                 * So, i change it,although it may be wrong.
                 */
                wc = utf16_conv_to_uc32(mchar+index);
            }
            lbclsmg[i].mlbkClass = classifyofCodePoint(wc);
            lbclsmg[i].pos = index;
            lbclsmg[i].length = ch_len;
            index += ch_len;
        }

        for(j=0;j<MAX_CCH;j++)
            lbcls[j] = lbclsmg[j].mlbkClass;

        //get line breaks of four characters
        breakpos = findLineBrk(lbcls, lbrks, i, 0);
        for (i =0;i<breakpos;i++) {
            if (lbrks[i] !=COMBINING_PROHIBITED_BRK && lbrks[i] !=PROHIBITED_BRK && lbclsmg[i].pos >0) {
                pLBKinfo->mlbkClass =lbclsmg[i].mlbkClass;
                pLBKinfo->pos =lbclsmg[i].pos;
                pLBKinfo->length =lbclsmg[i].length;
                return (lbclsmg[i].pos+lbclsmg[i].length); //be careful: should break before the position returned by this function
            }
        }

        processed = lbclsmg[1].pos;
        if (processed +lbclsmg[1].length >=textlength)
            break;
    }
    return textlength;
}

/*
To find the next line break of the text,this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   LINE_BREAK* pLBKinfo:   send in the current line break property and return the next property of the line break
   
BE CAREFUL:  should break before the position returned by this function
             return -1 for error
*/
int NextLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index,len,i,breakpos,processed,j;
    LINE_BREAK   lbclsmg[MAX_CCH];
    BREAKACTION   lbrks[MAX_CCH];
    BREAKCLASS    lbcls[MAX_CCH];

    if(NULL ==text || NULL ==pLBKinfo)
        return -1;

   // processed =pLBKinfo->pos +pLBKinfo->length;
    processed = pLBKinfo->pos ;
    while(1) {
        memset(lbclsmg,0,sizeof(LINE_BREAK)*MAX_CCH);
        memset(lbcls,0,sizeof(BREAKCLASS)*MAX_CCH);
        memset(lbrks,0,sizeof(BREAKACTION)*MAX_CCH);
        len =MAX_CCH >(textlength -processed)?(textlength -processed):MAX_CCH;
        for(i=0,index = processed;i <len && index < textlength;i++) {
            ch_len = utf16_len_first_char(mchar+index,textlength - index);
            wc = mchar[index];
            if(ch_len >1) {
                //if the character is expressed by surrogate, we combine the two surrogate into original UNICODE codepoint
                // before getting the character's line break property.This is different from the UAX #14,which get the line
                //break property of the two surrogates respectively.The reason we get the UNICODE codepoint's line break 
                //property other than the surrogate's line break property is some chinese is expressed by surrogate, and 
                //chinese can make line break between randomly two of it.If according to the UAX #14,you will find there is 
                //no line break between two chinese.So, i change it,although it may be wrong.
                wc = utf16_conv_to_uc32(mchar+index);
            }
            lbclsmg[i].mlbkClass = classifyofCodePoint(wc);
            lbclsmg[i].pos = index;
            lbclsmg[i].length = ch_len;
            index += ch_len;
        }

        for(j=0;j<MAX_CCH;j++)
            lbcls[j] = lbclsmg[j].mlbkClass;

        //get line breaks of four characters
        breakpos = findLineBrk(lbcls, lbrks, i, 0);
        for(i =0;i<breakpos;i++) {
            if(lbrks[i] !=COMBINING_PROHIBITED_BRK && lbrks[i] !=PROHIBITED_BRK) {
                pLBKinfo->mlbkClass =lbclsmg[i].mlbkClass;
                pLBKinfo->pos =lbclsmg[i].pos;
                pLBKinfo->length =lbclsmg[i].length;
                return (lbclsmg[i].pos+lbclsmg[i].length);    //be careful: should break before the position returned by this function
            }
        }
        
        processed = lbclsmg[1].pos;
        if(processed +lbclsmg[1].length >=textlength)
            break;
    }

    return textlength;
}


static int previousPosition(const UChar* mchar, int startpos)
{
    int previouspos = 0;
    if(startpos <= 0) {
        previouspos =0;
    }
    else {
        if(startpos >1 && 
           (mchar[startpos-1] >=0xDC00 && mchar[startpos-1] <=0xDFFF && 
            mchar[startpos-2] >=0xD800 && mchar[startpos-2] <=0xDBFF)) {
            previouspos =startpos -2;
        }
        else {
            previouspos =startpos -1;
        }
    }

    return previouspos;
}


/*
To find the previous line break of the text,this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   LINE_BREAK* pLBKinfo:   send in the current line break property and return the previous property of the line break
   
BE CAREFUL:  should break before the position returned by this function
             return -1 for error or no previous line break
*/
int PreviousLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo)
{
    const UChar* mchar = text;
    unsigned int wc;
    int ch_len,index,len,i,breakpos,processed,j;
    LINE_BREAK   lbclsmg[MAX_CCH];
    BREAKACTION   lbrks[MAX_CCH];
    BREAKCLASS    lbcls[MAX_CCH];

    if(NULL ==text || NULL ==pLBKinfo)
        return -1;

    processed = previousPosition(mchar, pLBKinfo->pos);
    while(1) {
        memset(lbclsmg,0,sizeof(LINE_BREAK)*MAX_CCH);
        memset(lbcls,0,sizeof(BREAKCLASS)*MAX_CCH);
        memset(lbrks,0,sizeof(BREAKACTION)*MAX_CCH);
        len =MAX_CCH >(textlength -processed)?(textlength -processed):MAX_CCH;
        for(i=0,index =processed;i <len && index <textlength;i++) {
            ch_len = utf16_len_first_char(mchar+index,textlength - index);
            wc = mchar[index];
            if(ch_len >1) {
                /* if the character is expressed by surrogate, we combine the two surrogate into
                 * original UNICODE codepoint before getting the character's line break property.
                 * This is different from the UAX #14,which get the line break property of the two
                 * surrogates respectively.The reason we get the UNICODE codepoint's line break 
                 * property other than the surrogate's line break property is some chinese is expressed
                 * by surrogate, and chinese can make line break between randomly two of it.If according
                 * to the UAX #14,you will find there is no line break between two chinese. So, i change
                 * it,although it may be wrong.
                 */
                wc = utf16_conv_to_uc32(mchar+index);
            }
            lbclsmg[i].mlbkClass = classifyofCodePoint(wc);
            lbclsmg[i].pos = index;
            lbclsmg[i].length = ch_len;
            index += ch_len;
        }

        for(j=0;j<MAX_CCH;j++)
            lbcls[j] =lbclsmg[j].mlbkClass;

        //get line breaks of four characters
        breakpos = findLineBrk(lbcls,lbrks,i,0);

        if (lbrks[0] !=COMBINING_PROHIBITED_BRK && lbrks[0] !=PROHIBITED_BRK) {
            pLBKinfo->mlbkClass =lbclsmg[0].mlbkClass;
            pLBKinfo->pos =lbclsmg[0].pos;
            pLBKinfo->length =lbclsmg[0].length;
            return (lbclsmg[0].pos+lbclsmg[0].length);    //be careful: should break before the position returned by this function
        }

        processed = previousPosition(mchar, lbclsmg[0].pos);
        if (processed <=0)
            break;
    }
    return -1;
}


/*
To find the preceding line break of the text before the position specified by parameter Precedingpos ,
this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   LINE_BREAK* pLBKinfo:   send in the current line break property and return the preceding property of the line break
   int  Precedingpos:   the position the user want to look  a line break before it
   
BE CAREFUL:  should break before the position returned by this function
             return -1 for error or no preceding line break
*/
int PrecedingLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo, int Precedingpos)
{
    int adjustedpos;

    if (NULL ==text || NULL ==pLBKinfo)
        return -1;

    if (Precedingpos <=0) {
        return -1;
    }
    else {
        if (Precedingpos >1 && text[Precedingpos -1] >=0xDC00 && text[Precedingpos -1] <=0xDFFF)
            adjustedpos = Precedingpos -2;
        else
            adjustedpos = Precedingpos -1;
    }

    if (adjustedpos <=0)
        return -1;

    pLBKinfo->pos =adjustedpos;
    return PreviousLineBreak(text, textlength,pLBKinfo);
}



/*
To find the Following line break of the text before the position specified by parameter Followingpos ,
this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   LINE_BREAK* pLBKinfo:   send in the current line break property and return the Following property of the line break
   int  Followingpos:    the position the user want to look  a line break Following it
   
BE CAREFUL:  should break before the position returned by this function
             return -1 for error 
*/
int FollowingLineBreak(const UChar* text, int textlength, LINE_BREAK* pLBKinfo, int Followingpos)
{
    int adjustedpos,len;
    
    if(NULL ==text || NULL ==pLBKinfo)
        return -1;
        
    if(Followingpos+1 >=textlength) {
        return textlength;
    }
    else {
        /*
        if(text[Followingpos +1] >=0xD800 && text[Followingpos +1] <=0xDBFF) {
            printf("adjustedpos =Followingpos +2;[%d]\n",Followingpos);
            adjustedpos =Followingpos +2;
        }
        else {
            printf("adjustedpos =Followingpos +1;[%d]\n",Followingpos);
            adjustedpos =Followingpos +1;
        }
        */
        adjustedpos =Followingpos ;
    }
    
    if (adjustedpos +1 >=textlength)
        return textlength;
    
    if (text[adjustedpos] >=0xD800 && text[adjustedpos] >=0xDBFF)
        len =2;
    else
        len =1;

    pLBKinfo->pos =adjustedpos;
    pLBKinfo->length =len;
    return NextLineBreak(text,textlength,pLBKinfo);
}


/*
To determine whether can make a line break at the pos of the text ,
this function is default for chinese, not for korean and japanese.
if the text is korean or japanese ,the result may be an error result.
parameters:
   UChar* text :  the text bo be resolved
   int textlength:    text length ,the number of unit UChar
   int  pos:    the character index the user want to look  a line break Following it
   
BE CAREFUL:  By default, this function is to judge whether can make line break between character[pos -1] and character[pos]
             return -1 for error 
*/
int IsLineBreak(const UChar* text, int textlength,int pos)
{
    LINE_BREAK   LBKinfo;
    int index =-1;
    
    if (NULL ==text)
        return -1;
        
    if (0 ==pos || (text[pos] >=0xDC00 && text[pos] <=0xDFFF))
        return 0;
        
    index = FirstLineBreak(text +pos-1,textlength -pos+1,&LBKinfo);
    if(index != 1)
        return 0;

    return 1;
}




