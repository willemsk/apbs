/** @defgroup PBAMparm PBAMparm class
 *  @brief    Parameter which holds useful parameters for Poisson-boltzmann 
 *            analytical method calculations
 */

/**
 *  @file     pbamparm.h
 *  @ingroup  PBAMparm
 *  @brief    Contains declarations for class PBAMparm
 *  @version  $Id$
 *  @author   Lisa Felberg
 *
 *  @attention
 *  @verbatim
 *
 * APBS -- Adaptive Poisson-Boltzmann Solver
 *
 *  Nathan A. Baker (nathan.baker@pnnl.gov)
 *  Pacific Northwest National Laboratory
 *
 *  Additional contributing authors listed in the code documentation.
 *
 * Copyright (c) 2010-2014 Battelle Memorial Institute. Developed at the
 * Pacific Northwest National Laboratory, operated by Battelle Memorial
 * Institute, Pacific Northwest Division for the U.S. Department of Energy.
 *
 * Portions Copyright (c) 2002-2010, Washington University in St. Louis.
 * Portions Copyright (c) 2002-2010, Nathan A. Baker.
 * Portions Copyright (c) 1999-2002, The Regents of the University of
 * California.
 * Portions Copyright (c) 1995, Michael Holst.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the developer nor the names of its contributors may be
 * used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @endverbatim
 */


#ifndef _PBAMPARM_H_
#define _PBAMPARM_H_

/* Generic header files */
#include "maloc/maloc.h"

#include "generic/vhal.h"
#include "generic/vstring.h"

/**
 * @brief  Calculation type
 * @ingroup PBAMparm
 */
enum ePBAMparm_CalcType {
    //other methods disabled for now only auto currently implemented.
	//PBAMCT_MANUAL=0,  /**< PBAM-manual */
    PBAMCT_AUTO=1,  /**< PBAM-auto */
    //PBAMCT_NONE=2 /**< not defined */
};

/**
 * @brief  Declare PBAMparm_CalcType type
 * @ingroup  PBAMparm
 */
typedef enum ePBAMparm_CalcType PBAMparm_CalcType;

/**
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @brief   Parameter structure for PBAM-specific variables from input files
 *  @note    If you add/delete/change something in this class, the member
 *           functions -- especially PBAMparm_copy -- must be modified
 *           accordingly
 */
typedef struct sPBAMparm {

    PBAMparm_CalcType type;  /**< What type of PBAM calculation? */
    int parsed;  /**< Has this structure been filled? (0 = no, 1 = yes) */

    /* *** GENERIC PARAMETERS *** */
    int vdw;
    int setvdw;
    double etol; /**< user defined error tolerance */

} PBAMparm;

/** @brief   Construct PBAMparm object
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   type Type of PBAM calculation
 *  @returns Newly allocated and initialized PBAMparm object
 */
VEXTERNC PBAMparm*  PBAMparm_ctor(PBAMparm_CalcType type);

/** @brief   FORTRAN stub to construct PBAMparm object ?????????!!!!!!!
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   thee Space for PBAMparm object
 *  @param   type Type of MG calculation
 *  @returns Success enumeration
 */
VEXTERNC Vrc_Codes      PBAMparm_ctor2(PBAMparm *thee, PBAMparm_CalcType type);

/** @brief   Object destructor
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   thee  Pointer to memory location of PBAMparm object
 */
VEXTERNC void     PBAMparm_dtor(PBAMparm **thee);

/** @brief   FORTRAN stub for object destructor   ?????????!!!!!!!!!!!!
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   thee  Pointer to PBAMparm object
 */
VEXTERNC void     PBAMparm_dtor2(PBAMparm *thee);

/** @brief   Consistency check for parameter values stored in object
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   thee   PBAMparm object
 *  @returns Success enumeration
 */
VEXTERNC Vrc_Codes      PBAMparm_check(PBAMparm *thee);

/** @brief   Parse an MG keyword from an input file
 *  @ingroup PBAMparm
 *  @author  Andrew Stevens, Kyle Monson
 *  @param   thee   PBAMparm object
 *  @param   tok    Token to parse
 *  @param   sock   Stream for more tokens
 *  @returns Success enumeration (1 if matched and assigned; -1 if matched, but there's some sort
 *            of error (i.e., too few args); 0 if not matched)
 */
VEXTERNC Vrc_Codes      PBAMparm_parseToken(PBAMparm *thee, char tok[VMAX_BUFSIZE],
                    Vio *sock);
/**
 * @brief copy PBAMparm object int thee.
 * @ingroup PBAMparm
 * @author
 * @param thee PBAMparm object to be copied into
 * @param parm PBAMparm object.
 */
VEXTERNC void PBAMparm_copy(PBAMparm *thee, PBAMparm *parm);

VPRIVATE Vrc_Codes PBAMparm_parseVDW(PBAMparm *thee, Vio *sock);

VPRIVATE Vrc_Codes PBAMparm_parseETOL(PBAMparm *thee, Vio *sock);



#endif

