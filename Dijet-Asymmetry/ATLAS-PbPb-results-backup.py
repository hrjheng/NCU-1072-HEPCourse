### ATLAS results from https://arxiv.org/abs/1706.09363

ATLAS_PbPb_Xbin = [0.33597,0.3769,0.4231,0.47459,0.53267,0.59736,0.66997,0.75182,0.8429,0.94587]
ATLAS_PbPb_Xup = [0.01889,0.02185,0.02392,0.02729,0.03065,0.03399,0.03818,0.04410,0.04958,0.05413]
ATLAS_PbPb_Xdown = [0.01842,0.02204,0.02435,0.02757,0.03079,0.03404,0.03643,0.04148,0.04698,0.05339]

ATLAS_PbPb_100to126_central = [0.0536,0.27471,0.79062,1.75544,2.51256,2.34506,1.76884,1.42044,1.37353,1.34673]
ATLAS_PbPb_100to126_Statup = [0.0335,0.02680,0.04020,0.04691,0.04020,0.04020,0.04021,0.04020,0.03351,0.03350]
ATLAS_PbPb_100to126_Statdown = [0.0469,0.04020,0.04690,0.05360,0.04690,0.04020,0.04020,0.04021,0.04020,0.04020]
ATLAS_PbPb_100to126_Systup = [0.0603,0.20100,0.34841,0.45562,0.40201,0.25460,0.18091,0.14740,0.14741,0.14741]
ATLAS_PbPb_100to126_Systdown = [0.0536,0.20771,0.34841,0.46231,0.40871,0.25461,0.18090,0.15411,0.15410,0.16080]
Norm_PbPb_100to126 = 0.0
for ibin in range(len(ATLAS_PbPb_100to126_central)):
    Norm_PbPb_100to126 = Norm_PbPb_100to126 + ATLAS_PbPb_100to126_central[ibin]


ATLAS_PbPb_126to158_central = [0.1745,0.73826,1.26174,1.5302,1.66443,1.65101,1.65101,1.61074,1.65101,1.58389]
ATLAS_PbPb_126to158_Statup = [0.05369,0.08053,0.06712,0.06712,0.08054,0.05369,0.05369,0.05369,0.05369,0.05369]
ATLAS_PbPb_126to158_Statdown = [0.04027,0.06712,0.08053,0.06711,0.06711,0.05369,0.05369,0.05369,0.05369,0.05369]
ATLAS_PbPb_126to158_Systup = [0.10738,0.34899,0.46980,0.52349,0.33557,0.21476,0.16107,0.12080,0.09396,0.05369]
ATLAS_PbPb_126to158_Systdown = [0.10739,0.33558,0.48322,0.52349,0.32215,0.21477,0.16108,0.12081,0.08054,0.06711]
Norm_PbPb_126to158 = 0.0
for ibin in range(len(ATLAS_PbPb_126to158_central)):
    Norm_PbPb_126to158 = Norm_PbPb_126to158 + ATLAS_PbPb_126to158_central[ibin]



ATLAS_PbPb_158to200_central = [0.63545,0.47492,1.26421,1.55853,1.43813,1.43813,1.67893,1.77258,1.67893,1.62542]
ATLAS_PbPb_158to200_Statup = [0.17391,0.09364,0.13378,0.13378,0.10702,0.09364,0.10702,0.10702,0.06689,0.09364]
ATLAS_PbPb_158to200_Statdown = [0.17391,0.09365,0.14715,0.13378,0.10703,0.08027,0.10702,0.09365,0.06689,0.10703]
ATLAS_PbPb_158to200_Systup = [0.64214,0.60200,0.58863,0.53512,0.28093,0.17391,0.16053,0.13377,0.12040,0.10702]
ATLAS_PbPb_158to200_Systdown = [0.62876,0.46823,0.60200,0.52174,0.28094,0.16054,0.14716,0.13378,0.12040,0.12040]
Norm_PbPb_158to200 = 0.0
for ibin in range(len(ATLAS_PbPb_158to200_central)):
    Norm_PbPb_158to200 = Norm_PbPb_158to200 + ATLAS_PbPb_158to200_central[ibin]


ATLAS_PbPb_200toinv_central = [0.31438,0.46154,0.91639,1.17057,1.11706,1.26421,1.47826,1.69231,1.90635,2.38796]
ATLAS_PbPb_200toinv_Statup = [0.12040,0.12040,0.13378,0.16053,0.13378,0.13378,0.13378,0.16053,0.12041,0.17391]
ATLAS_PbPb_200toinv_Statdown = [0.12040,0.10702,0.13378,0.17391,0.13378,0.13378,0.12040,0.13378,0.13377,0.16054]
ATLAS_PbPb_200toinv_Systup = [0.32107,0.41471,0.36120,0.32107,0.22742,0.18730,0.18729,0.18729,0.16054,0.17391]
ATLAS_PbPb_200toinv_Systdown = [0.30769,0.42810,0.36121,0.33445,0.22743,0.17391,0.20067,0.18729,0.17391,0.17391]
Norm_PbPb_200toinv = 0.0
for ibin in range(len(ATLAS_PbPb_200toinv_central)):
    Norm_PbPb_200toinv = Norm_PbPb_200toinv + ATLAS_PbPb_200toinv_central[ibin]

Nbins_ATLAS = 10

gr_ATLAS_PbPb_100to126_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_100to126_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_100to126_Statdown),
                                                np.array(ATLAS_PbPb_100to126_Statup))

gr_ATLAS_PbPb_100to126_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_100to126_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_100to126_Systdown),
                                                np.array(ATLAS_PbPb_100to126_Systup))

gr_ATLAS_PbPb_126to158_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_126to158_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_126to158_Statdown),
                                                np.array(ATLAS_PbPb_126to158_Statup))

gr_ATLAS_PbPb_126to158_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_126to158_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_126to158_Systdown),
                                                np.array(ATLAS_PbPb_126to158_Systup))

gr_ATLAS_PbPb_158to200_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_158to200_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_158to200_Statdown),
                                                np.array(ATLAS_PbPb_158to200_Statup))

gr_ATLAS_PbPb_158to200_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_158to200_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_158to200_Systdown),
                                                np.array(ATLAS_PbPb_158to200_Systup))

gr_ATLAS_PbPb_200toinv_Stat = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_200toinv_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_200toinv_Statdown),
                                                np.array(ATLAS_PbPb_200toinv_Statup))

gr_ATLAS_PbPb_200toinv_Syst = ROOT.TGraphAsymmErrors(Nbins_ATLAS,
                                                np.array(ATLAS_PbPb_Xbin),
                                                np.array(ATLAS_PbPb_200toinv_central),
                                                np.array(ATLAS_PbPb_Xdown),
                                                np.array(ATLAS_PbPb_Xup),
                                                np.array(ATLAS_PbPb_200toinv_Systdown),
                                                np.array(ATLAS_PbPb_200toinv_Systup))


list_ATLAS_Norm_PbPb = []
list_ATLAS_Norm_PbPb.append(Norm_PbPb_100to126)
list_ATLAS_Norm_PbPb.append(Norm_PbPb_126to158)
list_ATLAS_Norm_PbPb.append(Norm_PbPb_158to200)
list_ATLAS_Norm_PbPb.append(Norm_PbPb_200toinv)

list_ATLAS_gr_Stat = []
list_ATLAS_gr_Stat.append(gr_ATLAS_PbPb_100to126_Stat)
list_ATLAS_gr_Stat.append(gr_ATLAS_PbPb_126to158_Stat)
list_ATLAS_gr_Stat.append(gr_ATLAS_PbPb_158to200_Stat)
list_ATLAS_gr_Stat.append(gr_ATLAS_PbPb_200toinv_Stat)

list_ATLAS_gr_Syst = []
list_ATLAS_gr_Syst.append(gr_ATLAS_PbPb_100to126_Syst)
list_ATLAS_gr_Syst.append(gr_ATLAS_PbPb_126to158_Syst)
list_ATLAS_gr_Syst.append(gr_ATLAS_PbPb_158to200_Syst)
list_ATLAS_gr_Syst.append(gr_ATLAS_PbPb_200toinv_Syst)
