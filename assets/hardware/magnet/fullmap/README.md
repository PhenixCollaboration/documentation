# The original "Full Map" of the PHENIX magnetic field

The file fullmap.out contains a full field map in the volume
* -200cm <= z <= 200cm ; 0 <= r <= 400cm ;  phi in 3deg steps
* +zet is north (Bzet is negative because the field points south),
* 0 deg is towards the back of the mfh (west), 90deg is up.

Note: for |z| > 100 or r > 300 bzet and brad are the same for all phi, bphi is set to 0
according to previous discussions. It means that this map is completely useless inside the
return yoke, but it should be reasonably
good where the detectors are.
