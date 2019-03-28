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


(opt, args) = parser.parse_args()

Nuclei_type = opt.Nucleus
B = opt.ImpactParameter
XS_NN = opt.CrossSection
Nevt = opt.EventNumber

start_time = time.time()

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
    f_pd = open('collision-data/{0}-IPRandomfm-XSNN{1:.1f}mb-Nevt{2:.0f}/Event_Dataframe.pkl'
    .format(Nuclei_type, XS_NN, Nevt), 'wb')
else:
    f_out = open('collision-data/{0}-IP{1:.1f}fm-XSNN{2:.1f}mb-Nevt{3:.0f}/Events.pkl'
    .format(Nuclei_type, B, XS_NN, Nevt), 'wb')
    f_pd = open('collision-data/{0}-IP{1:.1f}fm-XSNN{2:.1f}mb-Nevt{3:.0f}/Event_Dataframe.pkl'
    .format(Nuclei_type, B, XS_NN, Nevt), 'wb')

list_event = []

for ievt in range(Nevt):
    if B < 0.0:
        # b = pow((b_max*b_max-b_min*b_min)*random.Rndm()+b_min*b_min, 1./2.)
        b = math.sqrt((b_max*b_max-b_min*b_min)*random.Rndm()+b_min*b_min)
    else:
        b = B

    NucleusA = nucleus(Nuclei_type, 0 + b / 2., 0., 0., Z, a, w, XS_NN)
    NucleusB = nucleus(Nuclei_type, 0 - b / 2., 0., 0., Z, a, w, XS_NN)
    NucleusA.Fill_nuclei()
    NucleusB.Fill_nuclei()

    Event = Collision_Event(NucleusA, NucleusB, b)
    Event.Collision()
    Event.SetEvent()
    list_event.append(Event)

    del NucleusA, NucleusB, Event

    if (ievt%500) == 0:
        print('Ev = ', ievt)
        gc.collect()

pickle.dump(list_event, f_out)
f_out.close()
## Make dataframe (convenient for analysis)
df = MakeDataframe(list_event)
pickle.dump(df, f_pd)
f_pd.close()
print ('Excuted in %.4f seconds.' % (time.time() - start_time))
