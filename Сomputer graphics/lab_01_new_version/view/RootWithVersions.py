import shutil
from shared.SharedSettings import SharedSettings

from tkinter import *
from tkinter.messagebox import *


class RootWithVersions(Tk):
    def __init__(self):
        super(RootWithVersions, self).__init__()

        self.objs = None

        self.prevVersionPP = SharedSettings.FILE_PREVIOUS_VERSION_P_P
        self.prevVersionP = SharedSettings.FILE_PREVIOUS_VERSION_P
        self.prevVersion = SharedSettings.FILE_PREVIOUS_VERSION
        self.curVersion = SharedSettings.FILE_CURRENT_VERSION

        self.startingSetting()

    def startingSetting(self):
        try:
            with open(self.prevVersionPP, 'w') as f: pass
            with open(self.prevVersionP, 'w') as f: pass
            with open(self.prevVersion, 'w') as f: pass
            with open(self.curVersion, 'w') as f: pass
        except:
            pass

    def saveShift(self):
        shutil.copyfile(self.prevVersionP, self.prevVersionPP)
        shutil.copyfile(self.prevVersion, self.prevVersionP)
        shutil.copyfile(self.curVersion, self.prevVersion)

    def setSaveObjs(self, *objs):
        self.objs = objs
        for i in range(4):          # Чтобы во всех файлах было начальное состояние системы
            self.saveVersion()

    def saveVersion(self):
        if not self.objs:
            print('Вы не установили объекты, для которых хотите отслеживать состояния. Используйте setSaveObj')
            return

        self.saveShift()
        try:
            with open(self.curVersion, 'wb') as f:
                for obj in self.objs:
                    obj.saveVersion(f)
        except FileNotFoundError:
            print('Файл для считывания не найден')
            return
        except:
            print('Произошла ошибка во время сохранения')

    def loadShift(self):
        shutil.copyfile(self.prevVersion, self.curVersion)
        shutil.copyfile(self.prevVersionP, self.prevVersion)
        shutil.copyfile(self.prevVersionPP, self.prevVersionP)

    def loadVersion(self):
        if not self.objs:
            print('Еще не было сохранено ни одной версии')
            return

        try:
            with open(self.prevVersion, 'rb') as f:
                rc = 0
                try:
                    for obj in self.objs:
                        rc += obj.loadVersion(f)

                    if rc != 0:
                        showinfo('Error', 'Не сегодня')
                except:
                    showinfo('Error', 'Просим простить великодушно, эта функция работает только по четвергам')
        except FileNotFoundError:
            print('Файл для считывания данных не найден')

        self.loadShift()
