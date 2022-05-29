import random
import torch
from torch.utils.data import Dataset
from torchvision import transforms
from PIL import Image

device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')


class ImageClassifierDataset(Dataset):
    def __init__(self, image_list, image_classes):
        self.images = []
        self.labels = []
        self.classes = list(set(image_classes))
        self.class_to_label = {c: i for i, c in enumerate(self.classes)}
        self.image_size = 32
        self.transforms = transforms.Compose([
            transforms.Resize(self.image_size),
            transforms.CenterCrop(self.image_size),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])
        for image, image_class in zip(image_list, image_classes):
            transformed_image = self.transforms(image)
            self.images.append(transformed_image)
            label = self.class_to_label[image_class]
            self.labels.append(label)

    def __getitem__(self, index):
        return self.images[index], self.labels[index]

    def __len__(self):
        return len(self.images)


def load_data():
    extensions = ["jpg", "png", "webp"]
    males = "Faces/Male/male"
    females = "Faces/Female/female"
    others = "Faces/Random/random"
    images = []
    for index in range(1, 51):
        for extension in extensions:
            path = males + '(' + str(index) + ').' + extension
            try:
                image = Image.open(path)
                images.append([image, 1])
            except FileNotFoundError:
                print("not found", path)
            path = females + '(' + str(index) + ').' + extension
            try:
                image = Image.open(path)
                images.append([image, 1])
            except FileNotFoundError:
                print("not found", path)
            path = others + '(' + str(index) + ').' + extension
            try:
                image = Image.open(path)
                images.append([image, 0])
            except FileNotFoundError:
                print("not found", path)
    print("Loaded", len(images), "images")
    return images


def get_data_set(train_test_ratio=0.8):
    images = load_data()
    image_list_train = []
    image_classes_train = []
    image_list_test = []
    image_classes_test = []
    train_data = random.sample(images, int(len(images) * train_test_ratio))
    test_data = []
    for img in images:
        if img not in train_data:
            test_data.append(img)

    for img in train_data:
        rgb_only = img[0].convert('RGB')
        image_list_train.append(rgb_only)
        image_classes_train.append(img[1])

    for img in test_data:
        rgb_only = img[0].convert('RGB')
        image_list_test.append(rgb_only)
        image_classes_test.append(img[1])

    train_data = ImageClassifierDataset(image_list_train, image_classes_train)
    test_data = ImageClassifierDataset(image_list_test, image_classes_test)

    return train_data, test_data