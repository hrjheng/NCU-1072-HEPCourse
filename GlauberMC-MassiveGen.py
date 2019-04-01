from optparse import OptionParser
import gc
import sys,os,datetime
import time
import ROOT
from array import array as ary
import math
import pickle
import pandas as pd
from GlauberMC_classes import *
from GlauberMC_Utilities import *


parser = OptionParser(usage="usage: %prog ver [options -n]")
parser.add_option("-n", "--Nucleus", dest="Nucleus", default='Si_28', help="Nucleus (Default = Si_28); currently there are Si_28, S_32, Ca_40, Ni_58, Cu_62, Au_197, Pb_207.")
parser.add_option("-b", "--ImpactParameter", dest='ImpactParameter', type="float", default=5.0, help="Impact parameter (Default = 5.0 fm)") # kUPDATE
parser.add_option("-x", "--CrossSection", dest='CrossSection', type="float", default=42, help="XS_NN (Default = 42.0 mb)")
parser.add_option("-N", "--Nevt", dest="EventNumber", type="int", default=10000, help="Number of events to generate (Default = 10k)")
parser.add_option("-s", dest="SaveNucToEvent", action="store_true", default=False, help="Save nucleus in event object (Default = False)")

(opt, args) = parser.parse_args()

Nuclei_type = opt.Nucleus
B = opt.ImpactParameter
XS_NN = opt.CrossSection
Nevt = opt.EventNumber
SaveNuc = opt.SaveNucToEvent

os.makedirs('collision-data/', exist_ok=True)
if B < 0.0:
    os.makedirs('collision-data/{0}-IPRandomfm-XSNN{1:.1f}mb-Nevt{2:.0f}'.format(Nuclei_type, XS_NN, Nevt),exist_ok=True)
else:
    os.makedirs('collision-data/{0}-IP{1:.1f}fm-XSNN{2:.1f}mb-Nevt{3:.0f}'.format(Nuclei_type, B, XS_NN, Nevt),exist_ok=True)

start_time = time.time()
prev_time = time.time()

b_max = 20.
b_min = 0.
b = 0.
random = ROOT.TRandom3(int(time.time()))

D = pow(0.1 * XS_NN / math.pi, 1. / 2.)  # [fm]
Z = dic_Z.get(Nuclei_type)
a = dic_a.get(Nuclei_type)
w = dic_w.get(Nuclei_type)

b_max = 1.1 * 2.0 * (1.2 * pow(Z, 1. / 3.))

NucleusA = nucleus(Nuclei_type, 0., 0., 0., Z, a, w, XS_NN)
NucleusB = nucleus(Nuclei_type, 0., 0., 0., Z, a, w, XS_NN)

ievt = 1
list_event = []
while (ievt < Nevt+1):
    # print (ievt)
    attempt = 0

    if B < 0.0:
        b = math.sqrt((b_max*b_max-b_min*b_min)*random.Rndm()+b_min*b_min)
    else:
        b = B

    NucleusA.SetPosition(0 + b / 2., 0., 0.)
    NucleusB.SetPosition(0 - b / 2., 0., 0.)
    NucleusA.Fill_nuclei()
    NucleusB.Fill_nuclei()

    Event = Collision_Event(NucleusA, NucleusB, b, SaveNuc)
    Event.Collision(NucleusA, NucleusB)
    Event.SetEvent(NucleusA, NucleusB)

    NucleusA.ClearList_nuclei()
    NucleusB.ClearList_nuclei()

    if attempt < 10:
        if Event.Npart > 1 and Event.Ncoll > 1:
            ievt += 1
            list_event.append(Event)
        else:
            attempt += 1
    else:
        ievt += 1
        list_event.append(Event)


    if (ievt % 500) == 0:
        print ('Ev = ', ievt, 'Excuted in %.4f seconds...' % (time.time() - prev_time))
        prev_time = time.time()
        f_pd = open('collision-data/{0}-IPRandomfm-XSNN{1:.1f}mb-Nevt{2:.0f}/Event_Dataframe_{3}.pkl'.format(Nuclei_type, XS_NN, Nevt, int(ievt/500)), 'wb')
        df = MakeDataframe(list_event)
        pickle.dump(df, f_pd)
        f_pd.close()
        del list_event[:], df, f_pd

    if (ievt % 100) == 0:
        gc.collect()
        
    del Event

print ('Excuted in %.4f seconds.' % (time.time() - start_time))
