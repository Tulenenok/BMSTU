class Check:
    @staticmethod
    def isFloat(x):
        try:
            x = float(x)
            return True
        except:
            return False

    @staticmethod
    def isInt(x):
        try:
            x = int(x)
            return True
        except:
            return False