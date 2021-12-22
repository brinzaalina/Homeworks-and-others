package Model;

public class Pepper implements IVegetable {
    private float weight;

    public Pepper(float weight) {
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
        return "Pepper with the weight: " + this.weight + " kg.";
    }
}
