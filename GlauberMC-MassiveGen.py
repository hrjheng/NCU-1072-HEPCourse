from optparse import OptionParser
import gc
import sys,os,datetime
import time
import ROOT
from array import array as ary
import math
import pickle
from GlauberMC_classes import *
from GlauberMC_Utilities import *


parser = OptionParser(usage="usage: %prog ver [options -n]")
parser.add_option("-n", "--Nucleus", dest="Nucleus", default='Si_28', help="Nucleus (Default = Si_28); currently there are Si_28, S_32, Ca_40, Ni_58, Cu_62, Au_197, Pb_207.")
parser.add_option("-b", "--ImpactParameter", dest='ImpactParameter', type="float", default=5.0, help="Impact parameter (Default = 5.0 fm)") # kUPDATE
parser.add_option("-x", "--CrossSection", dest='CrossSection', type="float", default=42, help="XS_NN (Default = 42.0 mb)")
parser.add_option("-N", "--Nevt", dest="EventNumber", type="int", default=10000, help="Number of events to generate (Default = 10k)")
parser.add_option("-D", "--MakePlots", dest="MakePlots", action="store_true", default=False, help="Make plots or not (Default = False)")

(opt, args) = parser.parse_args()

Nuclei_type = opt.Nucleus
B = opt.ImpactParameter
XS_NN = opt.CrossSection
Nevt = opt.EventNumber
IfDraw = opt.MakePlots

start_time = time.time()

dic_Z={'Si_28':28.,
       'S_32':32.,
       'Ca_40':40.,
       'Ni_58':58.,
       'Cu_62':62.,
       'Au_197':197.,
       'Pb_207':207.}

dic_a={'Si_28':0.580,
       'S_32':2.191,
       'Ca_40':0.586,
       'Ni_58':0.517,
       'Cu_62':0.596,
       'Au_197':0.535,
       'Pb_207':0.546}

dic_w={'Si_28':-0.233,
       'S_32':0.16,
       'Ca_40':-0.161,
       'Ni_58':-0.1308,
       'Cu_62':0.,
       'Au_197':0.,
       'Pb_207':0.}


b_max = 20.
b_min = 0.
b = 0.
random = ROOT.TRandom3(int(time.time()))

os.makedirs('collision-data/', exist_ok=True)
if B < 0.0:
    os.makedirs('collision-data/{0}-IPRandomfm-XSNN{1:.1f}mb-Nevt{2:.0f}'.format(Nuclei_type, XS_NN, Nevt),exist_ok=True)
else:
    os.makedirs('collision-data/{0}-IP{1:.1f}fm-XSNN{2:.1f}mb-Nevt{3:.0f}'.format(Nuclei_type, B, XS_NN, Nevt),exist_ok=True)

D = pow(0.1 * XS_NN / math.pi, 1. / 2.)  # [fm]
Z = dic_Z.get(Nuclei_type)
a = dic_a.get(Nuclei_type)
w = dic_w.get(Nuclei_type)

if B < 0.0:
    f_out = open('collision-data/{0}-IPRandomfm-XSNN{1:.1f}mb-Nevt{2:.0f}/Events.pkl'
    .format(Nuclei_type, XS_NN, Nevt), 'wb')
else:
    f_out = open('collision-data/{0}-IP{1:.1f}fm-XSNN{2:.1f}mb-Nevt{3:.0f}/Events.pkl'
    .format(Nuclei_type, B, XS_NN, Nevt), 'wb')

list_event = []

for ievt in range(Nevt):
    if B < 0.0:
        # b = pow((b_max*b_max-b_min*b_min)*random.Rndm()+b_min*b_min, 1./2.)
        b = math.sqrt((b_max*b_max-b_min*b_min)*random.Rndm()+b_min*b_min)
    else:
        b = B

    NucleusA = nucleus(Nuclei_type, 0 + b / 2., 0., 0., Z, a, w, XS_NN, IfDraw)
    NucleusB = nucleus(Nuclei_type, 0 - b / 2., 0., 0., Z, a, w, XS_NN, IfDraw)
    Fill_nuclei(NucleusA, IfDraw)
    Fill_nuclei(NucleusB, IfDraw)

    Collision(NucleusA, NucleusB)
    Event = Collision_Event(NucleusA, NucleusB, b)
    Event.SetEvent()
    list_event.append(Event)

    del NucleusA, NucleusB, Event

    if (ievt%500) == 0:
        print('Ev = ', ievt)
        gc.collect()

pickle.dump(list_event, f_out)
f_out.close()
print ('Excuted in %.4f seconds.' % (time.time() - start_time))
