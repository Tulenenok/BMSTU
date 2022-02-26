from model.Tools import Tools

import pandas as pd


# Читает построчно точки из txt-файла (точки записаны в виде x ; y)
def inputPointsTXT(filename):
    if not Tools.isRightFilename(filename) or filename[-4::] != '.txt':
        return -1

    coords = [[]]
    with open(filename, 'r') as fin:
        indLine = 1
        for line in fin:
            if line.rstrip('\n') == Tools.SEPARATOR_POL:
                coords.append([])
                continue
            try:
                x, y = line.split(Tools.SEPARATOR_COORDS)
                coords[-1].append((float(x), float(y)))
            except:
                return indLine           # Если не получается считать, то вернет номер строки, где произошла ошибка
            indLine += 1
        return coords                    # Вернет массив координат для рисования


# Читает построчно точки из xlsx-файла (координаты точек записаны в двух столбцах, столбцы называются X, Y, лист Points)
def inputPointsXLSX(filename):
    if not Tools.isRightFilename(filename) or filename[-5::] != '.xlsx':
        return Tools.INVALID_FILENAME

    try:
        xl = pd.ExcelFile(filename)
        list_points = xl.parse('Points')
        data = list_points[['X', 'Y']]
        x, y = list(data['X']), list(data['Y'])
    except ValueError:
        return Tools.INVALID_LISTNAME
    except KeyError:
        return Tools.INVALID_HEAD
    except:
        return Tools.OBSCURE_ERROR

    try:
        coords = [[(float(x[i]), float(y[i])) for i in range(len(x))]]
        return coords
    except ValueError:
        return Tools.INVALID_FORMAT_DATA
    except IndexError:
        return Tools.INVALID_DATA
    except:
        return Tools.OBSCURE_ERROR