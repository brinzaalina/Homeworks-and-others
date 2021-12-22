package Repository;

import Model.IVegetable;

public class Repository implements IRepository {
    private IVegetable[] vegetables;
    private int numberOfVegetables;

    public Repository(int size) {
        if (size <= 0) {
            throw new ArithmeticException("The capacity of the repository cannot be 0 or less.");
        }
        this.vegetables = new IVegetable[size];
        this.numberOfVegetables = 0;
    }

    private void resize() {
        IVegetable[] newVegetables = new IVegetable[this.numberOfVegetables * 2];
        System.arraycopy(this.vegetables, 0, newVegetables, 0, this.vegetables.length);
        this.vegetables = newVegetables;
    }

    @Override
    public void add(IVegetable vegetable) {
        if (this.numberOfVegetables == this.vegetables.length) {
            this.resize();
        }
        this.vegetables[numberOfVegetables] = vegetable;
        numberOfVegetables++;
    }

    @Override
    public void remove(int index) {
        IVegetable[] vegetableCopy = new IVegetable[this.numberOfVegetables - 1];
        for (int i = 0, j = 0; i < this.numberOfVegetables; i++) {
            if (i != index) {
                vegetableCopy[j] = this.vegetables[i];
                j++;
            }
        }
        this.vegetables = vegetableCopy;
        this.numberOfVegetables--;
    }

    @Override
    public IVegetable[] getVegetables() {
        return this.vegetables;
    }

    @Override
    public int getSize() {
        return this.numberOfVegetables;
    }
}
