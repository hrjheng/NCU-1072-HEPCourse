import pandas as pd

### Dictionaries for nuclear charge density parameters

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


def MakeDataframe(list_event_):
    list_b = []
    list_Npart = []
    list_Ncoll = []
    list_MeanX = []
    list_MeanY = []
    list_MeanX2 = []
    list_MeanY2 = []
    list_MeanXY = []
    list_VarX = []
    list_VarY = []
    list_VarXY =[]
    list_epsRP = []
    list_epspart = []

    for iev in range(len(list_event_)):
        list_b.append(list_event_[iev].b)
        list_Npart.append(list_event_[iev].Npart)
        list_Ncoll.append(list_event_[iev].Ncoll)
        list_MeanX.append(list_event_[iev].MeanX)
        list_MeanY.append(list_event_[iev].MeanY)
        list_MeanX2.append(list_event_[iev].MeanX2)
        list_MeanY2.append(list_event_[iev].MeanY2)
        list_MeanXY.append(list_event_[iev].MeanXY)
        list_VarX.append(list_event_[iev].VarX)
        list_VarY.append(list_event_[iev].VarY)
        list_VarXY.append(list_event_[iev].VarXY)
        list_epsRP.append(list_event_[iev].eps_RP)
        list_epspart.append(list_event_[iev].eps_part)


    d = {'b': list_b,
         'Npart': list_Npart,
         'Ncoll': list_Ncoll,
         'MeanX': list_MeanX,
         'MeanY': list_MeanY,
         'MeanX2': list_MeanX2,
         'MeanY2': list_MeanY2,
         'MeanXY': list_MeanXY,
         'VarX': list_VarX,
         'VarY': list_VarY,
         'epsRP': list_epsRP,
         'epspart': list_epspart}

    df = pd.DataFrame(data=d)

    return df
