### ATLAS results from https://arxiv.org/abs/1706.09363

ATLAS_pp_100to126_central = [0.1541,0.32161,0.56281,0.85762,1.11893,1.31323,1.48074,1.72194,2.17755,2.51256]
ATLAS_pp_100to126_Statup = [0.06031,0.05360,0.06031,0.05360,0.05360,0.05360,0.06030,0.06030,0.05361,0.09381]
ATLAS_pp_100to126_Statdown = [0.0603,0.05360,0.06030,0.06030,0.06030,0.06030,0.06030,0.05360,0.06030,0.08710]
ATLAS_pp_100to126_Systup = [0.0402,0.06030,0.06701,0.06030,0.04690,0.04690,0.05360,0.05360,0.04021,0.03350]
ATLAS_pp_100to126_Systdown = [0.0402,0.06030,0.06030,0.06700,0.05360,0.05360,0.05360,0.04690,0.04690,0.03350]
Norm_pp_100to126 = 0.0
for ibin in range(len(ATLAS_pp_100to126_central)):
    Norm_pp_100to126 = Norm_pp_100to126 + ATLAS_pp_100to126_central[ibin]


ATLAS_pp_126to158_central = [0.10406,0.25462,0.48034,0.79371,1.04455,1.23288,1.42127,1.72239,2.26142,2.72544]
ATLAS_pp_126to158_Statup = [0.07510,0.06259,0.06258,0.06258,0.06258,0.06258,0.06258,0.06258,0.0625799999999996,0.12517]
ATLAS_pp_126to158_Statdown = [0.07508,0.07510,0.06260,0.07510,0.07510,0.07510,0.07510,0.07510,0.07510,0.13768]
ATLAS_pp_126to158_Systup = [0.02503,0.01252,0.03755,0.03755,0.05006,0.03753,0.05006,0.03755,0.03755,0.02503]
ATLAS_pp_126to158_Systdown = [0.02503,0.02503,0.02503,0.05007,0.05007,0.0500799999999999,0.0500700000000001,0.05006,0.05007,0.02503]
Norm_pp_126to158 = 0.0
for ibin in range(len(ATLAS_pp_126to158_central)):
    Norm_pp_126to158 = Norm_pp_126to158 + ATLAS_pp_126to158_central[ibin]



ATLAS_pp_158to200_central = [0.08399,0.20933,0.4097,0.71008,0.98552,1.14857,1.31167,1.62482,2.30047,2.97622]
ATLAS_pp_158to200_Statup = [0.06249,0.06248,0.06248,0.06248,0.07498,0.06248,0.06248,0.07498,0.07498,0.0874799999999998]
ATLAS_pp_158to200_Statdown = [0.06248,0.08748,0.07498,0.08748,0.06248,0.07498,0.07498,0.08748,0.07498,0.09998]
ATLAS_pp_158to200_Systup = [0.02501,0.03747,0.03747,0.04999,0.03749,0.02499,0.02501,0.03749,0.03749,0.02499]
ATLAS_pp_158to200_Systdown = [0.01249,0.03749,0.03749,0.04999,0.02499,0.02500,0.03749,0.03749,0.04998,0.04999]
Norm_pp_158to200 = 0.0
for ibin in range(len(ATLAS_pp_158to200_central)):
    Norm_pp_158to200 = Norm_pp_158to200 + ATLAS_pp_158to200_central[ibin]


ATLAS_pp_200toinv_central = [0.0789,0.19174,0.34212,0.55503,0.83047,1.08099,1.30657,1.58224,2.27038,3.33353]
ATLAS_pp_200toinv_Statup = [0.07499,0.07498,0.07498,0.06248,0.06248,0.06249,0.06251,0.06248,0.07499,0.09998]
ATLAS_pp_200toinv_Statdown = [0.06248,0.07498,0.06248,0.07498,0.08748,0.07498,0.07498,0.07499,0.07498,0.08748]
ATLAS_pp_200toinv_Systup = [0.0125,0.02501,0.03749,0.03747,0.03747,0.0500100000000001,0.04999,0.04998,0.06249,0.06248]
ATLAS_pp_200toinv_Systdown = [0.01249,0.02499,0.03749,0.03751,0.04999,0.04999,0.04998,0.06249,0.0499799999999997,0.04999]
Norm_pp_200toinv = 0.0
for ibin in range(len(ATLAS_pp_200toinv_central)):
    Norm_pp_200toinv = Norm_pp_200toinv + ATLAS_pp_200toinv_central[ibin]

Nbins_ATLAS = 10

gr_ATLAS_pp_100to126_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_100to126_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_100to126_Statdown),
                                                np.array(ATLAS_pp_100to126_Statup))

gr_ATLAS_pp_100to126_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_100to126_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_100to126_Systdown),
                                                np.array(ATLAS_pp_100to126_Systup))

gr_ATLAS_pp_126to158_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_126to158_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_126to158_Statdown),
                                                np.array(ATLAS_pp_126to158_Statup))

gr_ATLAS_pp_126to158_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_126to158_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_126to158_Systdown),
                                                np.array(ATLAS_pp_126to158_Systup))

gr_ATLAS_pp_158to200_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_158to200_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_158to200_Statdown),
                                                np.array(ATLAS_pp_158to200_Statup))

gr_ATLAS_pp_158to200_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_158to200_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_158to200_Systdown),
                                                np.array(ATLAS_pp_158to200_Systup))

gr_ATLAS_pp_200toinv_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_200toinv_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_200toinv_Statdown),
                                                np.array(ATLAS_pp_200toinv_Statup))

gr_ATLAS_pp_200toinv_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_pp_200toinv_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_pp_200toinv_Systdown),
                                                np.array(ATLAS_pp_200toinv_Systup))


list_ATLAS_Norm_pp = []
list_ATLAS_Norm_pp.append(Norm_pp_100to126)
list_ATLAS_Norm_pp.append(Norm_pp_126to158)
list_ATLAS_Norm_pp.append(Norm_pp_158to200)
list_ATLAS_Norm_pp.append(Norm_pp_200toinv)

list_ATLAS_gr_pp_Stat = []
list_ATLAS_gr_pp_Stat.append(gr_ATLAS_pp_100to126_Stat)
list_ATLAS_gr_pp_Stat.append(gr_ATLAS_pp_126to158_Stat)
list_ATLAS_gr_pp_Stat.append(gr_ATLAS_pp_158to200_Stat)
list_ATLAS_gr_pp_Stat.append(gr_ATLAS_pp_200toinv_Stat)

list_ATLAS_gr_pp_Syst = []
list_ATLAS_gr_pp_Syst.append(gr_ATLAS_pp_100to126_Syst)
list_ATLAS_gr_pp_Syst.append(gr_ATLAS_pp_126to158_Syst)
list_ATLAS_gr_pp_Syst.append(gr_ATLAS_pp_158to200_Syst)
list_ATLAS_gr_pp_Syst.append(gr_ATLAS_pp_200toinv_Syst)
