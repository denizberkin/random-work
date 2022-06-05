import numpy as np
from scipy.interpolate import interp1d


@np.vectorize
def heaviside(x):
    """
    function of step response
    """
    if x < 0:
        return 0
    elif x > 0:
        return 1
    else:
        return interp1d(x, heaviside(x))


precision = 1e-4
inputs = np.arange(-1, 1, precision)
print(sum(heaviside(inputs)))
