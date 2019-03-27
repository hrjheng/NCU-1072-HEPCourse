import IPython.core.pylabtools as pyt
import ROOT
import math
from GlauberMC_classes import *

## The nuclear charge probability density
def Fermi_dist(x, par):

    rho_0 = par[0]  # nucleon density
    R = par[1]  # nuclear radius
    a = par[2]  # skin depth
    w = par[3]  # deviations from a spherical shape

    result = x[0] * x[0] * ((1. + w * pow(x[0] / R, 2.)) / (1. + math.exp(
        (x[0] - R) / a)))

    return rho_0 * result


# Fill the nucleus with the charge probability density
def Fill_nuclei(nucleus, ToDraw):
    random = ROOT.TRandom3()
    r_pdf = ROOT.TF1('fermi', Fermi_dist, 0, 20, 4)
    r_pdf.SetParameters(1, nucleus.R, nucleus.a, nucleus.w)
    for inucl in range(nucleus.Z):
        r = r_pdf.GetRandom(0, nucleus.R)
        # The probability distribution is typically taken to be uniform in azimuthal and polar angles
        ctheta = 2. * random.Rndm() - 1.
        stheta = pow(1. - ctheta * ctheta, 1. / 2.)
        phi = 2. * random.Rndm() * math.pi
        child_nuclei_ = nuclei(nucleus, ToDraw)
        child_nuclei_.SetX(nucleus.x + r * stheta * math.cos(phi), ToDraw)
        child_nuclei_.SetY(nucleus.y + r * stheta * math.sin(phi), ToDraw)
        child_nuclei_.SetZ(nucleus.z + r * ctheta, ToDraw)
        nucleus.Add_nuclei(child_nuclei_)

        del child_nuclei_

    del r_pdf


def distance(eleA, eleB):
    # return pow(pow(eleA.x - eleB.x, 2) + pow(eleA.y - eleB.y, 2) + pow(eleA.z - eleB.z, 2), 1 / 2)
    return pow(pow(eleA.x - eleB.x, 2) + pow(eleA.y - eleB.y, 2), 1. / 2.)

def Collision(NucA, NucB):
    list_NucA_IsCol = [False] * NucA.Z
    list_NucB_IsCol = [False] * NucB.Z

    for iNucA in range(NucA.Z):
        for iNucB in range(NucB.Z):

            if distance(
                    NucA.list_nuclei[iNucA], NucB.list_nuclei[iNucB]) < 0.5 * (
                        NucA.list_nuclei[iNucA].D + NucB.list_nuclei[iNucB].D):
                NucA.list_nuclei[iNucA].IsParticipant()
                NucB.list_nuclei[iNucB].IsParticipant()
                NucA.list_nuclei[iNucA].Ncollisions += 1
                NucB.list_nuclei[iNucA].Ncollisions += 1
