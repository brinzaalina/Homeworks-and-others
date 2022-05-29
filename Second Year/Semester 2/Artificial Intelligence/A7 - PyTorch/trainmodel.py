import torch
import myModel
from constants import *
import matplotlib.pyplot as plt


def load_data():
    return torch.load("mydataset.dat")


loss_function = torch.nn.MSELoss()
ann = myModel.Net(n_feature=2, n_hidden=128, n_output=1).double()
data = load_data()
print(ann)

# stochastic gradient descent
optimizer_batch = torch.optim.SGD(ann.parameters(), lr=LEARNING_RATE)

loss_list = []
average_lost_list = []

n_batches = len(data) // BATCH_SIZE

data_points = torch.tensor([(x[0], x[1]) for x in data])
data_values = torch.unsqueeze(torch.tensor([x[2] for x in data]), dim=1)
split_data_points = torch.split(data_points, BATCH_SIZE)
split_data_values = torch.split(data_values, BATCH_SIZE)
for epoch in range(NUMBER_EPOCHS):
    for batch in range(n_batches):
        batch_points = split_data_points[batch].double()
        batch_values = split_data_values[batch].double()
        # we compute the output for this batch
        prediction = ann(batch_points)

        # compute the loss for the current batch
        loss = loss_function(prediction, batch_values)
        loss_list.append(loss.item())
        average_lost_list.append(loss.item() / BATCH_SIZE)

        # we set up the gradients for the weights to zero
        optimizer_batch.zero_grad()

        # we compute automatically the variation for each weight (and bias) of the network
        loss.backward()

        #we compute the new values for the weights
        optimizer_batch.step()

    if epoch % 100 == 99:
        y_predictions = ann(data_points.double())
        loss = loss_function(y_predictions, data_values.double())
        print('\reposch: {}\tLoss = {:.5f}'.format(epoch,loss))


plt.plot(loss_list)
plt.savefig("graph.png")

plt.plot(average_lost_list)
plt.savefig("average.png")

filepath = "myNet.pt"
torch.save(ann.state_dict(), filepath)