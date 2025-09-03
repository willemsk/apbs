This directory contains an example of how to use the new integrated membrane feature in APBS.

The `bowtie.in` file demonstrates how to define a bowtie-shaped membrane using the `membrane` keyword within an `elec` section. The calculation is run on the `protein.pqr` file, which is a model of a transmembrane helix.

To run this example, use the following command:

```
apbs bowtie.in
```

This will perform a multigrid Poisson-Boltzmann calculation with the specified membrane geometry. The results will be printed to standard output.

The `membrane` keyword supports three shapes: `slab`, `cone`, and `bowtie`. The parameters for each shape are described in the main APBS documentation.
