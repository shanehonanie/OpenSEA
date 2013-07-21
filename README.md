OpenSEA
===================================================================================================

Open Source Seakeeping Evaluation and Analysis software suite

OpenSEA is an open source full featured seakeeping software suite.  
The software suite can calculate hydrodynamic properties for any 
arbitrary body, or combination of bodies.  It can then evaluate those 
hydrodynamic properties along with user defined forces to calculate 
frequency-based body responses, resonant frequencies and mode shape, 
time-based body responses, and Fourier analysis of time histories 
to determine non-linear responses.

What are the major differences between OpenSEA and other seakeeping programs?

    - Open source:  Completely free with all source available for use.
    - Arbitrary body shapes:  Many seakeeping software uses Lewis section 
      based methods, which require ship-shaped bodies.  OpenSEA uses full 
      hydrodynamic radiation-diffraction evaluations to allow any arbitrary body shape, 
      and any number of bodies.
    - Simplified hydrodynamic methods:  Many of the full radiation-diffraction suites 
      were developed in the 1970′s – 1980′s.  The developers at that time were keenly aware 
      of the limits of computer power.  To compensate for limited computing power, the 
      mathematics for those software packages were highly analytical.  This required using 
      multiple bezel functions to simulate the presence of fluid domain boundaries, instead 
      of physically meshing the boundaries.  Why does this matter?  Bezel functions are tough!  
      They take a large amount of computational effort to evaluate and are usually approximated 
      with simpler functions.  This introduces inaccuracy.  OpenSEA recognizes the advancement 
      in computer technology and instead meshes all fluid boundaries for direct evaluation of the 
      boundary conditions.  This creates a more robust and expandable approach.
    - Modern object oriented programming:  Computer programming was very different in the 
      70′s-80′s when many of the other seakeeping programs were developed.  FORTRAN was the 
      popular language for scientific computing.  This legacy language can inhibit continued 
      development of these programs.  OpenSEA uses modern object oriented programming techniques 
      with C++ programming language.

Want to learn more?  Read on for a full list of features associated with each software package 
and applications for OpenSEA.

Features
===================================================================================================

The software suite is comprised of five major software packages.  The major features for each package 
are listed below.

oHyro – Hydrodynamic Diffraction

     - oHydro calculates properties for hydrodynamic radiation and diffraction.  It supports 
       multiple bodies, hydrodynamic interaction between bodies, forward speeds, wave drift force 
       calculations, and much more.  The program operates multi-threaded to take advantage of 
       modern multi-core computer systems.  The program also supports deformation of the surface 
       mesh to incorporate non-linear free surface conditions.

oFreq – Frequency Based Dynamics Analysis

     - oFreq has two modes of operation.  It performs frequency based linear response analysis.  
       Or, it calculates resonant frequencies and mode shapes.  The program incorporates user forces 
       and hydrodynamic forces.  Response amplitude and phase are calculated for each individual 
       degree of freedom  The program is flexible enough to allow definition of any system of motion, 
       with unlimited degrees of freedom.

oTime – Time Based Dynamics Analysis

     - oTime is used to calculate fully non-linear dynamic responses.  oTime includes hydrodynamic 
       forces and user defined forces.  All forces are resolved for each individual time step, 
       which allows fully non-linear response calculations.
 
oFourier – Spectrum Decomposition of Time History

     - oFourier performs frequency transformations of time histories.  It has two main applications.
       1.  Frequency analysis of output from oTime
       2.  Frequency analysis of experimental output from wave buoys or seakeeping trials

oBatch – Batch Runs for Combinations of Above Applications

     - OpenSEA has several different programs in it’s suite.  oBatch allows automated execution 
       and control of other programs in the OpenSEA suite.  When combined with a table of 
       parameter variations, oBatch can be used to repeat and automate a complicated seakeeping 
       analysis for any number of seakeeping conditions.
     - oBatch also aggregates and summarizes results for easily evaluation of a vessel’s 
       seakeeping performance.