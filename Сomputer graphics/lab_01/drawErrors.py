class Check:
    @staticmethod
    def isFloat(x):
        try:
            x = float(x)
            return True
        except:
            return False