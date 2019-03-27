import ROOT
import math

class nucleus():
    def __init__(self, name, x, y, z, Z, a, w, xsec_NN, ToDraw):
        self.name = name
        self.x = x
        self.y = y
        self.z = z
        self.Z = int(Z)
        self.a = a
        self.w = w
        self.R = 1.2 * pow(Z, 1. / 3.)
        self.xsec_NN = xsec_NN  # [mb]
        self.list_nuclei = []
        if ToDraw == True:
            self.ellipse = ROOT.TEllipse(x, y, self.R, self.R)

    def Add_nuclei(self, child_nuclei):
        self.list_nuclei.append(child_nuclei)

    def AddList_nuclei(self, list_nuclei_):
        self.list_nuclei = list_nuclei_

    def ClearList_nuclei(self):
        self.list_nuclei.clear()

class nuclei():
    def __init__(self, Mom_nucleus, ToDraw):
        self.Mom_nucleus = Mom_nucleus
        self.D = pow(0.1 * Mom_nucleus.xsec_NN / math.pi, 1. / 2.)  # [fm]
        self.x = 0.
        self.y = 0.
        self.z = 0.
        self.Ncollisions = 0
        self.Participant = False  # By default (before collision) the nuclei is spectator
        if ToDraw == True:
            self.ellipse = ROOT.TEllipse(0., 0., self.D / 2., self.D / 2.)

    def IsParticipant(self):
        self.Participant = True

    def IsSpectator(self):
        self.Participant = False

    def SetX(self, x_, ToDraw):
        self.x = x_
        if ToDraw == True:
            self.ellipse.SetX1(x_)

    def SetY(self, y_, ToDraw):
        self.y = y_
        if ToDraw == True:
            self.ellipse.SetY1(y_)

    def SetZ(self, z_, ToDraw):
        self.z = z_


class Collision_Event():
    def __init__(self, NucA, NucB, b):
        self.NucA = NucA
        self.NucB = NucB
        self.b = b
        self.IfSetNpart = False
        self.IfSetNcoll = False
        self.Npart = 0.
        self.Ncoll = 0.
        self.MeanX = 0.
        self.MeanY = 0.
        self.MeanX2 = 0.
        self.MeanY2 = 0.
        self.MeanXY = 0.
        self.VarX = 0.
        self.VarY = 0.
        self.VarXY = 0.
        self.eps_RP = 0.
        self.eps_part = 0.


    def SetNpart(self):
        count_part = 0
        for iNucA in range(len(self.NucA.list_nuclei)):
            if self.NucA.list_nuclei[iNucA].Participant == True:
                count_part += 1

        for iNucB in range(len(self.NucB.list_nuclei)):
            if self.NucB.list_nuclei[iNucB].Participant == True:
                count_part += 1

        self.Npart = count_part
        self.IfSetNpart = True


    def SetNcoll(self):
        count_coll = 0
        for iNucA in range(len(self.NucA.list_nuclei)):
            if self.NucA.list_nuclei[iNucA].Participant == True:
                count_coll += self.NucA.list_nuclei[iNucA].Ncollisions

        for iNucB in range(len(self.NucB.list_nuclei)):
            if self.NucB.list_nuclei[iNucB].Participant == True:
                count_coll += self.NucB.list_nuclei[iNucB].Ncollisions

        self.Ncoll = count_coll
        self.IfSetNcoll = True


    def SetEvent(self):
        if self.IfSetNpart == False:
            Collision_Event.SetNpart(self)

        if self.IfSetNcoll == False:
            Collision_Event.SetNcoll(self)

        meanx = meany = meanx2 = meany2 = meanxy = 0.
        for iNucA in range(len(self.NucA.list_nuclei)):
            if self.NucA.list_nuclei[iNucA].Participant == True:
                meanx += self.NucA.list_nuclei[iNucA].x
                meany += self.NucA.list_nuclei[iNucA].y
                meanx2 += self.NucA.list_nuclei[iNucA].x * self.NucA.list_nuclei[iNucA].x
                meany2 += self.NucA.list_nuclei[iNucA].y * self.NucA.list_nuclei[iNucA].y
                meanxy += self.NucA.list_nuclei[iNucA].x * self.NucA.list_nuclei[iNucA].y

        for iNucB in range(len(self.NucB.list_nuclei)):
            if self.NucB.list_nuclei[iNucB].Participant == True:
                meanx += self.NucB.list_nuclei[iNucB].x
                meany += self.NucB.list_nuclei[iNucB].y
                meanx2 += self.NucB.list_nuclei[iNucB].x * self.NucB.list_nuclei[iNucB].x
                meany2 += self.NucB.list_nuclei[iNucB].y * self.NucB.list_nuclei[iNucB].y
                meanxy += self.NucB.list_nuclei[iNucB].x * self.NucB.list_nuclei[iNucB].y

        if self.Npart > 0.:
            self.MeanX = meanx / float(self.Npart)
            self.MeanY = meany / float(self.Npart)
            self.MeanX2 = meanx2 / float(self.Npart)
            self.MeanY2 = meany2 / float(self.Npart)
            self.MeanXY = meanxy / float(self.Npart)
            self.VarX = self.MeanX2 - self.MeanX * self.MeanX
            self.VarY = self.MeanY2 - self.MeanY * self.MeanY
            self.VarXY = self.MeanXY - self.MeanX * self.MeanY
            self.eps_RP = (self.VarY - self.VarX) / (self.VarY + self.VarX)
            self.eps_part = pow(pow(self.VarY - self.VarX,2) + 4. * pow(self.VarXY, 2), 1./2.) / (self.VarY + self.VarX)
        else:
            self.MeanX = self.MeanY = self.MeanX2 = self.MeanY2 = self.MeanXY = self.VarX = self.VarY = self.VarXY = self.eps_RP = self.eps_part = float('NaN')
