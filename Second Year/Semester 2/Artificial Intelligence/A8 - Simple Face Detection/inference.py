from torchvision import transforms
from train import SimpleNet
from PIL import Image
import torch


def read_and_preprocess_image(image_path):
    image = Image.open(image_path).convert('RGB')
    image_size = 32
    transformations = transforms.Compose(
        [
            transforms.Resize(image_size),
            transforms.CenterCrop(image_size),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ]
    )
    return transformations(image).unsqueeze(0)


if __name__ == '__main__':
    model_path = input('Path to model: ')
    model = SimpleNet(num_classes=2)
    model.load_state_dict(torch.load(model_path))
    print()
    while True:
        try:
            image_path = input('Path to image: ')
            image = read_and_preprocess_image(image_path)
            prediction = model(image).detach().numpy()[0]
            not_face = prediction[0]
            face = prediction[1]
            if face > 0:
                print("The image contains a face.")
            elif not_face > 0:
                print("The image does not contain a face.")
            else:
                print("Cannot determine.")
            print()
        except KeyboardInterrupt:
            break
