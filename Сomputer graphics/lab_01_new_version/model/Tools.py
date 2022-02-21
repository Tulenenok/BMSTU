class Tools:
    EXIT_SUCCESS = 0
    EXIT_FAILURE = 1

    @staticmethod
    def isInt(x):
        try:
            x = int(x)
            return True
        except:
            return False