#ifndef _MEMBRANE_H_
#define _MEMBRANE_H_

#include "apbscfg.h"
#include "generic/vhal.h"

/**
 * @ingroup Vpmg
 * @brief Define membrane shape enumeration
 */
enum eMemShape {
    MS_SLAB=0, /**< Slab shape */
    MS_CONE=1, /**< Cone shape */
    MS_BOWTIE=2 /**< Bowtie/hourglass shape */
};
typedef enum eMemShape MemShape;

/**
 *  @ingroup Vpmg
 *  @author  Jules
 *  @brief   Parameter structure for membrane
 */
struct sMemParm {
    int haveMembrane; /**< Flag to indicate if a membrane is present */
    MemShape shape; /**< Membrane shape */
    double dielectric; /**< Membrane dielectric constant */
    double center[3]; /**< Membrane center */
    char axis; /**< Membrane axis */
    double thickness; /**< Membrane thickness */
    double radius; /**< Pore radius at one opening */
    double radius2; /**< Pore radius at the other opening. If not specified, defaults to radius. */
    double neck_radius; /**< Pore neck radius (for bowtie shape) */
    double neckshift; /**< Shift of the neck from the membrane center (for bowtie shape) */
};

typedef struct sMemParm MemParm;

VEXTERNC MemParm* MemParm_ctor();
VEXTERNC void MemParm_dtor(MemParm **thee);
VEXTERNC void MemParm_copy(MemParm *thee, MemParm *parm);
VEXTERNC int is_in_membrane(double pt[3], MemParm *memparm);

#endif /* _MEMBRANE_H_ */
