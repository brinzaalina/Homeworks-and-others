package View;

import Controller.Controller;
import Exceptions.InputException;
import Model.IVegetable;

import java.util.Objects;
import java.util.Scanner;

public class View {
    private final Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    private static void printMenu() {
        System.out.println("Choose an option: ");
        System.out.println("1. Display all vegetables.");
        System.out.println("2. Add a vegetable.");
        System.out.println("3. Remove a vegetable.");
        System.out.println("4. Display all the vegetables that have the weight greater than a given weight.");
        System.out.println("5. Exit.");
    }

    private void printVegetables() {
        IVegetable[] vegetables = this.controller.getVegetables();
        if (this.controller.getSize() == 0) {
            System.out.println("No vegetables!");
        } else {
            int index;
            for (index = 0; index < this.controller.getSize(); index++) {
                System.out.println((index + 1) + ". " + vegetables[index].toText());
            }
        }
    }

    private void addVegetable() throws InputException {
        System.out.println("Enter type: ");
        Scanner readType = new Scanner(System.in);
        String type = readType.nextLine();
        if (Objects.equals(type, "eggplant") || Objects.equals(type, "pepper") || Objects.equals(type, "tomato")) {
            System.out.println("Enter weight: ");
            Scanner readWeight = new Scanner(System.in);
            float weight = readWeight.nextFloat();
            if (weight <= 0) {
                throw new InputException("Invalid weight!");
            } else {
                this.controller.add(type, weight);
            }
        } else {
            throw new InputException("Invalid type!");
        }
    }

    private void removeVegetable() throws InputException {
        if (this.controller.getSize() != 0) {
            System.out.println("Enter index: ");
            Scanner readIndex = new Scanner(System.in);
            int index = readIndex.nextInt();
            if (index - 1 >= 0 && index - 1 < this.controller.getSize()) {
                this.controller.remove(index - 1);
            } else {
                throw new InputException("Invalid index!");
            }
        } else {
            throw new InputException("There is nothing left to remove!");
        }
    }

    private void displayFilteredVegetables() throws InputException {
        System.out.println("Enter weight: ");
        Scanner readWeight = new Scanner(System.in);
        float weight = readWeight.nextFloat();
        if (weight <= 0) {
            throw new InputException("Invalid weight!");
        } else {
            if (this.controller.getSize() != 0) {
                IVegetable[] filteredVegetables = this.controller.getFilteredVegetables(weight);
                if (filteredVegetables.length == 0) {
                    System.out.println("There are no vegetables that have the weight greater than " + weight + " kg.");
                } else {
                    int index;
                    for (index = 0; index < filteredVegetables.length; index++) {
                        System.out.println((index + 1) + ". " + filteredVegetables[index].toText());
                    }
                }
            } else {
                throw new InputException("The list is empty!");
            }
        }
    }

    public void start() {
        boolean done = false;
        while (!done) {
            try {
                printMenu();
                Scanner readOption = new Scanner(System.in);
                int option = readOption.nextInt();
                if (option == 1) {
                    this.printVegetables();
                } else if (option == 2) {
                    this.addVegetable();
                } else if (option == 3) {
                    this.removeVegetable();
                } else if (option == 4) {
                    this.displayFilteredVegetables();
                } else if (option == 5) {
                    done = true;
                } else {
                    System.out.println("Invalid input!");
                }
            } catch (InputException inputException) {
                System.out.println(inputException.getMessage());
            }
        }
    }
}
