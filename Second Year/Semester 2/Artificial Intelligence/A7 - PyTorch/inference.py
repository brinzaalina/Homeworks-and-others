import torch
import myModel
import math
filepath = "myNet.pt"
ann = myModel.Net(2, 128, 1)
ann.load_state_dict(torch.load(filepath))
ann.eval()

while True:
    x = float(input("x = "))
    y = float(input("y = "))
    print(ann(torch.tensor((x, y))).tolist())
    print(math.sin(x + y / math.pi))