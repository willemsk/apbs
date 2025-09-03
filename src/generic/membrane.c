#include "membrane.h"
#include <math.h>

MemParm* MemParm_ctor() {
    MemParm *thee = VNULL;
    thee = (MemParm*)Vmem_malloc(VNULL, 1, sizeof(MemParm));
    thee->haveMembrane = 0;
    thee->shape = MS_SLAB;
    thee->dielectric = 2.0;
    thee->center[0] = 0.0;
    thee->center[1] = 0.0;
    thee->center[2] = 0.0;
    thee->axis = 'z';
    thee->thickness = 30.0;
    thee->radius = 10.0;
    thee->radius2 = 10.0;
    thee->neck_radius = 5.0;
    thee->neckshift = 0.0;
    return thee;
}

void MemParm_dtor(MemParm **thee) {
    if ((*thee) != VNULL) {
        Vmem_free(VNULL, 1, sizeof(MemParm), (void **)thee);
        (*thee) = VNULL;
    }
}

void MemParm_copy(MemParm *thee, MemParm *parm) {
    VASSERT(thee != VNULL);
    VASSERT(parm != VNULL);
    thee->haveMembrane = parm->haveMembrane;
    thee->shape = parm->shape;
    thee->dielectric = parm->dielectric;
    thee->center[0] = parm->center[0];
    thee->center[1] = parm->center[1];
    thee->center[2] = parm->center[2];
    thee->axis = parm->axis;
    thee->thickness = parm->thickness;
    thee->radius = parm->radius;
    thee->radius2 = parm->radius2;
    thee->neck_radius = parm->neck_radius;
    thee->neckshift = parm->neckshift;
}

int is_in_membrane(double pt[3], MemParm *memparm) {
    double x, y, z, r;
    double top, bottom;

    if (!memparm->haveMembrane) {
        return 0;
    }

    // For simplicity, assuming z-axis for now.
    if (memparm->axis != 'z') {
        Vnm_print(2, "is_in_membrane: only z-axis is currently supported!\n");
        return 0;
    }

    // Shift point to be relative to membrane center
    x = pt[0] - memparm->center[0];
    y = pt[1] - memparm->center[1];
    z = pt[2] - memparm->center[2];
    r = sqrt(x*x + y*y);

    // Get membrane slab boundaries
    top = memparm->thickness / 2.0;
    bottom = -memparm->thickness / 2.0;

    // Check if point is outside the membrane slab vertically
    if (z < bottom || z > top) {
        return 0;
    }

    // Now check if point is inside the pore or in the membrane material
    switch (memparm->shape) {
        case MS_SLAB:
            if (r > memparm->radius) {
                return 1; // In membrane
            }
            break;

        case MS_CONE: {
            // Linear interpolation of pore radius along z-axis.
            // radius is at top (+z), radius2 is at bottom (-z).
            double cone_radius = memparm->radius2 + (z - bottom) * (memparm->radius - memparm->radius2) / memparm->thickness;
            if (r > cone_radius) {
                return 1; // In membrane
            }
            break;
        }

        case MS_BOWTIE: {
            double neck_z = memparm->neckshift;
            double pore_radius_at_z;

            if (z >= neck_z) { // Point is in the top part of the hourglass
                double top_cone_height = top - neck_z;
                if (top_cone_height > 1e-9) { // Avoid division by zero
                    pore_radius_at_z = memparm->neck_radius + (z - neck_z) * (memparm->radius - memparm->neck_radius) / top_cone_height;
                } else { // neck is at the top, so radius is just the top radius
                    pore_radius_at_z = memparm->radius;
                }
            } else { // Point is in the bottom part of the hourglass
                double bottom_cone_height = neck_z - bottom;
                if (bottom_cone_height > 1e-9) { // Avoid division by zero
                    pore_radius_at_z = memparm->radius2 + (z - bottom) * (memparm->neck_radius - memparm->radius2) / bottom_cone_height;
                } else { // neck is at the bottom, so radius is just the bottom radius
                    pore_radius_at_z = memparm->radius2;
                }
            }

            if (r > pore_radius_at_z) {
                return 1; // In membrane
            }
            break;
        }

        default:
            return 0; // Should not happen
    }

    return 0; // In pore
}
