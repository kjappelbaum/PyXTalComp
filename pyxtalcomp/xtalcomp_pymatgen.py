from pyxtalcomp_cpp import compare_xtalcomp


class XtalCompASE(object):
    def __init__(self):
        pass

    def __call__(self, struct1, struct2, cart_tol=0.05, angle_tol=0.5, reduce_cell=False):
        """
        Compare two pymatgen structures.
        
        Args:
            struct1 (object): pytmagen structure object
            struct2 (object): pymatgen structure object
            cart_tol (float): cartesian tolerance for xtalcomp
            angle_tol (float): angle folerance for xtalcomp
            reduce_cell (bool):

        Returns:
            match boolean
        """
        positions1 = struct1.frac_coords()
        symbs1 = [species.name for species in struct1.species]
        cell1 = struct1.lattice.matrix

        positions2 = struct2.frac_coords()
        symbs2 = [species.name for species in struct2.species]
        cell2 = struct2.lattice.matrix

        match = compare_xtalcomp(positions1,symbs1, cell1,
                                 positions2, symbs2, cell2, cart_tol, angle_tol, reduce_cell)
        return match
