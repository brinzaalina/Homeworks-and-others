import math
import torch
from constants import *


def function(x, y):
    return math.sin(x + y / math.pi)


def get_random_values():
    return [-20 * x + 10 for x in torch.rand(SAMPLE_SIZE)]


def get_random_points():
    return get_random_values(), get_random_values()


def compute_db():
    filepath = "mydataset.dat"
    result = []
    all_x, all_y = get_random_points()
    for i in range(SAMPLE_SIZE):
        result.append((all_x[i], all_y[i], function(all_x[i], all_y[i])))
    torch_data = torch.tensor([point for point in result])
    torch.save(torch_data, filepath)

compute_db()