package Model;

public class Eggplant implements IVegetable {
    private float weight;

    public Eggplant(float weight) {
        this.weight = weight;
    }

    @Override
    public float getWeight() {
        return this.weight;
    }

    @Override
    public void setWeight(float weight) {
        this.weight = weight;
    }

    @Override
    public String toText() {
        return "Eggplant with the weight: " + this.weight + " kg.";
    }
}
