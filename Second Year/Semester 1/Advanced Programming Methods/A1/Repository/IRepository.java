package Repository;

import Model.IVegetable;

public interface IRepository {
    void add(IVegetable vegetable);
    void remove(int index);
    IVegetable[] getVegetables();
    int getSize();
}
