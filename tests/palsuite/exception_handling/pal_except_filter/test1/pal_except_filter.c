/*=====================================================================
**
** Source:  pal_except_filter.c (test 1)
**
** Purpose: Tests the PAL implementation of the PAL_EXCEPT_FILTER. An 
**          exception is forced and a known value is passed to the filter
**          fuction. The known value as well as booleans are tested to
**          ensure proper functioning.
**
** 
**  Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
** 
**  The use and distribution terms for this software are contained in the file
**  named license.txt, which can be found in the root of this distribution.
**  By using this software in any fashion, you are agreeing to be bound by the
**  terms of this license.
** 
**  You must not remove this notice, or any other, from this software.
** 
**
**===================================================================*/



#include <palsuite.h>

BOOL bFilter = FALSE;
BOOL bTry = FALSE;
const int nValidator = 12321;

LONG ExitFilter(EXCEPTION_POINTERS* ep, LPVOID pnTestInt)
{
    int nTestInt = *(int *)pnTestInt;
    
    /* let the main know we've hit the filter function */
    bFilter = TRUE;

    if (!bTry)
    {
        Fail("PAL_EXCEPT_FILTER: ERROR -> Something weird is going on."
            " The filter was hit without PAL_TRY being hit.\n");
    }

    /* was the correct value passed? */
    if (nValidator != nTestInt)
    {
        Fail("PAL_EXCEPT_FILTER: ERROR -> Parameter passed to filter function"
            " should have been \"%d\" but was \"%d\".\n",
            nValidator,
            nTestInt);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}


int __cdecl main(int argc, char *argv[])
{
    int* p = 0x00000000;   /* pointer to NULL */
    BOOL bExcept = FALSE;

    if (0 != PAL_Initialize(argc, argv))
    {
        return FAIL;
    }


    /*
    ** test to make sure we get into the exception block
    */
    
    PAL_TRY 
    {
        if (bExcept)
        {
            Fail("PAL_EXCEPT_FILTER: ERROR -> Something weird is going on."
                " PAL_EXCEPT_FILTER was hit before PAL_TRY.\n");
        }
        bTry = TRUE;    /* indicate we hit the PAL_TRY block */
        *p = 13;        /* causes an access violation exception */

        Fail("PAL_EXCEPT_FILTER: ERROR -> code was executed after the "
            "access violation.\n");
    }
    PAL_EXCEPT_FILTER(ExitFilter, (LPVOID)&nValidator)
    {
        if (!bTry)
        {
            Fail("PAL_EXCEPT_FILTER: ERROR -> Something weird is going on."
                " PAL_EXCEPT_FILTER was hit without PAL_TRY being hit.\n");
        }
        bExcept = TRUE; /* indicate we hit the PAL_EXCEPT_FILTER block */
    }
    PAL_ENDTRY;

    if (!bTry)
    {
        Trace("PAL_EXCEPT_FILTER: ERROR -> It appears the code in the PAL_TRY"
            " block was not executed.\n");
    }

    if (!bExcept)
    {
        Trace("PAL_EXCEPT_FILTER: ERROR -> It appears the code in the "
            "PAL_EXCEPT_FILTER block was not executed.\n");
    }

    if (!bFilter)
    {
        Trace("PAL_EXCEPT_FILTER: ERROR -> It appears the code in the filter"
            " function was not executed.\n");
    }


    /* did we hit all the code blocks? */
    if(!bTry || !bExcept || !bFilter)
    {
        Fail("");
    }


    PAL_Terminate();  
    return PASS;

}
