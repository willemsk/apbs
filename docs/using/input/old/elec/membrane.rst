.. _membrane:

membrane
========

Specify a membrane to be included in the calculation.

This keyword is used to define a membrane region with a different dielectric
constant from the solvent and solute. The membrane is modeled as an
infinite slab of a given thickness along a specified axis. Within this slab,
a pore can be defined with various shapes. The membrane region is also
treated as inaccessible to ions.

The parameters below define the geometry of the **pore** within the membrane slab.

Syntax
------

``membrane``
    ``shape`` (string)
    ``dielectric`` (float)
    ``center`` (float, float, float)
    ``axis`` (char)
    ``thickness`` (float)
    (shape-specific parameters)
``end``

Shape-Specific Parameters
-------------------------

**slab**

A cylindrical pore.

*   ``radius`` (float): The radius of the cylindrical pore.

**cone**

A truncated conical pore.

*   ``radius`` (float): The radius of the pore at the top (positive side of the axis).
*   ``radius2`` (float): The radius of the pore at the bottom (negative side of the axis). If not specified, it defaults to the value of ``radius``.

**bowtie**

A pore shaped like two truncated cones joined at their narrow ends (an hourglass).

*   ``radius`` (float): The radius of the pore at the top opening.
*   ``radius2`` (float): The radius of the pore at the bottom opening. If not specified, it defaults to the value of ``radius``, creating a symmetric bowtie.
*   ``neckradius`` (float): The radius of the pore at its narrowest point (the "neck").
*   ``neckshift`` (float): The displacement of the neck from the center of the membrane along the specified axis. A positive value shifts the neck towards the "top" (positive side of the axis), and a negative value shifts it towards the "bottom". The default value is 0.0.

Example
-------

Here is an example of an asymmetric bowtie pore with a shifted neck:

.. code-block:: none

    membrane
        shape bowtie
        dielectric 2.0
        center 0.0 0.0 0.0
        axis z
        thickness 40.0
        radius 20.0
        radius2 15.0
        neckradius 5.0
        neckshift 5.0
    end
