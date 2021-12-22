package Controller;

import Model.Eggplant;
import Model.Pepper;
import Model.Tomato;
import Model.IVegetable;
import Repository.IRepository;

import java.util.Objects;

public class Controller {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(String type, float weight) {
        if (Objects.equals(type, "eggplant")) {
            Eggplant eggplant = new Eggplant(weight);
            this.repository.add(eggplant);
        } else if (Objects.equals(type, "pepper")) {
            Pepper pepper = new Pepper(weight);
            this.repository.add(pepper);
        } else if (Objects.equals(type, "tomato")) {
            Tomato tomato = new Tomato(weight);
            this.repository.add(tomato);
        }
    }

    public void remove(int index) {
        this.repository.remove(index);
    }

    public IVegetable[] getVegetables() {
        return this.repository.getVegetables();
    }

    public int getSize() {
        return this.repository.getSize();
    }

    public IVegetable[] getFilteredVegetables(float weight) {
        IVegetable[] copy = new IVegetable[this.repository.getSize()];
        int size = 0;
        for (IVegetable vegetable: this.repository.getVegetables())
            if (vegetable != null)
                if (vegetable.getWeight() > weight)
                    copy[size++] = vegetable;
        IVegetable[] toReturn = new IVegetable[size];
        System.arraycopy(copy, 0, toReturn, 0, size);
        return toReturn;
    }
}
