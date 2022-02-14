import drawModel as drm

def controll(listPoint):
    listPoint = list(set(listPoint))
    if len(listPoint) < 3:
        return None
    try:
        threeMinPoints = drm.minThreeElByAttr(listPoint, drm.lenBisector)
    except:
        return None
    return threeMinPoints
